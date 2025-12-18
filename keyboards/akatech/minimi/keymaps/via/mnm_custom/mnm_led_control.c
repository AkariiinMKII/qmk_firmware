// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "mnm_custom.h"

// Lock LED state variables
static uint8_t lock_last_state = 0;
static bool lockled_timer_active = false;
static uint16_t lockled_timer = 0;

// Layer LED state variables
static layer_state_t layer_last_state = 0;

// Lock LED timer control functions
static void lock_indicator_timer_start(void) {
    lockled_timer_active = true;
    lockled_timer = timer_read();
}

static void lock_indicator_timer_reset(void) {
    lockled_timer_active = false;
    lockled_timer = 0;
}

void mnm_led_lock_indicator_timer(void) {
    if (timer_elapsed(lockled_timer) >= (mnm_via_get_led_timeout() * 100)) {
        lock_indicator_timer_reset();
        mnm_lock_indicator_hide();
    }
}

// Update lock indicators
void mnm_led_lock_indicator_update(led_t led_state) {
    if (!mnm_via_lock_system_enabled()) return;

    // Get current lock state for enabled LEDs
    uint8_t lock_current_mask = mnm_via_get_config(LOCK_LED_0, BITMASK) |
                               mnm_via_get_config(LOCK_LED_1, BITMASK);
    uint8_t lock_current_state = led_state.raw & lock_current_mask;

    // Only update if state changed
    if (lock_current_state != lock_last_state) {
        lock_last_state = lock_current_state;
        // Handle lock indicators override
        if (layer_state != default_layer_state && mnm_via_get_flag(OVERRIDE_LAYERLED)) {
            lock_indicator_timer_reset();  // Disable timer on upper layer for indicator override
        } else {
            lock_indicator_timer_start();  // Otherwise start timer
        }
        mnm_lock_indicator_show(lock_last_state);
    }
}

// Update layer indicators
void mnm_led_layer_indicator_update(layer_state_t state) {
    if (state != layer_last_state) {
        layer_last_state = state;  // Keep layer state cache up to date

        // Handle lock indicators override
        if (mnm_via_lock_system_enabled() && mnm_via_get_flag(OVERRIDE_LAYERLED)) {
            if (state != default_layer_state) {
                // Layer key down: show lock indicators without timeout
                lock_indicator_timer_reset();
            } else {
                // Layer key up: continue lock indicators for period of timeout
                lock_indicator_timer_start();
            }
            mnm_lock_indicator_show(lock_last_state);
        }

        // Update layer indicators
        mnm_layer_indicator_show(layer_last_state);
    }
}

// Refresh indicators on config change
void mnm_led_refresh_lockled(void) {
    lock_indicator_timer_reset();

    if (mnm_via_lock_system_enabled()) {
        lock_last_state = 0xFF; // Force trigger update
        mnm_led_lock_indicator_update(host_keyboard_led_state());
    } else {
        lock_last_state = 0;
        mnm_lock_indicator_hide();
    }
}

void mnm_led_refresh_layerled(void) {
    if (layer_state != default_layer_state) {
        lock_indicator_timer_reset();
        mnm_lock_indicator_hide();
        layer_last_state = 0xFF; // Force trigger update
        mnm_led_layer_indicator_update(layer_state);
    }
}

// Initialize RGB layers and refresh lock LEDs
void mnm_led_init_lockled(void) {
    lock_indicator_timer_reset();
    mnm_rgblight_layers_init();
    mnm_layer_indicator_show(layer_state);
    if (!mnm_via_lock_system_enabled()) return;
    if (layer_state == default_layer_state || !mnm_via_get_flag(OVERRIDE_LAYERLED)) {
        lock_indicator_timer_start();
    }
    mnm_lock_indicator_show(host_keyboard_led_state().raw);
}

// Initialize RGB layers and refresh layer LEDs
void mnm_led_init_layerled(void) {
    mnm_rgblight_layers_init();
    mnm_layer_indicator_show(layer_state);
    if (lockled_timer_active || (
            mnm_via_lock_system_enabled() &&
            mnm_via_get_flag(OVERRIDE_LAYERLED) &&
            layer_state != default_layer_state
        )) {
        mnm_lock_indicator_show(host_keyboard_led_state().raw);
    }
}

// Expose LED timers active state for matrix scan
bool mnm_led_lockled_timer_active(void) { return lockled_timer_active; }
