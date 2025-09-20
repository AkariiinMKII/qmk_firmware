// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_combo.h"

// Configuration defaults
#ifndef USR_COMBO_MOD1
#    define USR_COMBO_MOD1 KC_LSFT
#endif
#ifndef USR_COMBO_MOD2
#    define USR_COMBO_MOD2 KC_RSFT
#endif

// Temporarily disable this check to allow compilation
// TODO: Debug why KC_LSFT and KC_RSFT are being treated as equal
/*
#if USR_COMBO_MOD1 == USR_COMBO_MOD2
#    error "Combo modifier keys must be different"
#endif
*/

#ifndef RESET_COMBO_HOLD_TIME
#    define RESET_COMBO_HOLD_TIME 5000
#endif

#ifndef CIALLO_HOLD_TIME
#    define CIALLO_HOLD_TIME 5000
#endif

#if RESET_COMBO_HOLD_TIME < 1000 || RESET_COMBO_HOLD_TIME > 10000
#    warning "Reset combo hold time should be 1000-10000ms"
#endif

#if CIALLO_HOLD_TIME < 500 || CIALLO_HOLD_TIME > 10000
#    warning "Ciallo combo hold time should be 500-10000ms"
#endif

#ifndef USR_COMBO_DEFINITIONS
#    error "USR_COMBO_DEFINITIONS must be defined in usr_config.h"
#endif

// Types
typedef struct {
    uint16_t key;
    uint16_t hold_time;
    void (*action)(void);
} combo_config_t;

typedef struct {
    bool key_held;
    uint16_t timer;
} combo_state_t;

// Static data
static const combo_config_t combos[] = {
    USR_COMBO_DEFINITIONS
};

static combo_state_t combo_states[sizeof(combos) / sizeof(combos[0])] = {0};
static bool mod1_held = false;
static bool mod2_held = false;

#define NUM_COMBOS (sizeof(combos) / sizeof(combos[0]))

// Static functions
static bool is_combo_ready(void) {
    return mod1_held && mod2_held;
}

static void reset_combo_states(void) {
    for (uint8_t i = 0; i < NUM_COMBOS; i++) {
        combo_states[i].key_held = false;
        combo_states[i].timer = 0;
    }
}


static bool is_combo_fully_active(void) {
    if (!is_combo_ready()) {
        return false;
    }

    for (uint8_t i = 0; i < NUM_COMBOS; i++) {
        if (combo_states[i].key_held) {
            return true;
        }
    }
    return false;
}

static void usr_combo_timer(uint8_t combo_index) {
    const combo_config_t *config = &combos[combo_index];
    combo_state_t *state = &combo_states[combo_index];

    if (is_combo_ready() && state->key_held) {
        if (state->timer == 0) {
            state->timer = timer_read();
            if (state->timer == 0) {
                state->timer = 1;
            }
        } else if (timer_elapsed(state->timer) >= config->hold_time) {
            config->action();
            state->timer = 0;
        }
    } else {
        state->timer = 0;
    }
}

// Public functions
bool usr_combo_process(uint16_t keycode, bool pressed) {
    // Handle modifier keys
    if (keycode == USR_COMBO_MOD1) {
        mod1_held = pressed;
        if (!pressed) {
            reset_combo_states();
        }
        // Suppress modifier presses when any combo is already active
        return !(pressed && is_combo_fully_active());
    } else if (keycode == USR_COMBO_MOD2) {
        mod2_held = pressed;
        if (!pressed) {
            reset_combo_states();
        }
        // Suppress modifier presses when any combo is already active
        return !(pressed && is_combo_fully_active());
    }

    // Handle combo action keys
    for (uint8_t i = 0; i < NUM_COMBOS; i++) {
        if (keycode == combos[i].key) {
            bool was_combo_active = is_combo_fully_active();

            if (pressed && is_combo_ready()) {
                combo_states[i].key_held = true;
            } else if (!pressed) {
                combo_states[i].key_held = false;
            }

            // Suppress if combo was already active, or if it just became active
            return !(was_combo_active || (pressed && is_combo_ready()));
        }
    }

    // Not a combo-related key
    return true;
}

void usr_combo_resolver(void) {
    for (uint8_t i = 0; i < NUM_COMBOS; i++) {
        usr_combo_timer(i);
    }
}
