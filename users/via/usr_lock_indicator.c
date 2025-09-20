// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_lock_indicator.h"

// ============================================================================
// LOCK INDICATOR DISPLAY FUNCTIONS
// ============================================================================

// Initialize lock indicator system
void lock_indicator_init(void) {
    // Nothing needed - RGB layers handled elsewhere
}

// Display lock indicators with background
void lock_indicator_show(bool num_lock, bool caps_lock, bool scroll_lock) {
    // Activate lock LED background
    rgblight_set_layer_state(USR_LAYER_LOCKLED_BG, true);

    // Set lock indicators based on their states
    rgblight_set_layer_state(USR_LAYER_LOCKLED_NUM, num_lock);
    rgblight_set_layer_state(USR_LAYER_LOCKLED_CAPS, caps_lock);
    rgblight_set_layer_state(USR_LAYER_LOCKLED_SCROLL, scroll_lock);
}

// Hide all lock indicators
void lock_indicator_hide(void) {
    // Turn off lock LED background
    rgblight_set_layer_state(USR_LAYER_LOCKLED_BG, false);

    // Turn off all lock indicators
    rgblight_set_layer_state(USR_LAYER_LOCKLED_NUM, false);
    rgblight_set_layer_state(USR_LAYER_LOCKLED_CAPS, false);
    rgblight_set_layer_state(USR_LAYER_LOCKLED_SCROLL, false);
}
