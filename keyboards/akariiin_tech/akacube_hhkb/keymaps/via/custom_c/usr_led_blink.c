// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_led_blink.h"

// Blink timing and state
static bool blink_active = false;
static bool blink_led_on = false;
static uint16_t blink_timer = 0;

// Show LED blink effect on LEDs 0-7
void led_blink_show(void) {
    if (!blink_active) {
        blink_active = true;
        blink_led_on = true;
        blink_timer = timer_read();

        rgblight_set_layer_state(12, true);  // Background layer
        rgblight_set_layer_state(13, true);  // Color layer
    }
}

// Hide LED blink effect
void led_blink_hide(void) {
    if (blink_active) {
        blink_active = false;
        blink_led_on = false;
        blink_timer = 0;

        rgblight_set_layer_state(12, false); // Background layer off
        rgblight_set_layer_state(13, false); // Color layer off
    }
}

// Handle blink timing
void led_blink_timer(void) {
    if (!blink_active) return;

    uint16_t elapsed = timer_elapsed(blink_timer);
    uint16_t target_time = blink_led_on ? USR_BLINK_TIME_ON : USR_BLINK_TIME_IDLE;

    if (elapsed >= target_time) {
        blink_led_on = !blink_led_on;
        blink_timer = timer_read();

        rgblight_set_layer_state(13, blink_led_on);  // Toggle color layer
    }
}
