// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

// User configuration for VIA keymap

#pragma once

#include "quantum.h"
#include "usr_rgb_colors.h"

// Forward declarations for LED blink functions
void led_blink_show(void);
void led_blink_hide(void);
bool usr_combo_any_active(void);

// LED colors
#define USR_COLOR_LAYERLED_BG     HSV_RED_DIM
#define USR_COLOR_LAYERLED_MO1    HSV_BLUE_DIM
#define USR_COLOR_LAYERLED_MO2    HSV_BLUE_DIM
#define USR_COLOR_LAYERLED_MO3    HSV_BLUE_DIM
#define USR_COLOR_LAYERLED_MO4    HSV_BLUE_DIM
#define USR_COLOR_LOCKLED_BG      HSV_RED_DIM
#define USR_COLOR_LOCKLED_NUM     HSV_GREEN_DIM
#define USR_COLOR_LOCKLED_CAPS    HSV_GREEN_DIM
#define USR_COLOR_LOCKLED_SCROLL  HSV_GREEN_DIM
#define USR_COLOR_BLINK           HSV_RED_DIM

// LED Configuration
#define USR_LOCKLED_KEEPTIME 1000  // Lock LED keep time (ms)

// Blink Configuration
#define USR_BLINK_TIME_ON   200    // Blink on time (ms)
#define USR_BLINK_TIME_IDLE 200    // Blink idle time (ms)

// Layer key behavior
#define LAYER_KEY_SHOW_LOCK_INDICATORS  // Show locks on layer change

// Combo configuration:
// - Default: uint16_t bitmask supports up to 16 combos (better performance)
// - Define USR_COMBO_ALLOW_OVER16 to use uint32_t bitmask for up to 32 combos
// #define USR_COMBO_ALLOW_OVER16

// Combo key triggers (modifier keys only, default: LShift + RShift)
// Note: Modifier keys are automatically unregistered when combos become satisfied
#define USR_COMBO_MOD1 KC_LSFT
#define USR_COMBO_MOD2 KC_RSFT

// Internal combo definitions
// Format: {.key = COMBO_KEY, .hold_time = HOLD_TIME, .on_complete = action, .on_satisfied = action (optional), .on_reset = action (optional)}
// Note: Combo keys are suppressed if mod keys ready; released on key up or timeout
#define USR_COMBO_DEFINITIONS \
    {.key = USR_RESET_COMBO_KEY, .hold_time = USR_RESET_COMBO_TIME, .on_complete = usr_reset_combo_on_complete, .on_satisfied = usr_reset_combo_on_satisfied, .on_reset = usr_reset_combo_on_reset}, \
    {.key = USR_CIALLO_COMBO_KEY, .hold_time = USR_CIALLO_COMBO_TIME, .on_complete = usr_ciallo_combo_on_complete, .on_satisfied = usr_ciallo_combo_on_satisfied, .on_reset = usr_ciallo_combo_on_reset}

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
