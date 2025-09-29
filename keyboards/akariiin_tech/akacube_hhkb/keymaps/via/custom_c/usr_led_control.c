// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_led_control.h"
#include "usr_layer_indicator.h"
#include "usr_lock_indicator.h"
#include "usr_via_config.h"

// Lock LED state variables
static uint8_t lock_last_state = 0;
static bool lockled_active = false;
static uint16_t lockled_timer = 0;

// Layer LED state variables
static layer_state_t layer_last_state = 0;

// Start timer
static void lock_indicator_timer_start(void) {
    lockled_active = true;
    lockled_timer = timer_read();
}

// Reset timer variables
static void lock_indicator_timer_reset(void) {
    lockled_active = false;
    lockled_timer = 0;
}

// Update lock indicators
void lock_indicator_update(led_t led_state) {
    if (!usr_via_lock_system_enabled()) return;

    // Get current lock state for enabled LEDs
    uint8_t lock_current_mask = usr_via_get_config(LOCK_LED_0, BITMASK) |
                               usr_via_get_config(LOCK_LED_1, BITMASK) |
                               usr_via_get_config(LOCK_LED_2, BITMASK);
    uint8_t lock_current_state = led_state.raw & lock_current_mask;

    // Only update if state changed
    if (lock_current_state != lock_last_state) {
        lock_last_state = lock_current_state;
        // Handle lock indicators override
        if (layer_state > 1 && usr_via_get_layerkey_show_lockled()) {
            lock_indicator_timer_reset();  // Disable timer on upper layer for indicator override
        } else {
            lock_indicator_timer_start();  // Otherwise start timer
        }
        lock_indicator_show(lock_last_state);
    }
}

// Handle lock indicator timeout
void lock_indicator_timer(void) {
    if (lockled_active && timer_elapsed(lockled_timer) >= (usr_via_get_lock_timeout() * 100)) {
        lock_indicator_timer_reset();
        lock_indicator_hide();
    }
}

// Update layer indicators
void layer_indicator_update(layer_state_t state) {
    if (state != layer_last_state) {
        layer_last_state = state;  // Keep layer state cache up to date

        // Handle lock indicators override
        if (usr_via_lock_system_enabled() && usr_via_get_layerkey_show_lockled()) {
            if (state > 1) {
                // Layer key down: show lock indicators without timeout
                lock_indicator_timer_reset();
            } else {
                // Layer key up: continue lock indicators for period of timeout
                lock_indicator_timer_start();
            }
            lock_indicator_show(lock_last_state);
        }
        // Update layer indicators even if in background
        layer_indicator_show(layer_last_state);
    }
}

// Refresh indicators on config change
void usr_refresh_lockled(void) {
    lock_indicator_timer_reset();
    if (usr_via_lock_system_enabled()) {
        lock_last_state = 0xFF; // Force trigger update
        lock_indicator_update(host_keyboard_led_state());
    } else {
        lock_last_state = 0;
        lock_indicator_hide();
        layer_last_state = layer_state;
        layer_indicator_show(layer_last_state);
    }
}

void usr_refresh_layerled(uint8_t flag) {
    layer_indicator_hide();
    if (flag && layer_state > 1 && usr_via_lock_system_enabled()) {
        usr_refresh_lockled();
    } else {
        if (!lockled_active) {
            lock_indicator_timer_reset();
            lock_indicator_hide();
        }
        layer_last_state = layer_state;
        layer_indicator_show(layer_last_state);
    }
}
