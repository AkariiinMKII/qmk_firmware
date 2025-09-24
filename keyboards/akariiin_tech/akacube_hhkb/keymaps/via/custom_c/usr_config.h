// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

// User configuration for VIA keymap

#pragma once

#include "quantum.h"
#include "usr_rgb_colors.h"

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
#define USR_COLOR_LOCKLED_1       HSV_GREEN_DIM
#define USR_COLOR_LOCKLED_2       HSV_GREEN_DIM
#define USR_COLOR_LOCKLED_3       HSV_GREEN_DIM

// Blink effect color
#define USR_COLOR_BLINK           HSV_RED_DIM


// ================ LOCK INDICATOR SYSTEM ================
// Note: Due to API limitations, lock indicators may not work properly on some operating systems

// Lock LED mapping configuration
// Positions: LOCKLED_1=LED 0-1 (left), LOCKLED_2=LED 3-4 (middle), LOCKLED_3=LED 6-7 (right)
// Available values: num_lock, caps_lock, scroll_lock, compose, kana, disable
// Note: Setting all LOCKLEDs to 'disable' will disable the entire lock indicator system and forcely enable layer indicators
#define USR_LOCKLED_1 num_lock
#define USR_LOCKLED_2 caps_lock
#define USR_LOCKLED_3 scroll_lock

// Lock LED timeout
#define USR_LOCKLED_KEEPTIME 1000  // Lock LED keep time (ms)

// Layer key behavior
#define LAYER_KEY_SHOW_LOCK_INDICATORS  // Show locks on layer change


// ================== LED BLINK SYSTEM ==================

#define USR_BLINK_TIME_ON   200    // Blink on time (ms)
#define USR_BLINK_TIME_IDLE 200    // Blink idle time (ms)


// ================== COMBO SYSTEM ==================

// Combo configuration:
// - Default: uint16_t bitmask supports up to 16 combos (better performance)
// - Define USR_COMBO_ALLOW_OVER16 to use uint32_t bitmask for up to 32 combos
// #define USR_COMBO_ALLOW_OVER16

// Combo key triggers (modifier keys only, default: LShift + RShift)
// Note: Modifier keys are automatically unregistered when combos become satisfied
#define USR_COMBO_MOD1 KC_LSFT
#define USR_COMBO_MOD2 KC_RSFT

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

// Internal combo definitions - defined AFTER all symbols above
// Format: {.key = COMBO_KEY, .hold_time = HOLD_TIME, .on_complete = action, .on_satisfied = action (optional), .on_reset = action (optional)}
// Note: Combo keys are suppressed if mod keys ready; released on key up or timeout
#define USR_COMBO_DEFINITIONS \
    {.key = USR_RESET_COMBO_KEY, .hold_time = USR_RESET_COMBO_TIME, .on_complete = usr_reset_combo_on_complete, .on_satisfied = usr_reset_combo_on_satisfied, .on_reset = usr_reset_combo_on_reset}, \
    {.key = USR_CIALLO_COMBO_KEY, .hold_time = USR_CIALLO_COMBO_TIME, .on_complete = usr_ciallo_combo_on_complete, .on_satisfied = usr_ciallo_combo_on_satisfied, .on_reset = usr_ciallo_combo_on_reset}
