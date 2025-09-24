// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_lock_indicator.h"

// Display lock indicators with background
void lock_indicator_show(bool num_lock, bool caps_lock, bool scroll_lock) {
    // Activate lock LED background
    rgblight_set_layer_state(5, true);  // Lock background

    // Set lock indicators based on their states
    rgblight_set_layer_state(6, num_lock);     // Num lock
    rgblight_set_layer_state(7, caps_lock);    // Caps lock
    rgblight_set_layer_state(8, scroll_lock);  // Scroll lock
}

// Hide all lock indicators
void lock_indicator_hide(void) {
    // Turn off lock LED background
    rgblight_set_layer_state(5, false);  // Lock background

    // Turn off all lock indicators
    rgblight_set_layer_state(6, false);  // Num lock
    rgblight_set_layer_state(7, false);  // Caps lock
    rgblight_set_layer_state(8, false);  // Scroll lock
}
