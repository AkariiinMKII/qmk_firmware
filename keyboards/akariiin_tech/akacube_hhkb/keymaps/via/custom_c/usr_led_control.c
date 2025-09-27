// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_led_control.h"
#include "usr_layer_indicator.h"
#include "usr_lock_indicator.h"
#include "usr_via_config.h"

// Lock state management - moved from usr_lock_indicator.c  
// Single bitmask cache for all lock states
static uint8_t lock_last_state = 0;

static bool lockled_active = false;
static uint16_t lockled_timer = 0;

// Flag to indicate lock indicator timeout occurred (used in normal mode)
static bool lockled_timeouted = false;

// Lock LED Functions

// Update lock indicators when state changes
void lock_indicator_update(led_t led_state) {
    if (!usr_via_lock_system_enabled()) return;
    
    // Get current lock state bitmask for enabled LEDs - using hardcoded indices
    uint8_t lock_current_state = led_state.raw & (usr_via_get_config(0, 0) | usr_via_get_config(1, 0) | usr_via_get_config(2, 0));

    // Only update if state changed
    if (lock_current_state != lock_last_state) {
        lock_last_state = lock_current_state;
        if (usr_via_get_layerkey_show_lockled()) {
            // Only start timer when on base layer (not when layer key is held)
            if (layer_state > 1) {
                lockled_active = false;  // Disable timer while layer active
                lockled_timer = 0;
            } else {
                lockled_active = true;   // Start timer on base layer
                lockled_timer = timer_read();
            }
        } else {
            // Normal mode: always start timer when lock state changes
            lockled_active = true;
            lockled_timer = timer_read();
        }
        lock_indicator_show(lock_last_state);
    }
}

// Handle lock indicator timeout - hide indicators after configured timeout
void lock_indicator_timer(layer_state_t state) {
    if (!usr_via_lock_system_enabled()) return;
    
    if (lockled_active && timer_elapsed(lockled_timer) >= (usr_via_get_lock_timeout() * 100)) {
        lockled_active = false;
        lockled_timer = 0;
        lock_indicator_hide();

        if (!usr_via_get_layerkey_show_lockled()) {
            // Set flag to trigger layer update in normal mode
            lockled_timeouted = true;
        }
    }
}

// Layer LED Functions

// Cached layer state for comparison
static layer_state_t layer_last_state = 0;

// Update layer indicators
void layer_indicator_update(layer_state_t state) {
    if (usr_via_lock_system_enabled()) {
        if (usr_via_get_layerkey_show_lockled()) {
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
        } else {
            // Normal mode: use timeout flag to trigger updates after timer expires
            if (state != layer_last_state || lockled_timeouted) {
                lockled_timeouted = false;  // Clear timeout flag
                layer_last_state = state;
                layer_indicator_show(state);       // Show layer indicators
            }
        }
    } else {
        // No locks enabled: always show layer indicators
        if (state != layer_last_state) {
            layer_last_state = state;
            layer_indicator_show(state);
        }
    }
}

// Refresh all indicators (called when VIA configuration changes)
void usr_refresh_indicator(void) {
    if (usr_via_lock_system_enabled()) {
        // Reset lock system state when configuration changes
        lockled_active = false;
        lockled_timer = 0;
        lock_last_state = 0;
        lockled_timeouted = false;
        // Hide all current indicators
        lock_indicator_hide();
    }
    // Reset layer state cache to force refresh in next scan
    layer_last_state = 0;
}
