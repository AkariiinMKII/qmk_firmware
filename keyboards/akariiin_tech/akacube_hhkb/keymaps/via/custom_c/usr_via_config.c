// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_via_config.h"
#include "usr_led_control.h"
#include "eeconfig.h"

// Compile-time check to ensure EEPROM user data space is sufficient
_Static_assert(sizeof(uint32_t) <= EECONFIG_USER_DATA_SIZE, "EEPROM user data size too small for configuration");


// VIA Configuration Channel IDs
enum via_config_channels {
    LOCK_LED_CONFIG_CHANNEL = 0  // Use custom channel
};

// VIA Configuration Value IDs for Lock LEDs
enum lock_led_config_ids {
    LOCK_LED_1_CONFIG = 0,
    LOCK_LED_2_CONFIG = 1,
    LOCK_LED_3_CONFIG = 2,
    LOCK_LED_TIMEOUT_CONFIG = 3,
    LAYERKEY_SHOW_LOCKLED_CONFIG = 4
};

// Lock LED type values (must match VIA UI)
enum lock_led_types {
    LOCK_TYPE_DISABLE = 0,
    LOCK_TYPE_NUMLOCK = 1,
    LOCK_TYPE_CAPSLOCK = 2,
    LOCK_TYPE_SCROLLLOCK = 4,
    LOCK_TYPE_COMPOSE = 8,
    LOCK_TYPE_KANA = 16
};

// Runtime configuration storage
static uint8_t via_lock_led_1 = USR_LOCKLED_1;
static uint8_t via_lock_led_2 = USR_LOCKLED_2;
static uint8_t via_lock_led_3 = USR_LOCKLED_3;
static uint8_t via_lock_timeout = USR_LOCKLED_KEEPTIME / 100;
static uint8_t via_layerkey_show_lockled = 0;

// Compact pack/unpack helpers for 32-bit EEPROM storage
// Bit layout: [unused:11][layerkey_flag:1][timeout:7][lock_led_3:5][lock_led_2:5][lock_led_1:5]
static uint32_t pack_config(void) {
    return (uint32_t)(via_lock_led_1 & 0x1F) |           // 5 bits for led1 (0-16)
           ((uint32_t)(via_lock_led_2 & 0x1F) << 5) |    // 5 bits for led2
           ((uint32_t)(via_lock_led_3 & 0x1F) << 10) |   // 5 bits for led3
           ((uint32_t)(via_lock_timeout & 0x7F) << 15) | // 7 bits for timeout (1-100)
           ((uint32_t)(via_layerkey_show_lockled & 1) << 22); // 1 bit for flag
}

static void unpack_config(uint32_t packed) {
    via_lock_led_1 = (uint8_t)(packed & 0x1F);
    via_lock_led_2 = (uint8_t)((packed >> 5) & 0x1F);
    via_lock_led_3 = (uint8_t)((packed >> 10) & 0x1F);
    via_lock_timeout = (uint8_t)((packed >> 15) & 0x7F);
    via_layerkey_show_lockled = (uint8_t)((packed >> 22) & 1);
}

// Validation helpers
static bool is_valid_lock_led_value(uint8_t value) {
    return (value == 0 || value == 1 || value == 2 || value == 4 || value == 8 || value == 16);
}

static bool is_valid_timeout_value(uint8_t value) {
    return (value >= 1 && value <= 100);
}

// Individual save functions with validation and change detection
static bool save_lock_led_1(uint8_t new_value) {
    if (is_valid_lock_led_value(new_value) && via_lock_led_1 != new_value) {
        via_lock_led_1 = new_value;
        eeconfig_update_kb(pack_config());
        return true;
    }
    return false;
}

static bool save_lock_led_2(uint8_t new_value) {
    if (is_valid_lock_led_value(new_value) && via_lock_led_2 != new_value) {
        via_lock_led_2 = new_value;
        eeconfig_update_kb(pack_config());
        return true;
    }
    return false;
}

static bool save_lock_led_3(uint8_t new_value) {
    if (is_valid_lock_led_value(new_value) && via_lock_led_3 != new_value) {
        via_lock_led_3 = new_value;
        eeconfig_update_kb(pack_config());
        return true;
    }
    return false;
}

