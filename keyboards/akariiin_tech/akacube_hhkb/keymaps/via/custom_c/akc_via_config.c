// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "akc_via_config.h"
#include "akc_config.h"
#include "eeconfig.h"

// Compile-time check to ensure EEPROM user data space is sufficient
_Static_assert(8 <= EECONFIG_USER_DATA_SIZE, "EEPROM user data size too small for configuration");

// VIA Configuration Channel IDs
enum via_config_channels {
    LOCK_LED_CONFIG_CHANNEL = 0  // Use custom channel
};

// VIA Configuration Value IDs for Lock LEDs
enum lock_led_config_ids {
    LOCK_LED_0_CONFIG = 0,
    LOCK_LED_0_COLOR_OFF = 1,
    LOCK_LED_0_COLOR_ON = 2,
    LOCK_LED_1_CONFIG = 3,
    LOCK_LED_1_COLOR_OFF = 4,
    LOCK_LED_1_COLOR_ON = 5,
    LOCK_LED_2_CONFIG = 6,
    LOCK_LED_2_COLOR_OFF = 7,
    LOCK_LED_2_COLOR_ON = 8,
    LAYER_LED_COLOR_OFF = 9,
    LAYER_LED_COLOR_ON = 10,
    LOCK_LED_TIMEOUT_CONFIG = 11,
    LAYERKEY_SHOW_LOCKLED_CONFIG = 12
};

// Configuration initialization flag
static bool config_loaded = false;

// Configuration matrix [4x3]:
//      | col 0       | col 1      | col 2
// -----+-------------+------------+----------
// row 0| lock0_mask  | color_off  | color_on
// row 1| lock1_mask  | color_off  | color_on
// row 2| lock2_mask  | color_off  | color_on
// row 3| timeout|flag| layer_off  | layer_on
//
// Lock mask: 0=disable, 1=numlock, 2=capslock, 4=scrolllock, 8=compose, 16=kana
// Colors: 1-13 (0=EEPROM reset), EEPROM: 8 bytes packed
static uint8_t via_config[4][3];

// Validation functions
static bool is_valid_lock_led_value(uint8_t value) {
    return (value == 0 || value == 1 || value == 2 || value == 4 || value == 8 || value == 16);
}

static bool is_valid_timeout_value(uint8_t value) {
    return (value >= 1 && value <= 100);
}

static bool is_valid_color_index(uint8_t value) {
    return (value >= 1 && value <= 13);
}

static bool is_valid_config_matrix(uint8_t row, uint8_t col) {
    return (row <= 3 && col <= 2);
}

static bool is_valid_default_layer(uint32_t mask) {
    return (mask == 1 || mask == 2 || mask == 4 || mask == 8);
}

// Get default layer from EEPROM or keymap
static void eerestore_default_layer(void) {
    uint32_t load_default_layer = 1;  // Initialize with fallback layer 0

    uint8_t eeload_default_layer_shift = get_highest_layer(eeconfig_read_default_layer());
    uint32_t eeload_default_layer = (1UL << eeload_default_layer_shift);

    if (is_valid_default_layer(eeload_default_layer)) {
        load_default_layer = eeload_default_layer;  // Valid default layer from EEPROM
    } else if (is_valid_default_layer(default_layer_state)) {
        load_default_layer = default_layer_state;  // Valid default layer from keymap
    }

    default_layer_set(load_default_layer);
    layer_state_set(default_layer_state); // Workaround to ensure layer state is set
}

// Data packing/unpacking functions
// 64-bit EEPROM: [63:48 layer][47:32 lock2][31:16 lock1][15:0 lock0]
// 16-bit pack: [15:12 color_on][11:8 color_off][7:0 config/timeout]
static uint16_t pack_matrix_row(uint8_t row_index) {
    return (uint16_t)via_config[row_index][0] |
           ((uint16_t)(via_config[row_index][1] & 0xF) << 8) |
           ((uint16_t)(via_config[row_index][2] & 0xF) << 12);
}

static void unpack_matrix_row(uint16_t packed, uint8_t row_index) {
    via_config[row_index][0] = (uint8_t)(packed & 0xFF);
    via_config[row_index][1] = (uint8_t)((packed >> 8) & 0xF);
    via_config[row_index][2] = (uint8_t)((packed >> 12) & 0xF);
}

// Mixed timeout/flag manipulation functions
static uint8_t pick_mixed_time(void) {
    return via_config[3][0] & 0x7F;  // Lower 7 bits
}

static uint8_t pick_mixed_flag(void) {
    return (via_config[3][0] >> 7) & 0x1;  // Upper 1 bit
}

