// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "akc_custom.h"

// Types
typedef struct {
    uint16_t key;
    uint16_t hold_time;
    void (*on_complete)(void);
    void (*on_satisfied)(void);  // Called when combo becomes satisfied (optional)
    void (*on_reset)(void);      // Called when combo is reset (optional)
} combo_config_t;

// Static data
static const combo_config_t combos[] = { AKC_COMBO_DEFINITIONS };
static bool mod1_held = false;
static bool mod2_held = false;
#ifdef AKC_COMBO_ALLOW_OVER16
static uint32_t combo_satisfied_state = 0;  // Bitmask: bit N = combo N satisfied (up to 32 combos)
#else
static uint16_t combo_satisfied_state = 0;  // Bitmask: bit N = combo N satisfied (up to 16 combos)
#endif
static uint16_t combo_timers[sizeof(combos) / sizeof(combos[0])] = {0};

// Macros
#define NUM_COMBOS (sizeof(combos) / sizeof(combos[0]))

// Compile-time checks for combo limits
#ifdef AKC_COMBO_ALLOW_OVER16
_Static_assert(NUM_COMBOS <= 32, "Too many combo definitions for uint32_t bitmask (max 32)");
#else
_Static_assert(NUM_COMBOS <= 16, "Too many combo definitions for uint16_t bitmask (max 16, or define AKC_COMBO_ALLOW_OVER16 for up to 32)");
#endif

// Static functions
static bool combo_ready(void) { return mod1_held && mod2_held; } // Mark as ready when both mods held

// Bitmask operations for combo satisfied states (like QMK layer system)
static inline void combo_satisfied_set(uint8_t combo_index, bool satisfied) {
#ifdef AKC_COMBO_ALLOW_OVER16
    satisfied ? (combo_satisfied_state |= (1UL << combo_index))
              : (combo_satisfied_state &= ~(1UL << combo_index));
#else
    satisfied ? (combo_satisfied_state |= (1U << combo_index))
              : (combo_satisfied_state &= ~(1U << combo_index));
#endif
}

static inline bool combo_satisfied_get(uint8_t combo_index) {
#ifdef AKC_COMBO_ALLOW_OVER16
    return combo_satisfied_state & (1UL << combo_index);
#else
    return combo_satisfied_state & (1U << combo_index);
#endif
}

static void combo_reset(void) {
    if (!combo_satisfied_state) return;

    for (uint8_t i = 0; i < NUM_COMBOS; i++) {
        if (combo_satisfied_get(i)) {
            combo_satisfied_set(i, false);
            combo_timers[i] = 0;
            if (combos[i].on_reset) {
                combos[i].on_reset();
            }
        }
    }
}

static void combo_timer(uint8_t combo_index) {
    if (!combo_satisfied_get(combo_index)) return;

    const combo_config_t *config = &combos[combo_index];

    if (timer_elapsed(combo_timers[combo_index]) >= config->hold_time) {
        combo_satisfied_set(combo_index, false);  // Mark as completed to prevent repeated executions
        combo_timers[combo_index] = 0;

        config->on_complete();
    }
}

// Public functions
bool akc_combo_check(uint16_t keycode, bool pressed) {
    // Handle modifier keys
    if (keycode == AKC_COMBO_MOD1) {
        mod1_held = pressed;
        if (!pressed) { combo_reset(); }  // Mark as not satisfied on any mod release
        return true;  // Always allow modifier keys through
    } else if (keycode == AKC_COMBO_MOD2) {
        mod2_held = pressed;
        if (!pressed) { combo_reset(); }  // Mark as not satisfied on any mod release
        return true;  // Always allow modifier keys through
    }

    // Handle combo trigger keys
    for (uint8_t i = 0; i < NUM_COMBOS; i++) {
        if (keycode == combos[i].key) {
            bool was_satisfied = combo_satisfied_get(i);

            if (pressed) {
                if (combo_ready()) {
                    // Check if this combo newly becomes satisfied
                    if (!was_satisfied) {
                        combo_satisfied_set(i, true); // Mark as satisfied on key press
                        combo_timers[i] = timer_read();

                        // Unregister modifier keys when combo becomes satisfied
                        unregister_code(AKC_COMBO_MOD1);
                        unregister_code(AKC_COMBO_MOD2);

                        if (combos[i].on_satisfied) {
                            combos[i].on_satisfied();
                        }
                    }
                    return false;  // Catch the key and suppress on satisfied or already satisfied
                } else {
                    return true;   // Allow key through if combo not ready
                }
            } else {
                if (was_satisfied) {
                    combo_satisfied_set(i, false); // Mark as not satisfied on key release
                    combo_timers[i] = 0;
                    if (combos[i].on_reset) {
                        combos[i].on_reset();
                    }
                }
                return true;  // Always allow key release
            }
        }
    }

    // Handle non-combo keys
    return true;  // Allow non-combo-related keys through
}

void akc_combo_handler(void) {
    for (uint8_t i = 0; i < NUM_COMBOS; i++) { combo_timer(i); }
}

// Public function to check if any combo is currently satisfied
bool akc_combo_any_active(void) { return combo_satisfied_state != 0; }
