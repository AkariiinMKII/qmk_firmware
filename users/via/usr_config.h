// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

// User configuration for VIA keymap

#pragma once

#include "quantum.h"
#include "usr_rgb_colors.h"

// LED Configuration
#define USR_LOCK_LED_TIME 3000  // Lock LED timeout (ms)
#define USR_LED_COUNT 8         // Total RGB LEDs

// RGB layers
#define RGBLIGHT_MAX_LAYERS 12

#define USR_LAYER_LAYERLED_BG     0  // Layer background
#define USR_LAYER_LAYERLED_MO1    1  // Layer 1
#define USR_LAYER_LAYERLED_MO2    2  // Layer 2
#define USR_LAYER_LAYERLED_MO3    3  // Layer 3
#define USR_LAYER_LAYERLED_MO4    4  // Layer 4
#define USR_LAYER_LOCKLED_BG      5  // Lock background
#define USR_LAYER_LOCKLED_NUM     6  // Num lock
#define USR_LAYER_LOCKLED_CAPS    7  // Caps lock
#define USR_LAYER_LOCKLED_SCROLL  8  // Scroll lock

// LED colors
#define USR_COLOR_CAPS      HSV_GREEN_DIM
#define USR_COLOR_SCROLL    HSV_GREEN_DIM
#define USR_COLOR_NUM       HSV_GREEN_DIM
#define USR_COLOR_LAYER1    HSV_BLUE_DIM
#define USR_COLOR_LAYER2    HSV_BLUE_DIM
#define USR_COLOR_LAYER3    HSV_BLUE_DIM
#define USR_COLOR_LAYER4    HSV_BLUE_DIM

#define LAYER_KEY_SHOW_LOCK_INDICATORS  // Show locks on layer change

// Combo keys (default: LShift + RShift + key)
#define USR_COMBO_MOD1 KC_LSFT   // Left Shift
#define USR_COMBO_MOD2 KC_RSFT   // Right Shift

// Internal combo definitions
// Format: {.key = COMBO_KEY, .hold_time = HOLD_TIME, .action = action_function}
#define USR_COMBO_DEFINITIONS \
    {.key = RESET_COMBO_KEY, .hold_time = RESET_COMBO_HOLD_TIME, .action = reset_combo_action}, \
    {.key = CIALLO_KEY, .hold_time = CIALLO_HOLD_TIME, .action = ciallo_combo_action}

// Reset combo configuration
#define RESET_COMBO_KEY KC_R          // Change reset key
#define RESET_COMBO_HOLD_TIME 5000    // Change reset timing
static inline void reset_combo_action(void) {
    reset_keyboard();
}

// Ciallo combo configuration
#define CIALLO_KEY KC_C           // Change ciallo key
#define CIALLO_HOLD_TIME 3000     // Change ciallo timing
static inline void ciallo_combo_action(void) {
    SEND_STRING("ciallo");
}
