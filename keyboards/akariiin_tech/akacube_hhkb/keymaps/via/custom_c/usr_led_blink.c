// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_led_blink.h"

// ============================================================================
// LED BLINK CONTROL FUNCTIONS
// ============================================================================

// Blink state management
static struct {
    bool active;        // Blink active
    bool led_on;        // LED state
    uint16_t timer;     // Timer
    uint8_t ref_count;  // Reference count for multiple combos
} blink_state = {false, false, 0, 0};


// Show LED blink effect on LEDs 0-7
static void check_ref_count(void) {
    if (blink_state.ref_count >= 16) {
        // Abnormal value detected - force reset
        blink_state.active = false;
        blink_state.led_on = false;
        blink_state.timer = 0;
        blink_state.ref_count = 0;
        rgblight_set_layer_state(9, false);
        rgblight_set_layer_state(10, false);
    }
}

// Show LED blink effect on LEDs 0-7
void led_blink_show(void) {
    check_ref_count();
    blink_state.ref_count++;

    if (!blink_state.active) {
        blink_state.active = true;
        blink_state.led_on = true;
        blink_state.timer = timer_read();

        rgblight_set_layer_state(9, true);   // Background layer initial
        rgblight_set_layer_state(10, true);  // Color layer initial
    }
}

// Hide LED blink effect
void led_blink_hide(void) {
    check_ref_count();

    if (blink_state.ref_count > 0) {
        blink_state.ref_count--;
    }

    if (blink_state.ref_count == 0) {
        blink_state.active = false;
        blink_state.led_on = false;
        blink_state.timer = 0;

        rgblight_set_layer_state(9, false);  // Background layer off
        rgblight_set_layer_state(10, false); // Color layer off
    }
}

// Handle blink timing
void led_blink_timer(void) {
    check_ref_count();

    if (!blink_state.active) return;

    uint16_t elapsed = timer_elapsed(blink_state.timer);
    uint16_t target_time = blink_state.led_on ? USR_BLINK_TIME_ON : USR_BLINK_TIME_IDLE;

    if (elapsed >= target_time) {
        blink_state.led_on = !blink_state.led_on;
        blink_state.timer = timer_read();

        rgblight_set_layer_state(10, blink_state.led_on);  // Toggle color layer
    }
}
