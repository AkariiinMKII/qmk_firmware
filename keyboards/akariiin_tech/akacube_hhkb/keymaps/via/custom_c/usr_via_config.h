// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "via.h"

#define disable     0
#define numlock     1
#define capslock    2
#define scrolllock  4
#define compose     8
#define kana        16

// Configuration matrix row indices
enum config_rows {
    LOCK_LED_0 = 0,
    LOCK_LED_1 = 1,
    LOCK_LED_2 = 2,
    LAYER_LED = 3
};

// Configuration matrix column indices
enum config_cols {
    BITMASK = 0,
    OFF_COLOR = 1,
    ON_COLOR = 2
};

void usr_via_config_init(void);
void usr_via_config_save(void);

// Generic config access - matrix[row][col]
uint8_t usr_via_get_config(uint8_t row, uint8_t col);

// Special getters for packed values
uint8_t usr_via_get_lock_timeout(void);
bool usr_via_get_layerkey_show_lockled(void);

// Helper functions
bool usr_via_lock_system_enabled(void);

// Callback for when config changes (implemented in usr_led_control.c)
void usr_refresh_indicator(void);

// VIA command handler
void via_custom_value_command_kb(uint8_t *data, uint8_t length);
