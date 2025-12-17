// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "mnm_rgb_colors.h"

bool mnm_combo_any_active(void);
void mnm_led_blink_show(void);
void mnm_led_blink_hide(void);

// =========================================================
// ================== USER CONFIGURATION ===================
// =========================================================

// NOTE: Some definitions serve as default fallback values.
// When VIA is used, these values are overwritten by user configurations from VIA.

// ==================== RGB LED COLORS =====================

// Layer indicator colors (overwritten by VIA config)
#define MNM_COLOR_LAYERLED_MO1    HSV_BLUE_DIM
#define MNM_COLOR_LAYERLED_MO2    HSV_BLUE_DIM
#define MNM_COLOR_LAYERLED_MO3    HSV_BLUE_DIM

// Lock indicator colors (overwritten by VIA config)
#define MNM_COLOR_LOCKLED_BG      HSV_RED_DIM   // Off state color
#define MNM_COLOR_LOCKLED_0       HSV_GREEN_DIM
#define MNM_COLOR_LOCKLED_1       HSV_GREEN_DIM

// Blink effect color
#define MNM_COLOR_BLINK           HSV_RED_DIM

// ===================== LED KEEP TIME =====================

// LED timeout (overwritten by VIA config)
// - Time to keep LED indicators on after state changes (ms)
#define MNM_LED_KEEPTIME 1500

// ================ LAYER INDICATOR SYSTEM =================

// Indicator positions for 4 keymap layers
// - Starting number of LEDs for each layer indicator (layer 0,1,2,3)
// - LEDs count starts from 0
#define MNM_LAYERLED_POSITIONS {0, 2}

// Layer LED length
// - Number of LEDs used for each indicator
// - Should not be greater than the step to next position
#define MNM_LAYERLED_LENGTH 2

// ================= LOCK INDICATOR SYSTEM =================

// NOTE: Due to API limitations, lock indicators are automatically disabled for macOS/iOS host.

// Indicator positions for 3 lock states
// - Starting number of LEDs for each lock indicator (lock 0,1,2)
// - LEDs count starts from 0
#define MNM_LOCKLED_POSITIONS {0, 2}

// Lock LED length
// - Number of LEDs used for each indicator
// - Should not be greater than the step to next position
#define MNM_LOCKLED_LENGTH 2

// Lock LED mapping configuration (overwritten by VIA config)
// - Available values: 0=disable, 1=numlock, 2=capslock, 4=scrolllock, 8=compose, 16=kana
// - Setting all LOCKLEDs to 0 will disable the entire lock indicator system and force enable layer indicators
#define MNM_LOCKLED_0 2
#define MNM_LOCKLED_1 0

// =================== LED BLINK SYSTEM ====================

// Blink effect configuration
// - Time of LED on and off in a blink cycle (ms)
#define MNM_BLINK_TIME_ON   200
#define MNM_BLINK_TIME_IDLE 200

// ===================== COMBO SYSTEM ======================

// Combo configuration
// - Support up to 16 combos by default (better performance)
// - Uncomment to enable support for up to 32 combos
// #define MNM_COMBO_ALLOW_OVER16

// Combo triggers
// - Only support modifier keys, default: LShift + RShift
// - These modifier keys must be held down before pressing combo key
// - Modifier keys are automatically unregistered when combos being satisfied
#define MNM_COMBO_MOD1 KC_LSFT
#define MNM_COMBO_MOD2 KC_RSFT

// Combo set definitions

// Reset combo configuration
#define MNM_COMBO_RESET_KEY KC_R          // Combo key
#define MNM_COMBO_RESET_TIME 5000         // Hold time (ms)
static inline void mnm_combo_reset_on_complete(void) {
    if (!mnm_combo_any_active()) {
        mnm_led_blink_hide();
    }
    wait_ms(100);
    reset_keyboard();
}
static inline void mnm_combo_reset_on_satisfied(void) {
    mnm_led_blink_show();
}
static inline void mnm_combo_reset_on_reset(void) {
    if (!mnm_combo_any_active()) {
        mnm_led_blink_hide();
    }
}

// Ciallo combo configuration
#define MNM_COMBO_CIALLO_KEY KC_C         // Combo key
#define MNM_COMBO_CIALLO_TIME 3000        // Hold time (ms)
static inline void mnm_combo_ciallo_on_complete(void) {
    if (!mnm_combo_any_active()) {
        mnm_led_blink_hide();
    }
    SEND_STRING("ciallo");
}
static inline void mnm_combo_ciallo_on_satisfied(void) {
    mnm_led_blink_show();
}
static inline void mnm_combo_ciallo_on_reset(void) {
    if (!mnm_combo_any_active()) {
        mnm_led_blink_hide();
    }
}

// Internal combo definitions
// - Define combo configurations above then add them here, optional items can be omitted
// - Format: {.key = COMBO_KEY, .hold_time = HOLD_TIME, .on_complete = action, .on_satisfied = action (optional), .on_reset = action (optional)}
// - Combo keys will be suppressed if modifier keys are held
// - On_complete: called when combo being completed (all keys held for required time after being satisfied)
// - On_satisfied (optional): called when combo being satisfied (modifier and combo keys pressed in required sequence)
// - On_reset (optional): called when combo being reset (any modifier or combo key released after satisfaction and before completion)
#define MNM_COMBO_DEFINITIONS { \
    .key = MNM_COMBO_RESET_KEY, \
    .hold_time = MNM_COMBO_RESET_TIME, \
    .on_complete = mnm_combo_reset_on_complete, \
    .on_satisfied = mnm_combo_reset_on_satisfied, \
    .on_reset = mnm_combo_reset_on_reset \
}, { \
    .key = MNM_COMBO_CIALLO_KEY, \
    .hold_time = MNM_COMBO_CIALLO_TIME, \
    .on_complete = mnm_combo_ciallo_on_complete, \
    .on_satisfied = mnm_combo_ciallo_on_satisfied, \
    .on_reset = mnm_combo_ciallo_on_reset \
}
