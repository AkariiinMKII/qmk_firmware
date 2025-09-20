// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_led_control.h"

// State tracking
static struct {
    bool num_lock;
    bool caps_lock;
    bool scroll_lock;
} last_lock_state = {false, false, false};

static struct {
    bool active;
    uint16_t timer;
} lock_timeout = {false, 0};

// Check if any layer indicators are active
static bool any_layer_indicator_active(void) {
    for (uint8_t i = USR_LAYER_1; i <= USR_LAYER_4; i++) {
        if (rgblight_get_layer_state(i)) {
            return true;
        }
    }
    return false;
}

// Update lock LED indicators
void usr_led_lock_update(led_t led_state) {
    bool any_change = false;
    
    // Check for changes in lock states
    if (led_state.num_lock != last_lock_state.num_lock) {
        last_lock_state.num_lock = led_state.num_lock;
        any_change = true;
    }
    
    if (led_state.caps_lock != last_lock_state.caps_lock) {
        last_lock_state.caps_lock = led_state.caps_lock;
        any_change = true;
    }
    
    if (led_state.scroll_lock != last_lock_state.scroll_lock) {
        last_lock_state.scroll_lock = led_state.scroll_lock;
        any_change = true;
    }
    
    // If any lock changed, show indicators and restart timer
    if (any_change) {
        lock_timeout.active = true;
        lock_timeout.timer = timer_read();
        
        // Activate black background to override default animation
        rgblight_set_layer_state(USR_LAYER_BG, true);
        
        // Set lock indicators based on their states
        rgblight_set_layer_state(USR_LAYER_NUM, last_lock_state.num_lock);
        rgblight_set_layer_state(USR_LAYER_CAPS, last_lock_state.caps_lock);
        rgblight_set_layer_state(USR_LAYER_SCROLL, last_lock_state.scroll_lock);
    }
}

void usr_led_layer_update(layer_state_t state) {
    // Update layer indicators
    rgblight_set_layer_state(USR_LAYER_1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(USR_LAYER_2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(USR_LAYER_3, layer_state_cmp(state, 3));
    rgblight_set_layer_state(USR_LAYER_4, layer_state_cmp(state, 4));

    // If showing lock LEDs and no layers active, turn off highest layer LED
    if (lock_timeout.active && !any_layer_indicator_active()) {
        rgblight_set_layer_state(USR_LAYER_4, false);
    }
}

void usr_led_scan(layer_state_t state) {
    // Check for timeout
    if (lock_timeout.active && timer_elapsed(lock_timeout.timer) >= USR_LOCK_LED_TIME) {
        lock_timeout.active = false;
        
        // Turn off background to restore default animation
        rgblight_set_layer_state(USR_LAYER_BG, false);
        
        // Turn off all lock indicators
        rgblight_set_layer_state(USR_LAYER_NUM, false);
        rgblight_set_layer_state(USR_LAYER_CAPS, false);
        rgblight_set_layer_state(USR_LAYER_SCROLL, false);
        
        // Restore layer indicators
        usr_led_layer_update(state);
    }
}

