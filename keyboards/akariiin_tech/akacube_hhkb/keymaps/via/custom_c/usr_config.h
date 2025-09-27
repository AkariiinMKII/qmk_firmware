// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

// User configuration for custom features

#pragma once

#include "quantum.h"
#include "usr_rgb_colors.h"
#include "usr_via_config.h"

void led_blink_show(void);
void led_blink_hide(void);
bool usr_combo_any_active(void);


// ================== RGB LED COLORS ==================

// Layer indicator colors
#define USR_COLOR_LAYERLED_BG     HSV_RED_DIM   // Stands for layer off
#define USR_COLOR_LAYERLED_MO1    HSV_BLUE_DIM
#define USR_COLOR_LAYERLED_MO2    HSV_BLUE_DIM
#define USR_COLOR_LAYERLED_MO3    HSV_BLUE_DIM
#define USR_COLOR_LAYERLED_MO4    HSV_BLUE_DIM

// Lock indicator colors
#define USR_COLOR_LOCKLED_BG      HSV_RED_DIM   // Stands for lock off
#define USR_COLOR_LOCKLED_0       HSV_GREEN_DIM  // Lock LED 0
#define USR_COLOR_LOCKLED_1       HSV_GREEN_DIM  // Lock LED 1
#define USR_COLOR_LOCKLED_2       HSV_GREEN_DIM  // Lock LED 2

// Blink effect color
#define USR_COLOR_BLINK           HSV_RED_DIM


// ================ LOCK INDICATOR SYSTEM ================
// Note: Due to API limitations, lock indicators may not work properly on some operating systems

// Lock LED mapping configuration
// - Hardware positions: USR_LOCKLED_0=LED 0-1 (left), USR_LOCKLED_1=LED 3-4 (middle), USR_LOCKLED_2=LED 6-7 (right)
// - Available values: numlock, capslock, scrolllock, compose, kana, disable
// - Setting all LOCKLEDs to 'disable' will disable the entire lock indicator system and force enable layer indicators
#define USR_LOCKLED_0 numlock
#define USR_LOCKLED_1 capslock
#define USR_LOCKLED_2 scrolllock

// Lock LED timeout
// - Time to keep lock indicators on after lock state changes (ms)
#define USR_LOCKLED_KEEPTIME 1000


// ================== LED BLINK SYSTEM ==================

// Blink effect configuration
// - Time of LED on and off in a blink cycle (ms)
#define USR_BLINK_TIME_ON   200    // Blink on time
#define USR_BLINK_TIME_IDLE 200    // Blink off time


// ================== COMBO SYSTEM ==================

// Combo configuration
// - Support up to 16 combos by default (better performance)
// - Uncomment to enable support for up to 32 combos
// #define USR_COMBO_ALLOW_OVER16

// Combo triggers
// - Only support modifier keys, default: LShift + RShift
// - These modifier keys must be held down before pressing combo key
// - Modifier keys are automatically unregistered when combos being satisfied
#define USR_COMBO_MOD1 KC_LSFT
#define USR_COMBO_MOD2 KC_RSFT

// Combo set definitions
// Reset combo configuration
#define USR_RESET_COMBO_KEY KC_R          // Change reset key
#define USR_RESET_COMBO_TIME 5000         // Change reset timing
static inline void usr_reset_combo_on_complete(void) {
    if (!usr_combo_any_active()) {
        led_blink_hide();
    }
    wait_ms(100);
    reset_keyboard();
}
static inline void usr_reset_combo_on_satisfied(void) {
    led_blink_show();
}
static inline void usr_reset_combo_on_reset(void) {
    if (!usr_combo_any_active()) {
        led_blink_hide();
    }
}

// Ciallo combo configuration
#define USR_CIALLO_COMBO_KEY KC_C         // Change ciallo key
#define USR_CIALLO_COMBO_TIME 3000        // Change ciallo timing
static inline void usr_ciallo_combo_on_complete(void) {
    if (!usr_combo_any_active()) {
        led_blink_hide();
    }
    SEND_STRING("ciallo");
}
static inline void usr_ciallo_combo_on_satisfied(void) {
    led_blink_show();
}
static inline void usr_ciallo_combo_on_reset(void) {
    if (!usr_combo_any_active()) {
        led_blink_hide();
    }
}

// Internal combo definitions
// - Define combo configurations above then add them here, optional items can be omitted
// - Format: {.key = COMBO_KEY, .hold_time = HOLD_TIME, .on_complete = action, .on_satisfied = action (optional), .on_reset = action (optional)}
// - Combo keys will be suppressed if modifier keys are held
// - On_complete: called when combo being completed (all keys held for required time after being satisfied)
// - On_satisfied (optional): called when combo being satisfied (modifier and combo keys pressed in required sequence)
// - On_reset (optional): called when combo being reset (any modifier or combo key released after satisfaction and before completion)
#define USR_COMBO_DEFINITIONS \
    {.key = USR_RESET_COMBO_KEY, .hold_time = USR_RESET_COMBO_TIME, .on_complete = usr_reset_combo_on_complete, .on_satisfied = usr_reset_combo_on_satisfied, .on_reset = usr_reset_combo_on_reset}, \
    {.key = USR_CIALLO_COMBO_KEY, .hold_time = USR_CIALLO_COMBO_TIME, .on_complete = usr_ciallo_combo_on_complete, .on_satisfied = usr_ciallo_combo_on_satisfied, .on_reset = usr_ciallo_combo_on_reset}
