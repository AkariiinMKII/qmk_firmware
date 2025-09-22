// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_combo.h"

// Types
typedef struct {
    uint16_t key;
    uint16_t hold_time;
    void (*action)(void);
} combo_config_t;

typedef struct {
    bool key_held;
    uint16_t timer;  // 0 = timer not started, >0 = timer start timestamp
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
        combo_states[i].key_held = false;
        combo_states[i].timer = 0;
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

    if (combo_ready() && state->key_held) {
        if (state->timer == 0) {
            state->timer = timer_read();
            if (state->timer == 0) { state->timer = 1; }  // Avoid timer_read() == 0 edge case
        } else if (timer_elapsed(state->timer) >= config->hold_time) {
            config->action();
            state->timer = 0;
        }
    } else {
        // Reset current timer if combo pressing suspended
        state->timer = 0;
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
            if (pressed && combo_ready()) {
                combo_states[i].key_held = true;
            } else if (!pressed) {
                combo_states[i].key_held = false;
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
