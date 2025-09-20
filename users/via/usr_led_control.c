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

// Flag to indicate lock indicator timeout occurred
static bool lock_indicator_timeouted = false;

// Initialize LED control systems
void usr_led_control_init(void) {
    // Initialize LED systems
    layer_indicator_init();
    lock_indicator_init();
}

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
        // Don't start timer if layer is already active
        if (layer_state > 1) {
            lock_indicator_state.active = false;  // No timer when layer active
        } else {
            lock_indicator_state.active = true;   // Normal timer when on base layer
            lock_indicator_state.timer = timer_read();
        }
#else
        // Normal behavior - always start timer
        lock_indicator_state.active = true;
        lock_indicator_state.timer = timer_read();
#endif
        lock_indicator_show(led_state.num_lock, led_state.caps_lock, led_state.scroll_lock);
    }
}

// Handle lock indicator timeout
void lock_indicator_timer(layer_state_t state) {
    // Check timeout
    if (lock_indicator_state.active && timer_elapsed(lock_indicator_state.timer) >= USR_LOCK_LED_TIME) {
        lock_indicator_state.active = false;

        // Hide locks, set flag for layer refresh
        lock_indicator_hide();
        lock_indicator_timeouted = true;
    }
}

// Layer LED Functions

// Cached layer state for comparison
static layer_state_t layer_last_state = 0;

// Update layer indicators
void layer_indicator_update(layer_state_t state) {
    // Show if state changed or lock timed out
    if (state != layer_last_state || lock_indicator_timeouted) {
        layer_last_state = state;          // Cache current state
        lock_indicator_timeouted = false;  // Clear timeout flag
#ifdef LAYER_KEY_SHOW_LOCK_INDICATORS
            if (state > 1) {  // If any layer other than base is active
                lock_indicator_show(lock_last_state.num_lock, lock_last_state.caps_lock, lock_last_state.scroll_lock);  // Show lock indicators
                // Disable timer to keep locks visible while layer is active
                lock_indicator_state.active = false;
            } else {
                lock_indicator_hide();  // Hide lock indicators
            }
#else
            layer_indicator_show(state);       // Refresh layer indicators
#endif
    }
}
