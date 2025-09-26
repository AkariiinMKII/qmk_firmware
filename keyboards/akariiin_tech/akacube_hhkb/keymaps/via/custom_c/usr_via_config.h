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

void usr_via_config_init(void);
void usr_via_config_save(void);
uint8_t usr_via_get_lock_led_1(void);
uint8_t usr_via_get_lock_led_2(void);
uint8_t usr_via_get_lock_led_3(void);
uint8_t usr_via_get_lock_timeout(void);
bool usr_via_get_layerkey_show_lockled(void);
bool usr_via_lock_system_enabled(void);

// Callback for when config changes (implemented in usr_led_control.c)
void usr_refresh_indicator(void);

// VIA command handler
void via_custom_value_command_kb(uint8_t *data, uint8_t length);
