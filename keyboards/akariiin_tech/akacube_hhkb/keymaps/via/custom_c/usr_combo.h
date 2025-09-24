// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "usr_config.h"
#include "usr_led_blink.h"

// Configuration fallbacks
#ifndef USR_COMBO_MOD1
#    define USR_COMBO_MOD1 KC_LSFT
#endif
#ifndef USR_COMBO_MOD2
#    define USR_COMBO_MOD2 KC_RSFT
#endif

bool usr_combo_check(uint16_t keycode, bool pressed);
void usr_combo_handler(void);
bool usr_combo_any_active(void);
