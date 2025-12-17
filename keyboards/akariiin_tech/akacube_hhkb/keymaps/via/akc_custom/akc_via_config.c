// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "akc_custom.h"

// Compile-time check to ensure VIA custom config space is sufficient
_Static_assert(VIA_EEPROM_CUSTOM_CONFIG_SIZE >= 10, "VIA custom config size too small for configuration");

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
    FLAG_OVERRIDE_LAYERLED = 12,
    FLAG_AUTO_DISABLE = 13,
    FLAG_AUTO_SWAP = 14
};

// Configuration initialization flag
static bool config_loaded = false;

// Configuration matrix [5x3]:
//      | col 0        | col 1           | col 2
// -----+--------------+-----------------+----------------
// row 0| lock0_mask   | lock0_off_color | lock0_on_color
// row 1| lock1_mask   | lock1_off_color | lock1_on_color
// row 2| lock2_mask   | lock2_off_color | lock2_on_color
// row 3| timeout      | layer_off_color | layer_on_color
// row 4| flags        | reserved        | reserved
//
// Lock mask: 0=disable, 1=numlock, 2=capslock, 4=scrolllock, 8=compose, 16=kana
// Colors: 1-13 (0=EEPROM reset), EEPROM VIA custom config area: 10 bytes packed
static uint8_t via_config[5][3];

// Validation functions
static bool is_valid_lockled_mask(uint8_t value) {
    return (value == 0 || value == 1 || value == 2 || value == 4 || value == 8 || value == 16);
}

static bool is_valid_timeout_value(uint8_t value) {
    return (value >= 1 && value <= 100);
}

static bool is_valid_flag_group(uint8_t value) {
    return (value & 0xF8) == 0x80;  // Bit 7 set (valid marker), bits 3-6 clear (reserved)
}

static bool is_valid_color_index(uint8_t value) {
    return (value >= 1 && value <= 14);
}

static bool is_valid_config_matrix(uint8_t row, uint8_t col) {
    if (row < 4) { return (col <= 2); }
    if (row == 4) { return (col == 0); }
    return false;
}

// Data packing/unpacking functions
// 80-bit EEPROM: [79:64 flags][63:48 layer][47:32 lock2][31:16 lock1][15:0 lock0]
// 16-bit pack: [15:12 color_on][11:8 color_off][7:0 timeout/flags/data]
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

// Flag access functions
static uint8_t update_flag_bit(uint8_t bit_index, bool value) {
    value ? (via_config[4][0] |= (1 << bit_index))
          : (via_config[4][0] &= ~(1 << bit_index));
    return via_config[4][0];
}

// VIA custom config I/O functions
static void eeload_config_all(void) {
    uint8_t config[10];
    via_read_custom_config(config, 0, 10);
    for (uint8_t row = 0; row < 5; row++) {
        uint8_t offset = row * 2;
        uint16_t packed = (uint16_t)config[offset] | ((uint16_t)config[offset + 1] << 8);
        unpack_matrix_row(packed, row);
    }
}

static void eesave_config_all(void) {
    uint8_t config[10];
    for (uint8_t row = 0; row < 5; row++) {
        uint16_t packed = pack_matrix_row(row);
        uint8_t offset = row * 2;
        config[offset] = (uint8_t)(packed & 0xFF);
        config[offset + 1] = (uint8_t)((packed >> 8) & 0xFF);
    }
    via_update_custom_config(config, 0, 10);
}

static void eesave_config_matrix_row(uint8_t row_index) {
    if (!is_valid_config_matrix(row_index, 0)) return;

    uint16_t packed = pack_matrix_row(row_index);
    uint8_t offset = row_index * 2;
    uint8_t data[2] = {
        (uint8_t)(packed & 0xFF),
        (uint8_t)((packed >> 8) & 0xFF)
    };
    via_update_custom_config(data, offset, 2);
}

// Core configuration functions
static bool via_update_config(uint8_t row_index, uint8_t col_index, uint8_t new_value) {
    // Validate parameters
    if (!is_valid_config_matrix(row_index, col_index)) {
        return false;
    }

    // Check for value change
    if (via_config[row_index][col_index] == new_value) {
        return false; // No change needed
    }

    // Validate new value based on position
    bool is_valid = false;
    switch (col_index) {
        case 0:
            if (row_index < 3) {
                is_valid = is_valid_lockled_mask(new_value);
            } else if (row_index == 3) {
                is_valid = is_valid_timeout_value(new_value);
            } else {
                is_valid = is_valid_flag_group(new_value);
            }
            break;
        default:  // case 1, 2
            is_valid = is_valid_color_index(new_value);  // Only row 0-3 could reach here
            break;
    }

    if (!is_valid) return false;

    // Update the value and save to EEPROM VIA custom config area
    via_config[row_index][col_index] = new_value;
    eesave_config_matrix_row(row_index);
    return true;
}