static uint8_t merge_mixed_time(uint8_t new_timeout) {
    uint8_t flag = pick_mixed_flag();
    return (new_timeout & 0x7F) | (flag << 7);
}

static uint8_t merge_mixed_flag(uint8_t new_flag) {
    uint8_t timeout = pick_mixed_time();
    return (timeout & 0x7F) | ((new_flag & 0x1) << 7);
}

// EEPROM I/O functions
static void eeload_all_config(void) {
    uint8_t config[8];
    eeconfig_read_user_datablock(config, 0, 8);
    for (uint8_t row = 0; row < 4; row++) {
        uint8_t offset = row * 2;
        uint16_t packed = (uint16_t)config[offset] | ((uint16_t)config[offset + 1] << 8);
        unpack_matrix_row(packed, row);
    }
}

static void eesave_all_config(void) {
    uint8_t config[8];
    for (uint8_t row = 0; row < 4; row++) {
        uint16_t packed = pack_matrix_row(row);
        uint8_t offset = row * 2;
        config[offset] = (uint8_t)(packed & 0xFF);
        config[offset + 1] = (uint8_t)((packed >> 8) & 0xFF);
    }
    eeconfig_update_user_datablock(config, 0, 8);
}

static void eesave_config_matrix_row(uint8_t row_index) {
    if (!is_valid_config_matrix(row_index, 0)) return;

    uint16_t packed = pack_matrix_row(row_index);
    uint8_t offset = row_index * 2;
    uint8_t data[2] = {
        (uint8_t)(packed & 0xFF),
        (uint8_t)((packed >> 8) & 0xFF)
    };
    eeconfig_update_user_datablock(data, offset, 2);
}

// Core configuration functions
static bool via_update_config(uint8_t row_index, uint8_t col_index, uint8_t new_value) {
    // Validate parameters
    if (!is_valid_config_matrix(row_index, col_index)) {
        return false;
    }

    // Check if value is different
    if (via_config[row_index][col_index] == new_value) {
        return false; // No change needed
    }

    // Validate new value based on position
    bool is_valid = false;
    switch (col_index) {
        case 0:
            if (row_index < 3) {
                is_valid = is_valid_lock_led_value(new_value);
            } else {
                // For packed timeout/flag, validate the entire byte
                uint8_t timeout = new_value & 0x7F;
                is_valid = is_valid_timeout_value(timeout);
            }
            break;
        default:  // case 1, 2
            is_valid = is_valid_color_index(new_value);  // Same for all rows
            break;
    }

    if (!is_valid) return false;

    // Update the value and save to EEPROM
    via_config[row_index][col_index] = new_value;
    eesave_config_matrix_row(row_index);
    return true;
}

// Initialize VIA configuration from EEPROM using user datablock
void akc_via_config_init(void) {
    if (config_loaded) return;

    static const uint8_t default_config[4][3] = {
        {AKC_LOCKLED_0, 1, 5},  // 1: Red, 5: Green
        {AKC_LOCKLED_1, 1, 5},  // 1: Red, 5: Green
        {AKC_LOCKLED_2, 1, 5},  // 1: Red, 5: Green
        {(AKC_LED_KEEPTIME / 100), 1, 9}  // 1: Red, 9: Blue
    };

    eeload_all_config();

    // Validate loaded config per-row (handles corrupted data)
    for (uint8_t row = 0; row < 4; row++) {
        bool should_reset_row = false;

        if (row < 3) {
            // Validate LED row
            if (!is_valid_lock_led_value(via_config[row][0]) ||
                !is_valid_color_index(via_config[row][1]) ||
                !is_valid_color_index(via_config[row][2])) {
                should_reset_row = true;
            }
        } else {
            // Validate misc row (row 3)
            if (!is_valid_timeout_value(pick_mixed_time()) ||
                !is_valid_color_index(via_config[3][1]) ||
                !is_valid_color_index(via_config[3][2])) {
                should_reset_row = true;
            }
        }

        if (should_reset_row) {
            // Reset only this row to defaults
            memcpy(via_config[row], default_config[row], 3);
            eesave_config_matrix_row(row);
        }
    }

    config_loaded = true;

    eerestore_default_layer();

    akc_refresh_lockled();
    akc_refresh_layerled();
}

void akc_via_config_save(void) {
    eesave_all_config();
}

// Public API functions
uint8_t akc_via_get_config(uint8_t row, uint8_t col) {
    if (!is_valid_config_matrix(row, col) || (row == 3 && col == 0)) return 0;
    return via_config[row][col];
}

uint8_t akc_via_get_led_timeout(void) {
    return pick_mixed_time();
}

bool akc_via_get_layerkey_show_lockled(void) {
    return pick_mixed_flag() != 0;
}

