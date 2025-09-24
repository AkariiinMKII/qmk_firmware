// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_lock_indicator.h"
#include "usr_led_control.h"

// Show lock indicators with bit checks
void lock_indicator_show(uint8_t lock_state) {
    rgblight_set_layer_state(5, true);                              // Background
    rgblight_set_layer_state(6, (lock_state & USR_LOCKLED_1) > 0);  // Lock 1
    rgblight_set_layer_state(7, (lock_state & USR_LOCKLED_2) > 0);  // Lock 2
    rgblight_set_layer_state(8, (lock_state & USR_LOCKLED_3) > 0);  // Lock 3
}

// Hide all lock indicators
void lock_indicator_hide(void) {
    rgblight_set_layer_state(5, false);  // Background
    rgblight_set_layer_state(6, false);  // Lock 1
    rgblight_set_layer_state(7, false);  // Lock 2
    rgblight_set_layer_state(8, false);  // Lock 3
}