static bool save_lock_timeout(uint8_t new_value) {
    if (is_valid_timeout_value(new_value) && via_lock_timeout != new_value) {
        via_lock_timeout = new_value;
        eeconfig_update_kb(pack_config());
        return true;
    }
    return false;
}

static bool save_layerkey_show_lockled(uint8_t new_value) {
    if (via_layerkey_show_lockled != new_value) {
        via_layerkey_show_lockled = new_value;
        eeconfig_update_kb(pack_config());
        return true;
    }
    return false;
}

// Configuration valid flag
static bool config_loaded = false;

// Initialize VIA configuration from EEPROM using user datablock
void usr_via_config_init(void) {
    if (config_loaded) return;

    uint32_t stored_config = eeconfig_read_kb();
    unpack_config(stored_config);

    // Validate loaded config (handles both invalid data and first boot)
    if (!is_valid_lock_led_value(via_lock_led_1) || !is_valid_lock_led_value(via_lock_led_2) ||
        !is_valid_lock_led_value(via_lock_led_3) || !is_valid_timeout_value(via_lock_timeout)) {
        // Reset to defaults if invalid or first boot
        via_lock_led_1 = USR_LOCKLED_1;
        via_lock_led_2 = USR_LOCKLED_2;
        via_lock_led_3 = USR_LOCKLED_3;
        via_lock_timeout = USR_LOCKLED_KEEPTIME / 100;
        via_layerkey_show_lockled = 0;
        usr_via_config_save();
    }

    config_loaded = true;
}

void usr_via_config_save(void) {
    eeconfig_update_kb(pack_config());
}

uint8_t usr_via_get_lock_led_1(void) { return via_lock_led_1; }

uint8_t usr_via_get_lock_led_2(void) { return via_lock_led_2; }

uint8_t usr_via_get_lock_led_3(void) { return via_lock_led_3; }

uint8_t usr_via_get_lock_timeout(void) { return via_lock_timeout; }

bool usr_via_get_layerkey_show_lockled(void) { return via_layerkey_show_lockled != 0; }

bool usr_via_lock_system_enabled(void) {
    return (via_lock_led_1 | via_lock_led_2 | via_lock_led_3) > 0;
}

// VIA custom value command handler (VIA v3 protocol)
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
                    case LOCK_LED_1_CONFIG:
                        value_data[0] = via_lock_led_1;
                        break;
                    case LOCK_LED_2_CONFIG:
                        value_data[0] = via_lock_led_2;
                        break;
                    case LOCK_LED_3_CONFIG:
                        value_data[0] = via_lock_led_3;
                        break;
                    case LOCK_LED_TIMEOUT_CONFIG:
                        value_data[0] = via_lock_timeout;
                        break;
                    case LAYERKEY_SHOW_LOCKLED_CONFIG:
                        value_data[0] = via_layerkey_show_lockled;
                        break;
                    default:
                        *command_id = id_unhandled;
                        return;
                }
                break;
            }
            case id_custom_set_value: {
                uint8_t new_value = value_data[0];
                bool config_changed = false;

                switch (*value_id) {
                    case LOCK_LED_1_CONFIG:
                        config_changed = save_lock_led_1(new_value);
                        break;
                    case LOCK_LED_2_CONFIG:
                        config_changed = save_lock_led_2(new_value);
                        break;
                    case LOCK_LED_3_CONFIG:
                        config_changed = save_lock_led_3(new_value);
                        break;
                    case LOCK_LED_TIMEOUT_CONFIG:
                        config_changed = save_lock_timeout(new_value);
                        break;
                    case LAYERKEY_SHOW_LOCKLED_CONFIG:
                        config_changed = save_layerkey_show_lockled(new_value);
                        break;
                    default:
                        *command_id = id_unhandled;
                        return;
                }

                if (config_changed) {
                    // Trigger reconfiguration of lock system
                    usr_refresh_indicator();
                }
                break;
            }
            case id_custom_save: {
                usr_via_config_save();
                break;
            }
            default:
                *command_id = id_unhandled;
                return;
        }
        return; // Command handled successfully
    }

    // If we get here, the channel is not ours - mark as unhandled
    *command_id = id_unhandled;
}
