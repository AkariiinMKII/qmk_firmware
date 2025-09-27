// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_lock_indicator.h"
#include "usr_led_control.h"
#include "usr_via_config.h"

// Show lock indicators - black background if any enabled, color backgrounds if enabled, indicators if active
void lock_indicator_show(uint8_t lock_state) {
    uint8_t led0 = usr_via_get_config(0, 0);  // Lock LED 0 bitmask (row 0, col 0)
    uint8_t led1 = usr_via_get_config(1, 0);  // Lock LED 1 bitmask (row 1, col 0)
    uint8_t led2 = usr_via_get_config(2, 0);  // Lock LED 2 bitmask (row 2, col 0)

    // All-black background (if any lock LED is enabled)
    rgblight_set_layer_state(5, (led0 | led1 | led2) > 0);  // RGB layer 5

    // Color backgrounds (if specific lock LED is enabled)
    rgblight_set_layer_state(6, led0 > 0);   // RGB layer 6: Lock 0 color background
    rgblight_set_layer_state(7, led1 > 0);   // RGB layer 7: Lock 1 color background
    rgblight_set_layer_state(8, led2 > 0);   // RGB layer 8: Lock 2 color background

    // Lock indicator colors (when lock state is active AND lock LED is enabled)
    rgblight_set_layer_state(9, (lock_state & led0) > 0);   // RGB layer 9: Lock 0 indicator
    rgblight_set_layer_state(10, (lock_state & led1) > 0);  // RGB layer 10: Lock 1 indicator
    rgblight_set_layer_state(11, (lock_state & led2) > 0);  // RGB layer 11: Lock 2 indicator
}

// Hide all lock indicators - using hardcoded indices
void lock_indicator_hide(void) {
    // All lock LED layers
    rgblight_set_layer_state(5, false);   // RGB layer 5: All-black background
    rgblight_set_layer_state(6, false);   // RGB layer 6: Lock 0 color background
    rgblight_set_layer_state(7, false);   // RGB layer 7: Lock 1 color background
    rgblight_set_layer_state(8, false);   // RGB layer 8: Lock 2 color background
    rgblight_set_layer_state(9, false);   // RGB layer 9: Lock 0 indicator
    rgblight_set_layer_state(10, false);  // RGB layer 10: Lock 1 indicator
    rgblight_set_layer_state(11, false);  // RGB layer 11: Lock 2 indicator
}
