// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "mnm_custom.h"

// Show lock indicators - black background if any enabled, color backgrounds if enabled, indicators if active
void mnm_lock_indicator_show(uint8_t lock_state) {
    uint8_t led0 = mnm_via_get_config(LOCK_LED_0, BITMASK);
    uint8_t led1 = mnm_via_get_config(LOCK_LED_1, BITMASK);

    // Color backgrounds (if specific lock LED is enabled)
    rgblight_set_layer_state(3, led0 > 0);   // Lock 0 color background
    rgblight_set_layer_state(4, led1 > 0);   // Lock 1 color background

    // Lock indicator colors (when lock state is active AND lock LED is enabled)
    rgblight_set_layer_state(5, (lock_state & led0) > 0);  // Lock 0 indicator
    rgblight_set_layer_state(6, (lock_state & led1) > 0);  // Lock 1 indicator
}

// Hide all lock indicators
void mnm_lock_indicator_hide(void) {
    for (uint8_t i = 3; i < 7; i++) {
        rgblight_set_layer_state(i, false);
    }
}
