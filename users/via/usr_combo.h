// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

// Combo key sequences (LShift + RShift + key)

#pragma once

#include "quantum.h"
#include "usr_config.h"

// Configurable combos: LShift + RShift + key
// RESET_COMBO_KEY: Reset key (default: KC_R, 5000ms)
// EASTER_EGG_KEY: Easter egg key (default: KC_C, 3000ms)

// Process key events for combo detection
// Returns false to suppress key when combo is active
bool usr_combo_process(uint16_t keycode, bool pressed);

// Update combo states (call from matrix_scan_user)
bool usr_combo_scan(void);
