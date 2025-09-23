// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

// User configuration for VIA keymap

#pragma once

#include "quantum.h"
#include "usr_rgb_colors.h"

// Forward declarations for LED blink functions
void led_blink_show(void);
void led_blink_hide(void);

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

// Combo key triggers (modifier keys only, default: LShift + RShift)
#define USR_COMBO_MOD1 KC_LSFT
#define USR_COMBO_MOD2 KC_RSFT

// Internal combo definitions
// Format: {.key = COMBO_KEY, .hold_time = HOLD_TIME, .action = action on completed, .on_satisfied = action on pressed (optional), .on_reset = action on reset (optional)}
#define USR_COMBO_DEFINITIONS \
    {.key = USR_RESET_COMBO_KEY, .hold_time = USR_RESET_COMBO_TIME, .action = usr_reset_combo_action, .on_satisfied = led_blink_show, .on_reset = led_blink_hide}, \
    {.key = USR_CIALLO_COMBO_KEY, .hold_time = USR_CIALLO_COMBO_TIME, .action = usr_ciallo_combo_action, .on_satisfied = led_blink_show, .on_reset = led_blink_hide}

// Reset combo configuration
#define USR_RESET_COMBO_KEY KC_R          // Change reset key
#define USR_RESET_COMBO_TIME 5000         // Change reset timing
static inline void usr_reset_combo_action(void) {
    led_blink_hide();
    wait_ms(100);
    reset_keyboard();
}

// Ciallo combo configuration
#define USR_CIALLO_COMBO_KEY KC_C         // Change ciallo key
#define USR_CIALLO_COMBO_TIME 3000        // Change ciallo timing
static inline void usr_ciallo_combo_action(void) {
    led_blink_hide();
    SEND_STRING("ciallo");
}
