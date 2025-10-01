// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "via.h"

enum config_rows {
    LOCK_LED_0 = 0,
    LOCK_LED_1 = 1,
    LOCK_LED_2 = 2,
    LAYER_LED = 3
};

enum config_cols {
    BITMASK = 0,
    OFF_COLOR = 1,
    ON_COLOR = 2
};

void usr_via_config_init(void);
void usr_via_config_save(void);
uint8_t usr_via_get_config(uint8_t row, uint8_t col);
uint8_t usr_via_get_led_timeout(void);
bool usr_via_get_layerkey_show_lockled(void);
bool usr_via_lock_system_enabled(void);
void usr_refresh_lockled(void);
void usr_refresh_layerled(void);
void via_custom_value_command_kb(uint8_t *data, uint8_t length);
