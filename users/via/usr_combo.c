// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_combo.h"

// Reset combo: LShift + RShift + R (hold 5s)
#ifndef RESET_COMBO_KEY
#    define RESET_COMBO_KEY KC_R
#endif
#ifndef RESET_COMBO_HOLD_TIME
#    define RESET_COMBO_HOLD_TIME 5000
#endif

// Easter egg combo: LShift + RShift + C (hold 3s)
#ifndef EASTER_EGG_KEY
#    define EASTER_EGG_KEY KC_C
#endif
#ifndef EASTER_EGG_HOLD_TIME
#    define EASTER_EGG_HOLD_TIME 3000
#endif

// Combo system
typedef struct {
    uint16_t key;           // Third key
    uint16_t hold_time;     // Hold time (ms)
    bool key_held;          // Key state
    uint16_t timer;         // Timer
    void (*action)(void);   // Action function
} combo_t;

// Combo actions
static void reset_action(void) {
    reset_keyboard();
}

static void easter_egg_action(void) {
    SEND_STRING("ciallo");
}

// Combo definitions
static combo_t combos[] = {
    {RESET_COMBO_KEY, RESET_COMBO_HOLD_TIME, false, 0, reset_action},
    {EASTER_EGG_KEY, EASTER_EGG_HOLD_TIME, false, 0, easter_egg_action},
};

#define NUM_COMBOS (sizeof(combos) / sizeof(combos[0]))

// Shift key states
static bool lshift_held = false;
static bool rshift_held = false;

// Check if key is part of any combo
static bool is_combo_key(uint16_t keycode) {
    if (keycode == KC_LSFT || keycode == KC_RSFT) return true;
    
    for (uint8_t i = 0; i < NUM_COMBOS; i++) {
        if (keycode == combos[i].key) {
            return true;
        }
    }
    return false;
}

// Check if any combo is fully active
static bool is_combo_fully_active(void) {
    if (!lshift_held || !rshift_held) return false;
    
    for (uint8_t i = 0; i < NUM_COMBOS; i++) {
        if (combos[i].key_held) {
            return true;
        }
    }
    return false;
}

// Handle individual combo timing
static void handle_combo(combo_t *combo) {
    if (lshift_held && rshift_held && combo->key_held) {
        if (combo->timer == 0) {
            combo->timer = timer_read();  // Start timer
        } else if (timer_elapsed(combo->timer) >= combo->hold_time) {
            combo->action();  // Execute action
            combo->timer = 0; // Prevent repeat
        }
    } else {
        combo->timer = 0;  // Reset on key release
    }
}

// Process all combos
static void handle_all_combos(void) {
    for (uint8_t i = 0; i < NUM_COMBOS; i++) {
        handle_combo(&combos[i]);
    }
}

bool usr_combo_process(uint16_t keycode, bool pressed) {
    // Update key states
    switch (keycode) {
        case KC_LSFT: lshift_held = pressed; break;
        case KC_RSFT: rshift_held = pressed; break;
        default:
            // Check for matching combo keys
            for (uint8_t i = 0; i < NUM_COMBOS; i++) {
                if (keycode == combos[i].key) {
                    combos[i].key_held = pressed;
                    break;
                }
            }
            break;
    }
    
    // Suppress key events when combo is active
    if (is_combo_key(keycode) && is_combo_fully_active()) {
        return false;  // Suppress key
    }
    
    return true;  // Allow key
}

bool usr_combo_scan(void) {
    handle_all_combos();
    return false;
}
