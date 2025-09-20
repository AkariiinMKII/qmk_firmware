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

// Safety checks
#if USR_RESET_COMBO_TIME < 1000 || USR_RESET_COMBO_TIME > 10000
#    warning "Reset combo hold time should be 1000-10000ms"
#endif

#if USR_CIALLO_COMBO_TIME < 500 || USR_CIALLO_COMBO_TIME > 10000
#    warning "Ciallo combo hold time should be 500-10000ms"
#endif

#ifndef USR_COMBO_DEFINITIONS
#    error "USR_COMBO_DEFINITIONS must be defined in usr_config.h"
#endif

// Temporarily disable this check to allow compilation
// TODO: Debug why KC_LSFT and KC_RSFT are being treated as equal
/*
#if USR_COMBO_MOD1 == USR_COMBO_MOD2
#    error "Combo modifier keys must be different"
#endif
*/

// Usage: Hold MOD1 + MOD2, then press action key
// Configure combos in usr_config.h

// Call this from process_record_user()
bool usr_combo_process(uint16_t keycode, bool pressed);

// Call this from matrix_scan_user()
void usr_combo_resolver(void);
