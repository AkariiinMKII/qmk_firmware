// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "mnm_custom.h"

// Blink timing and state
static bool blink_active = false;
static bool blink_led_on = false;
static uint16_t blink_timer = 0;

// Show LED blink effect
void mnm_led_blink_show(void) {
    if (!blink_active) {
        blink_active = true;
        blink_led_on = true;
        blink_timer = timer_read();

        rgblight_set_layer_state(7, true);  // Background layer
        rgblight_set_layer_state(8, true);  // Blink color layer
    }
}

// Hide LED blink effect
void mnm_led_blink_hide(void) {
    if (blink_active) {
        blink_active = false;
        blink_led_on = false;
        blink_timer = 0;

        rgblight_set_layer_state(7, false); // Background layer off
        rgblight_set_layer_state(8, false); // Blink color layer off
    }
}

// Handle blink timing
void mnm_led_blink_timer(void) {
    uint16_t elapsed = timer_elapsed(blink_timer);
    uint16_t target_time = blink_led_on ? MNM_BLINK_TIME_ON : MNM_BLINK_TIME_IDLE;

    if (elapsed >= target_time) {
        blink_led_on = !blink_led_on;
        blink_timer = timer_read();

        rgblight_set_layer_state(8, blink_led_on);  // Toggle blink color layer
    }
}

// Check if blink timer is active
bool mnm_led_blink_timer_active(void) { return blink_active; }
