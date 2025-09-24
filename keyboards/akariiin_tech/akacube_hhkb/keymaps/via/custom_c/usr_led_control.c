// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_led_control.h"
#include "usr_layer_indicator.h"
#include "usr_lock_indicator.h"

#if (USR_LOCKLED_1 + USR_LOCKLED_2 + USR_LOCKLED_3) > 0
// Lock state management - moved from usr_lock_indicator.c
// Single bitmask cache for all lock states
static uint8_t lock_last_state = 0;

static bool lockled_active = false;
static uint16_t lockled_timer = 0;

#ifndef LAYER_KEY_SHOW_LOCK_INDICATORS
// Flag to indicate lock indicator timeout occurred (only used when LAYER_KEY_SHOW_LOCK_INDICATORS is not defined)
static bool lockled_timeouted = false;
#endif

// Lock LED Functions

// Update lock indicators when state changes
void lock_indicator_update(led_t led_state) {
    // Get current lock state bitmask for enabled LEDs
    uint8_t lock_current_state = led_state.raw & (USR_LOCKLED_1 + USR_LOCKLED_2 + USR_LOCKLED_3);

    // Only update if state changed
    if (lock_current_state != lock_last_state) {
        lock_last_state = lock_current_state;
#ifdef LAYER_KEY_SHOW_LOCK_INDICATORS
        // Only start timer when on base layer (not when layer key is held)
        if (layer_state > 1) {
            lockled_active = false;  // Disable timer while layer active
            lockled_timer = 0;
        } else {
            lockled_active = true;   // Start timer on base layer
            lockled_timer = timer_read();
        }
#else
        // Normal mode: always start timer when lock state changes
        lockled_active = true;
        lockled_timer = timer_read();
#endif
        lock_indicator_show(lock_last_state);
    }
}

// Handle lock indicator timeout - hide indicators after USR_LOCKLED_KEEPTIME
void lock_indicator_timer(layer_state_t state) {
    if (lockled_active && timer_elapsed(lockled_timer) >= USR_LOCKLED_KEEPTIME) {
        lockled_active = false;
        lockled_timer = 0;
        lock_indicator_hide();

#ifndef LAYER_KEY_SHOW_LOCK_INDICATORS
        // Set flag to trigger layer update in normal mode
        lockled_timeouted = true;
#endif
    }
}
#endif

// Layer LED Functions

// Cached layer state for comparison
static layer_state_t layer_last_state = 0;

// Update layer indicators
void layer_indicator_update(layer_state_t state) {
#if (USR_LOCKLED_1 + USR_LOCKLED_2 + USR_LOCKLED_3) > 0
#ifdef LAYER_KEY_SHOW_LOCK_INDICATORS
    if (state != layer_last_state) {
        layer_last_state = state;
        if (state > 1) {
            // Layer key held: disable timer, keep indicators on indefinitely
            lockled_active = false;
            lockled_timer = 0;
        } else {
            // Layer key released: start fresh timer for full timeout period
            lockled_active = true;
            lockled_timer = timer_read();
        }
        // Always show lock indicators
        lock_indicator_show(lock_last_state);
    }
#else
    // Normal mode: use timeout flag to trigger updates after timer expires
    if (state != layer_last_state || lockled_timeouted) {
        lockled_timeouted = false;  // Clear timeout flag
        layer_last_state = state;
        layer_indicator_show(state);       // Show layer indicators
    }
#endif
#else
    // No locks enabled: always show layer indicators
    if (state != layer_last_state) {
        layer_last_state = state;
        layer_indicator_show(state);
    }
#endif
}
