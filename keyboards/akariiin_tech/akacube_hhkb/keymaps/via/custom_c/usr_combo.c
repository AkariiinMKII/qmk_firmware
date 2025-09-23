// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_combo.h"

// Types
typedef struct {
    uint16_t key;
    uint16_t hold_time;
    void (*action)(void);
    void (*on_satisfied)(void);  // Called when combo becomes satisfied (optional)
    void (*on_reset)(void);      // Called when combo is reset (optional)
} combo_config_t;

typedef struct {
    bool key_held;   // Physical combo key is held
    bool satisfied;  // Combo is satisfied (for callbacks and timing)
    uint16_t timer;  // Timestamp when combo became satisfied
} combo_state_t;

// Static data
static const combo_config_t combos[] = { USR_COMBO_DEFINITIONS };
static combo_state_t combo_states[sizeof(combos) / sizeof(combos[0])] = {0};
static bool mod1_held = false;
static bool mod2_held = false;

#define NUM_COMBOS (sizeof(combos) / sizeof(combos[0]))

// Static functions
static bool combo_ready(void) { return mod1_held && mod2_held; }

static void combo_reset(void) {
    for (uint8_t i = 0; i < NUM_COMBOS; i++) {
        if (combo_states[i].satisfied && combos[i].on_reset) {
            combos[i].on_reset();
        }
        combo_states[i].key_held = false;
        combo_states[i].satisfied = false;
    }
}

static bool combo_satisfied(void) {
    if (!combo_ready()) { return false; }

    for (uint8_t i = 0; i < NUM_COMBOS; i++) {
        if (combo_states[i].key_held) { return true; }
    }
    return false;
}

static void usr_combo_timer(uint8_t combo_index) {
    const combo_config_t *config = &combos[combo_index];
    combo_state_t *state = &combo_states[combo_index];

    if (state->satisfied) {
        if (timer_elapsed(state->timer) >= config->hold_time) {
            config->action();
            state->satisfied = false;  // Mark as completed to stop repeated actions
        }
    }
}

// Public functions
bool usr_combo_check(uint16_t keycode, bool pressed) {
    // Handle modifier keys
    if (keycode == USR_COMBO_MOD1) {
        mod1_held = pressed;
        if (!pressed) { combo_reset(); }
        // Suppress modifier presses when any combo is already active
        return !(pressed && combo_satisfied());
    } else if (keycode == USR_COMBO_MOD2) {
        mod2_held = pressed;
        if (!pressed) { combo_reset(); }
        // Suppress modifier presses when any combo is already active
        return !(pressed && combo_satisfied());
    }

    // Handle combo action keys
    for (uint8_t i = 0; i < NUM_COMBOS; i++) {
        if (keycode == combos[i].key) {
            bool was_satisfied = combo_states[i].satisfied;

            if (pressed && combo_ready()) {
                combo_states[i].key_held = true;
                // Check if this combo just became satisfied
                if (!was_satisfied) {
                    combo_states[i].satisfied = true;
                    combo_states[i].timer = timer_read();  // Start timing immediately
                    if (combos[i].on_satisfied) {
                        combos[i].on_satisfied();  // Call on_satisfied callback
                    }
                }
            } else if (!pressed) {
                combo_states[i].key_held = false;
                if (was_satisfied) {
                    combo_states[i].satisfied = false;
                    if (combos[i].on_reset) {
                        combos[i].on_reset();  // Call on_reset callback
                    }
                }
            }

            // Suppress if combo is active now, or if it just became active
            return !(combo_satisfied() || (pressed && combo_ready()));
        }
    }

    // Not a combo-related key
    return true;
}

void usr_combo_handler(void) {
    for (uint8_t i = 0; i < NUM_COMBOS; i++) {
        usr_combo_timer(i);
    }
}
