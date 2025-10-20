// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

// User configuration for custom features

#pragma once

#include "quantum.h"
#include "akc_rgb_colors.h"

bool akc_combo_any_active(void);
void akc_led_blink_show(void);
void akc_led_blink_hide(void);


// ==================== OS COMPATIBILITY ====================

// Auto Alt/GUI swap configuration
// - Enable automatic modifier key swap based on detected OS
// - Swaps Alt/GUI keys for macOS/iOS compatibility
#define AKC_AUTO_SWAP_AG


// ===================== RGB LED COLORS =====================

// Layer indicator colors
#define AKC_COLOR_LAYERLED_BG     HSV_RED_DIM
#define AKC_COLOR_LAYERLED_MO0    HSV_BLUE_DIM
#define AKC_COLOR_LAYERLED_MO1    HSV_BLUE_DIM
#define AKC_COLOR_LAYERLED_MO2    HSV_BLUE_DIM
#define AKC_COLOR_LAYERLED_MO3    HSV_BLUE_DIM

// Lock indicator colors
#define AKC_COLOR_LOCKLED_BG      HSV_RED_DIM   // Stands for lock off
#define AKC_COLOR_LOCKLED_0       HSV_GREEN_DIM  // Lock LED 0
#define AKC_COLOR_LOCKLED_1       HSV_GREEN_DIM  // Lock LED 1
#define AKC_COLOR_LOCKLED_2       HSV_GREEN_DIM  // Lock LED 2

// Blink effect color
#define AKC_COLOR_BLINK           HSV_RED_DIM


// ================== LOCK INDICATOR SYSTEM ==================
// Note: Due to API limitations, lock indicators may not work properly on some operating systems

// Lock LED mapping configuration
// - Hardware positions: AKC_LOCKLED_0=LED 0-1 (left), AKC_LOCKLED_1=LED 3-4 (middle), AKC_LOCKLED_2=LED 6-7 (right)
// - Available values: 0=disable, 1=numlock, 2=capslock, 4=scrolllock, 8=compose, 16=kana
// - Setting all LOCKLEDs to 0 will disable the entire lock indicator system and force enable layer indicators
#define AKC_LOCKLED_0 1  // numlock
#define AKC_LOCKLED_1 2  // capslock
#define AKC_LOCKLED_2 4  // scrolllock

// LED timeout
// - Time to keep LED indicators on after state changes (ms)
#define AKC_LED_KEEPTIME 1500


// ==================== LED BLINK SYSTEM =====================

// Blink effect configuration
// - Time of LED on and off in a blink cycle (ms)
#define AKC_BLINK_TIME_ON   200    // Blink on time
#define AKC_BLINK_TIME_IDLE 200    // Blink off time


// ====================== COMBO SYSTEM =======================

// Combo configuration
// - Support up to 16 combos by default (better performance)
// - Uncomment to enable support for up to 32 combos
// #define AKC_COMBO_ALLOW_OVER16

// Combo triggers
// - Only support modifier keys, default: LShift + RShift
// - These modifier keys must be held down before pressing combo key
// - Modifier keys are automatically unregistered when combos being satisfied
#define AKC_COMBO_MOD1 KC_LSFT
#define AKC_COMBO_MOD2 KC_RSFT

// Combo set definitions
// Reset combo configuration
#define AKC_RESET_COMBO_KEY KC_R          // Change reset key
#define AKC_RESET_COMBO_TIME 5000         // Change reset timing
static inline void akc_reset_combo_on_complete(void) {
    if (!akc_combo_any_active()) {
        akc_led_blink_hide();
    }
    wait_ms(100);
    reset_keyboard();
}
static inline void akc_reset_combo_on_satisfied(void) {
    akc_led_blink_show();
}
static inline void akc_reset_combo_on_reset(void) {
    if (!akc_combo_any_active()) {
        akc_led_blink_hide();
    }
}

// Ciallo combo configuration
#define AKC_CIALLO_COMBO_KEY KC_C         // Change ciallo key
#define AKC_CIALLO_COMBO_TIME 3000        // Change ciallo timing
static inline void akc_ciallo_combo_on_complete(void) {
    if (!akc_combo_any_active()) {
        akc_led_blink_hide();
    }
    SEND_STRING("ciallo");
}
static inline void akc_ciallo_combo_on_satisfied(void) {
    akc_led_blink_show();
}
static inline void akc_ciallo_combo_on_reset(void) {
    if (!akc_combo_any_active()) {
        akc_led_blink_hide();
    }
}

// Internal combo definitions
// - Define combo configurations above then add them here, optional items can be omitted
// - Format: {.key = COMBO_KEY, .hold_time = HOLD_TIME, .on_complete = action, .on_satisfied = action (optional), .on_reset = action (optional)}
// - Combo keys will be suppressed if modifier keys are held
// - On_complete: called when combo being completed (all keys held for required time after being satisfied)
// - On_satisfied (optional): called when combo being satisfied (modifier and combo keys pressed in required sequence)
// - On_reset (optional): called when combo being reset (any modifier or combo key released after satisfaction and before completion)
#define AKC_COMBO_DEFINITIONS \
    {.key = AKC_RESET_COMBO_KEY, .hold_time = AKC_RESET_COMBO_TIME, .on_complete = akc_reset_combo_on_complete, .on_satisfied = akc_reset_combo_on_satisfied, .on_reset = akc_reset_combo_on_reset}, \
    {.key = AKC_CIALLO_COMBO_KEY, .hold_time = AKC_CIALLO_COMBO_TIME, .on_complete = akc_ciallo_combo_on_complete, .on_satisfied = akc_ciallo_combo_on_satisfied, .on_reset = akc_ciallo_combo_on_reset}
