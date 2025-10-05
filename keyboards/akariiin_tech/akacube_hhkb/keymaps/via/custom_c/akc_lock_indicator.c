// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "akc_lock_indicator.h"
#include "akc_via_config.h"

// Show lock indicators - black background if any enabled, color backgrounds if enabled, indicators if active
void akc_lock_indicator_show(uint8_t lock_state) {
    uint8_t led0 = akc_via_get_config(LOCK_LED_0, BITMASK);
    uint8_t led1 = akc_via_get_config(LOCK_LED_1, BITMASK);
    uint8_t led2 = akc_via_get_config(LOCK_LED_2, BITMASK);

    // All-black background (if any lock LED is enabled)
    rgblight_set_layer_state(5, (led0 | led1 | led2) > 0);

    // Color backgrounds (if specific lock LED is enabled)
    rgblight_set_layer_state(6, led0 > 0);   // Lock 0 color background
    rgblight_set_layer_state(7, led1 > 0);   // Lock 1 color background
    rgblight_set_layer_state(8, led2 > 0);   // Lock 2 color background

    // Lock indicator colors (when lock state is active AND lock LED is enabled)
    rgblight_set_layer_state(9, (lock_state & led0) > 0);   // Lock 0 indicator
    rgblight_set_layer_state(10, (lock_state & led1) > 0);  // Lock 1 indicator
    rgblight_set_layer_state(11, (lock_state & led2) > 0);  // Lock 2 indicator
}

// Hide all lock indicators
void akc_lock_indicator_hide(void) {
    rgblight_set_layer_state(5, false);   // All-black background
    rgblight_set_layer_state(6, false);   // Lock 0 color background
    rgblight_set_layer_state(7, false);   // Lock 1 color background
    rgblight_set_layer_state(8, false);   // Lock 2 color background
    rgblight_set_layer_state(9, false);   // Lock 0 indicator
    rgblight_set_layer_state(10, false);  // Lock 1 indicator
    rgblight_set_layer_state(11, false);  // Lock 2 indicator
}
