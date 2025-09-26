// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_lock_indicator.h"
#include "usr_led_control.h"
#include "usr_via_config.h"

// Show lock indicators - black background if any enabled, color backgrounds if enabled, indicators if active
void lock_indicator_show(uint8_t lock_state) {
    uint8_t led1 = usr_via_get_lock_led_1();
    uint8_t led2 = usr_via_get_lock_led_2();
    uint8_t led3 = usr_via_get_lock_led_3();

    // All-black background (if any lock LED is enabled)
    rgblight_set_layer_state(5, (led1 | led2 | led3) > 0);

    // Color backgrounds (if specific lock LED is enabled)
    rgblight_set_layer_state(6, led1 > 0);  // Lock 1 color background
    rgblight_set_layer_state(7, led2 > 0);  // Lock 2 color background
    rgblight_set_layer_state(8, led3 > 0);  // Lock 3 color background

    // Lock indicator colors (when lock state is active AND lock LED is enabled)
    rgblight_set_layer_state(9, (lock_state & led1) > 0);   // Lock 1 indicator
    rgblight_set_layer_state(10, (lock_state & led2) > 0);  // Lock 2 indicator
    rgblight_set_layer_state(11, (lock_state & led3) > 0);  // Lock 3 indicator
}

// Hide all lock indicators
void lock_indicator_hide(void) {
    // All lock LED layers
    rgblight_set_layer_state(5, false);   // All-black background
    rgblight_set_layer_state(6, false);   // Lock 1 color background
    rgblight_set_layer_state(7, false);   // Lock 2 color background
    rgblight_set_layer_state(8, false);   // Lock 3 color background
    rgblight_set_layer_state(9, false);   // Lock 1 indicator
    rgblight_set_layer_state(10, false);  // Lock 2 indicator
    rgblight_set_layer_state(11, false);  // Lock 3 indicator
}
