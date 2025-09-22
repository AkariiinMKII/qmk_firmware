// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

// Simple combo system: two modifier keys + one action key

#pragma once

#include "quantum.h"
#include "usr_config.h"

// Configuration fallbacks
#ifndef USR_COMBO_MOD1
#    define USR_COMBO_MOD1 KC_LSFT
#endif
#ifndef USR_COMBO_MOD2
#    define USR_COMBO_MOD2 KC_RSFT
#endif

#ifndef USR_RESET_COMBO_TIME
#    define USR_RESET_COMBO_TIME 5000
#endif

#ifndef USR_CIALLO_COMBO_TIME
#    define USR_CIALLO_COMBO_TIME 5000
#endif

// Usage: Hold MOD1 + MOD2, then press action key
// Configure combos in usr_config.h

// Call this from process_record_user()
bool usr_combo_check(uint16_t keycode, bool pressed);

// Call this from matrix_scan_user()
void usr_combo_handler(void);