bool akc_via_lock_system_enabled(void) {
    return (via_config[0][0] | via_config[1][0] | via_config[2][0]) > 0;
}

// VIA protocol handler
void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id = &(data[0]);
    uint8_t *channel_id = &(data[1]);
    uint8_t *value_id   = &(data[2]);
    uint8_t *value_data = &(data[3]);
    // Check if this is for our custom lock LED channel
    if (*channel_id == LOCK_LED_CONFIG_CHANNEL) {
        switch (*command_id) {
            case id_custom_get_value: {
                switch (*value_id) {
                    case LOCK_LED_0_CONFIG:
                        value_data[0] = via_config[0][0];
                        break;
                    case LOCK_LED_0_COLOR_OFF:
                        value_data[0] = via_config[0][1];
                        break;
                    case LOCK_LED_0_COLOR_ON:
                        value_data[0] = via_config[0][2];
                        break;
                    case LOCK_LED_1_CONFIG:
                        value_data[0] = via_config[1][0];
                        break;
                    case LOCK_LED_1_COLOR_OFF:
                        value_data[0] = via_config[1][1];
                        break;
                    case LOCK_LED_1_COLOR_ON:
                        value_data[0] = via_config[1][2];
                        break;
                    case LOCK_LED_2_CONFIG:
                        value_data[0] = via_config[2][0];
                        break;
                    case LOCK_LED_2_COLOR_OFF:
                        value_data[0] = via_config[2][1];
                        break;
                    case LOCK_LED_2_COLOR_ON:
                        value_data[0] = via_config[2][2];
                        break;
                    case LAYER_LED_COLOR_OFF:
                        value_data[0] = via_config[3][1];
                        break;
                    case LAYER_LED_COLOR_ON:
                        value_data[0] = via_config[3][2];
                        break;
                    case LOCK_LED_TIMEOUT_CONFIG:
                        value_data[0] = pick_mixed_time();
                        break;
                    case LAYERKEY_SHOW_LOCKLED_CONFIG:
                        value_data[0] = pick_mixed_flag();
                        break;
                    default:
                        *command_id = id_unhandled;
                        return;
                }
                break;
            }
            case id_custom_set_value: {
                bool should_update_lockled = false;
                bool should_update_layerled = false;
                switch (*value_id) {
                    case LOCK_LED_0_CONFIG:
                        should_update_lockled = via_update_config(0, 0, value_data[0]);
                        break;
                    case LOCK_LED_0_COLOR_OFF:
                        should_update_lockled = via_update_config(0, 1, value_data[0]);
                        break;
                    case LOCK_LED_0_COLOR_ON:
                        should_update_lockled = via_update_config(0, 2, value_data[0]);
                        break;
                    case LOCK_LED_1_CONFIG:
                        should_update_lockled = via_update_config(1, 0, value_data[0]);
                        break;
                    case LOCK_LED_1_COLOR_OFF:
                        should_update_lockled = via_update_config(1, 1, value_data[0]);
                        break;
                    case LOCK_LED_1_COLOR_ON:
                        should_update_lockled = via_update_config(1, 2, value_data[0]);
                        break;
                    case LOCK_LED_2_CONFIG:
                        should_update_lockled = via_update_config(2, 0, value_data[0]);
                        break;
                    case LOCK_LED_2_COLOR_OFF:
                        should_update_lockled = via_update_config(2, 1, value_data[0]);
                        break;
                    case LOCK_LED_2_COLOR_ON:
                        should_update_lockled = via_update_config(2, 2, value_data[0]);
                        break;
                    case LAYER_LED_COLOR_OFF:
                        should_update_layerled = via_update_config(3, 1, value_data[0]);
                        break;
                    case LAYER_LED_COLOR_ON:
                        should_update_layerled = via_update_config(3, 2, value_data[0]);
                        break;
                    case LOCK_LED_TIMEOUT_CONFIG:
                        via_update_config(3, 0, merge_mixed_time(value_data[0]));
                        break;
                    case LAYERKEY_SHOW_LOCKLED_CONFIG:
                        should_update_layerled = via_update_config(3, 0, merge_mixed_flag(value_data[0]));
                        break;
                    default:
                        *command_id = id_unhandled;
                        return;
                }

                if (should_update_lockled) { akc_refresh_lockled(); }
                if (should_update_layerled) { akc_refresh_layerled(); }
                break;
            }
            case id_custom_save: {
                akc_via_config_save();
                break;
            }
            default:
                *command_id = id_unhandled;
                return;
        }
        return; // Command handled successfully
    }

    // Unknown channel - mark as unhandled
    *command_id = id_unhandled;
}
