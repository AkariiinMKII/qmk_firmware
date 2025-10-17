// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "akc_custom.h"

// Lock LED state variables
static uint8_t lock_last_state = 0;
static bool lockled_active = false;
static uint16_t lockled_timer = 0;

// Layer LED state variables
static layer_state_t layer_last_state = 0;
static bool layerled_active = false;
static uint16_t layerled_timer = 0;

// Lock LED timer control functions
static void lock_indicator_timer_start(void) {
    lockled_active = true;
    lockled_timer = timer_read();
}

static void lock_indicator_timer_reset(void) {
    lockled_active = false;
    lockled_timer = 0;
}

void akc_led_lock_indicator_timer(void) {
    if (timer_elapsed(lockled_timer) >= (akc_via_get_led_timeout() * 100)) {
        lock_indicator_timer_reset();
        akc_lock_indicator_hide();
    }
}

// Layer LED timer control functions
static void layer_indicator_timer_start(void) {
    layerled_active = true;
    layerled_timer = timer_read();
}

static void layer_indicator_timer_reset(void) {
    layerled_active = false;
    layerled_timer = 0;
}

void akc_led_layer_indicator_timer(void) {
    if (timer_elapsed(layerled_timer) >= (akc_via_get_led_timeout() * 100)) {
        layer_indicator_timer_reset();
        akc_layer_indicator_hide();
    }
}

// Update lock indicators
void akc_led_lock_indicator_update(led_t led_state) {
    if (!akc_via_lock_system_enabled()) return;

    // Get current lock state for enabled LEDs
    uint8_t lock_current_mask = akc_via_get_config(LOCK_LED_0, BITMASK) |
                               akc_via_get_config(LOCK_LED_1, BITMASK) |
                               akc_via_get_config(LOCK_LED_2, BITMASK);
    uint8_t lock_current_state = led_state.raw & lock_current_mask;

    // Only update if state changed
    if (lock_current_state != lock_last_state) {
        lock_last_state = lock_current_state;
        // Handle lock indicators override
        if (layer_state != default_layer_state && akc_via_layerkey_show_lockled_enabled()) {
            lock_indicator_timer_reset();  // Disable timer on upper layer for indicator override
        } else {
            lock_indicator_timer_start();  // Otherwise start timer
        }
        akc_lock_indicator_show(lock_last_state);
    }
}

// Update layer indicators
void akc_led_layer_indicator_update(layer_state_t state) {
    if (state != layer_last_state) {
        layer_last_state = state;  // Keep layer state cache up to date

        // Handle lock indicators override
        if (akc_via_lock_system_enabled() && akc_via_layerkey_show_lockled_enabled()) {
            if (state != default_layer_state) {
                // Layer key down: show lock indicators without timeout
                lock_indicator_timer_reset();
            } else {
                // Layer key up: continue lock indicators for period of timeout
                lock_indicator_timer_start();
            }
            akc_lock_indicator_show(lock_last_state);
        }
        // Update layer indicators even if in background
        if (state != default_layer_state) {
            layer_indicator_timer_reset();
        } else {
            layer_indicator_timer_start();
        }
        akc_layer_indicator_show(layer_last_state);
    }
}

// Switch active indicators
static void switch_layerled_to_lockled(void) {
    if (layerled_active) {
        lockled_active = true;
        lockled_timer = layerled_timer; // Transfer remaining time
        layer_indicator_timer_reset();
        akc_layer_indicator_hide();
        akc_lock_indicator_show(lock_last_state);
    }
}

static void switch_lockled_to_layerled(void) {
    if (lockled_active) {
        layerled_active = true;
        layerled_timer = lockled_timer; // Transfer remaining time
        lock_indicator_timer_reset();
        akc_lock_indicator_hide();
        akc_layer_indicator_show(layer_last_state);
    }
}

// Refresh indicators on config change
void akc_led_refresh_lockled(void) {
    lock_indicator_timer_reset();

    if (akc_via_lock_system_enabled()) {
        lock_last_state = 0xFF; // Force trigger update
        akc_led_lock_indicator_update(host_keyboard_led_state());
    } else {
        lock_last_state = 0;
        akc_lock_indicator_hide();
    }
}

void akc_led_refresh_layerled(void) {
    if (layer_state != default_layer_state) {
        if (akc_via_layerkey_show_lockled_enabled() && akc_via_lock_system_enabled()) {
            akc_led_refresh_lockled();
        } else {
            lock_indicator_timer_reset();
            akc_lock_indicator_hide();
            layer_last_state = 0xFF; // Force trigger update
            akc_led_layer_indicator_update(layer_state);
        }
    } else {
        if (akc_via_layerkey_show_lockled_enabled() && akc_via_lock_system_enabled()) {
            switch_layerled_to_lockled();
        } else {
            switch_lockled_to_layerled();
        }
    }
}

// Initialize RGB layers and refresh lock LEDs
void akc_led_init_lockled(void) {
    lock_indicator_timer_reset();
    layer_indicator_timer_reset();
    akc_rgblight_layers_init();
    if (layer_state != default_layer_state) {
        akc_layer_indicator_show(layer_state);
    }
    if (!akc_via_lock_system_enabled()) return;
    if (layer_state == default_layer_state || !akc_via_layerkey_show_lockled_enabled()) {
        lock_indicator_timer_start();
    }
    akc_lock_indicator_show(host_keyboard_led_state().raw);
}

// Initialize RGB layers and refresh layer LEDs
void akc_led_init_layerled(void) {
    lock_indicator_timer_reset();
    layer_indicator_timer_reset();
    akc_rgblight_layers_init();
    if (akc_via_lock_system_enabled() && akc_via_layerkey_show_lockled_enabled()) {
        if (layer_state != default_layer_state) {
            akc_lock_indicator_show(host_keyboard_led_state().raw);
        }
    } else {
        if (layer_state == default_layer_state) {
            layer_indicator_timer_start();
        }
        akc_layer_indicator_show(layer_state);
    }
}

// Expose LED timers active state for matrix scan
bool akc_led_lockled_timer_active(void) { return lockled_active; }
bool akc_led_layerled_timer_active(void) { return layerled_active; }
