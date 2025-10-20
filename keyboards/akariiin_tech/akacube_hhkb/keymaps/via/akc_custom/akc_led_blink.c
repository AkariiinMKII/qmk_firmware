// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "akc_custom.h"

// Blink timing and state
static bool blink_active = false;
static bool blink_led_on = false;
static uint16_t blink_timer = 0;

// Show LED blink effect on LEDs 0-7
void akc_led_blink_show(void) {
    if (!blink_active) {
        blink_active = true;
        blink_led_on = true;
        blink_timer = timer_read();

        rgblight_set_layer_state(13, true);  // Background layer
        rgblight_set_layer_state(14, true);  // Blink color layer
    }
}

// Hide LED blink effect
void akc_led_blink_hide(void) {
    if (blink_active) {
        blink_active = false;
        blink_led_on = false;
        blink_timer = 0;

        rgblight_set_layer_state(13, false); // Background layer off
        rgblight_set_layer_state(14, false); // Blink color layer off
    }
}

// Handle blink timing
void akc_led_blink_timer(void) {
    uint16_t elapsed = timer_elapsed(blink_timer);
    uint16_t target_time = blink_led_on ? AKC_BLINK_TIME_ON : AKC_BLINK_TIME_IDLE;

    if (elapsed >= target_time) {
        blink_led_on = !blink_led_on;
        blink_timer = timer_read();

        rgblight_set_layer_state(14, blink_led_on);  // Toggle blink color layer
    }
}

// Check if blink timer is active
bool akc_led_blink_timer_active(void) { return blink_active; }
