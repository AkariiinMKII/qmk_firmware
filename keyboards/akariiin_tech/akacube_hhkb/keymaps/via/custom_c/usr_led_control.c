// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_led_control.h"
#include "usr_layer_indicator.h"
#include "usr_lock_indicator.h"

// ============================================================================
// LED CONTROL - COORDINATES LOCK AND LAYER INDICATORS
// ============================================================================

// Lock state management - moved from usr_lock_indicator.c
static struct {
    bool num_lock;
    bool caps_lock;
    bool scroll_lock;
} lock_last_state = {false, false, false};

static struct {
    bool active;
    uint16_t timer;
} lock_indicator_state = {false, 0};

#ifndef LAYER_KEY_SHOW_LOCK_INDICATORS
// Flag to indicate lock indicator timeout occurred (only used when LAYER_KEY_SHOW_LOCK_INDICATORS is not defined)
static bool lock_indicator_timeouted = false;
#endif

// Lock LED Functions

// Update lock indicators when state changes
void lock_indicator_update(led_t led_state) {
    // Check if any lock state changed
    if (led_state.num_lock != lock_last_state.num_lock ||
        led_state.caps_lock != lock_last_state.caps_lock ||
        led_state.scroll_lock != lock_last_state.scroll_lock) {

        // Update cached states
        lock_last_state.num_lock = led_state.num_lock;
        lock_last_state.caps_lock = led_state.caps_lock;
        lock_last_state.scroll_lock = led_state.scroll_lock;

#ifdef LAYER_KEY_SHOW_LOCK_INDICATORS
        // Only start timer when on base layer (not when layer key is held)
        if (layer_state > 1) {
            lock_indicator_state.active = false;  // Disable timer while layer active
        } else {
            lock_indicator_state.active = true;   // Start timer on base layer
            lock_indicator_state.timer = timer_read();
        }
#else
        // Normal mode: always start timer when lock state changes
        lock_indicator_state.active = true;
        lock_indicator_state.timer = timer_read();
#endif
        lock_indicator_show(led_state.num_lock, led_state.caps_lock, led_state.scroll_lock);
    }
}

// Handle lock indicator timeout - hide indicators after USR_LOCKLED_KEEPTIME
void lock_indicator_timer(layer_state_t state) {
    if (lock_indicator_state.active && timer_elapsed(lock_indicator_state.timer) >= USR_LOCKLED_KEEPTIME) {
        lock_indicator_state.active = false;
        lock_indicator_hide();

#ifndef LAYER_KEY_SHOW_LOCK_INDICATORS
        // Set flag to trigger layer update in normal mode
        lock_indicator_timeouted = true;
#endif
    }
}

// Layer LED Functions

// Cached layer state for comparison
static layer_state_t layer_last_state = 0;

// Update layer indicators
void layer_indicator_update(layer_state_t state) {
#ifdef LAYER_KEY_SHOW_LOCK_INDICATORS
    if (state != layer_last_state) {
        if (state > 1) {
            // Layer key held: disable timer, keep indicators on indefinitely
            lock_indicator_state.active = false;
        } else {
            // Layer key released: start fresh timer for full timeout period
            lock_indicator_state.active = true;
            lock_indicator_state.timer = timer_read();
        }
        // Always show lock indicators (regardless of actual lock states)
        lock_indicator_show(lock_last_state.num_lock, lock_last_state.caps_lock, lock_last_state.scroll_lock);
#else
    // Normal mode: use timeout flag to trigger updates after timer expires
    if (state != layer_last_state || lock_indicator_timeouted) {
        lock_indicator_timeouted = false;  // Clear timeout flag
        layer_indicator_show(state);       // Show layer indicators
#endif
        layer_last_state = state;          // Cache current state
    }
}