// Initialize VIA configuration from EEPROM VIA custom config area
void akc_via_init_config(void) {
    if (config_loaded) return;

    static const uint8_t default_config[5][3] = {
        {AKC_LOCKLED_0, 1, 5},            // 1: Red, 5: Green
        {AKC_LOCKLED_1, 1, 5},            // 1: Red, 5: Green
        {AKC_LOCKLED_2, 1, 5},            // 1: Red, 5: Green
        {(AKC_LED_KEEPTIME / 100), 1, 9}, // 1: Red, 9: Blue
        {0x86, 0, 0}                      // row 4: flags (0b10000110: bit7=valid, bit2|1|0=flags) + reserved
    };

    eeload_config_all();

    // Validate loaded config per-row (handles corrupted data)
    for (uint8_t row = 0; row < 5; row++) {
        bool should_reset_row = false;

        if (row < 3) {
            // Validate LED row
            if (!is_valid_lockled_mask(via_config[row][0]) ||
                !is_valid_color_index(via_config[row][1]) ||
                !is_valid_color_index(via_config[row][2])) {
                should_reset_row = true;
            }
        } else if (row == 3) {
            // Validate timeout row (row 3)
            if (!is_valid_timeout_value(via_config[row][0]) ||
                !is_valid_color_index(via_config[row][1]) ||
                !is_valid_color_index(via_config[row][2])) {
                should_reset_row = true;
            }
        } else {
            // Validate flags row (row 4)
            if (!is_valid_flag_group(via_config[row][0]) ||
                via_config[row][1] > 0 ||
                via_config[row][2] > 0) {
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
}

void akc_via_save_config(void) {
    eesave_config_all();
}

// Public API functions
uint8_t akc_via_get_config(uint8_t row, uint8_t col) {
    if (!is_valid_config_matrix(row, col) || (row > 2 && col == 0)) return 0;
    return via_config[row][col];
}

uint8_t akc_via_get_led_timeout(void) {
    return via_config[3][0];
}

bool akc_via_get_flag(uint8_t flag_index) {
    return (via_config[4][0] >> flag_index) & 0x1;
}

bool akc_via_lock_system_enabled(void) {
    if ((via_config[0][0] | via_config[1][0] | via_config[2][0]) == 0) return false;

    if (akc_via_get_flag(1)) {
        os_variant_t host_os = detected_host_os();
        if (host_os == OS_MACOS || host_os == OS_IOS) return false;
    }
    return true;
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
                        value_data[0] = via_config[3][0];
                        break;
                    case FLAG_OVERRIDE_LAYERLED:
                        value_data[0] = akc_via_get_flag(0);
                        break;
                    case FLAG_AUTO_DISABLE:
                        value_data[0] = akc_via_get_flag(1);
                        break;
                    case FLAG_AUTO_SWAP:
                        value_data[0] = akc_via_get_flag(2);
                        break;
                    default:
                        *command_id = id_unhandled;
                        return;
                }
                break;
            }
            case id_custom_set_value: {
                bool should_refresh_lockled = false;
                bool should_refresh_layerled = false;
                bool should_init_lockled = false;
                bool should_init_layerled = false;
                switch (*value_id) {
                    case LOCK_LED_0_CONFIG:
                        should_refresh_lockled = via_update_config(0, 0, value_data[0]);
                        break;
                    case LOCK_LED_0_COLOR_OFF:
                        should_init_lockled = via_update_config(0, 1, value_data[0]);
                        break;
                    case LOCK_LED_0_COLOR_ON:
                        should_init_lockled = via_update_config(0, 2, value_data[0]);
                        break;
                    case LOCK_LED_1_CONFIG:
                        should_refresh_lockled = via_update_config(1, 0, value_data[0]);
                        break;
                    case LOCK_LED_1_COLOR_OFF:
                        should_init_lockled = via_update_config(1, 1, value_data[0]);
                        break;
                    case LOCK_LED_1_COLOR_ON:
                        should_init_lockled = via_update_config(1, 2, value_data[0]);
                        break;
                    case LOCK_LED_2_CONFIG:
                        should_refresh_lockled = via_update_config(2, 0, value_data[0]);
                        break;
                    case LOCK_LED_2_COLOR_OFF:
                        should_init_lockled = via_update_config(2, 1, value_data[0]);
                        break;
                    case LOCK_LED_2_COLOR_ON:
                        should_init_lockled = via_update_config(2, 2, value_data[0]);
                        break;
                    case LAYER_LED_COLOR_OFF:
                        should_init_layerled = via_update_config(3, 1, value_data[0]);
                        break;
                    case LAYER_LED_COLOR_ON:
                        should_init_layerled = via_update_config(3, 2, value_data[0]);
                        break;
                    case LOCK_LED_TIMEOUT_CONFIG:
                        via_update_config(3, 0, value_data[0]);
                        break;
                    case FLAG_OVERRIDE_LAYERLED:
                        should_refresh_layerled = via_update_config(4, 0, update_flag_bit(0, value_data[0]));
                        break;
                    case FLAG_AUTO_DISABLE:
                        via_update_config(4, 0, update_flag_bit(1, value_data[0]));
                        break;
                    case FLAG_AUTO_SWAP:
                        via_update_config(4, 0, update_flag_bit(2, value_data[0]));
                        akc_env_setup_swap_ag(value_data[0] ? detected_host_os() : OS_UNSURE);
                        break;
                    default:
                        *command_id = id_unhandled;
                        return;
                }

                if (should_refresh_lockled) { akc_led_refresh_lockled(); }
                if (should_refresh_layerled) { akc_led_refresh_layerled(); }
                if (should_init_lockled) { akc_led_init_lockled(); }
                if (should_init_layerled) { akc_led_init_layerled(); }
                break;
            }
            case id_custom_save: {
                akc_via_save_config();
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
