// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

// Configuration constants for VIA keymap
// LED timings, colors, combo settings

#pragma once

#include "quantum.h"
#include "usr_rgb_colors.h"

// LED Configuration
#define USR_LOCK_LED_TIME 3000  // Lock LED display timeout (ms)
#define USR_LED_COUNT 8         // Total RGB LEDs

// RGB layer indices
#define USR_LAYER_BG          0  // Black background (overrides animations)
#define USR_LAYER_NUM         1  // Num lock indicator
#define USR_LAYER_CAPS        2  // Caps lock indicator
#define USR_LAYER_SCROLL      3  // Scroll lock indicator
#define USR_LAYER_1           4  // Layer 1 indicator
#define USR_LAYER_2           5  // Layer 2 indicator
#define USR_LAYER_3           6  // Layer 3 indicator
#define USR_LAYER_4           7  // Layer 4 indicator

// LED Colors
#define USR_COLOR_CAPS      HSV_RED_DIM     // Caps lock: Red
#define USR_COLOR_SCROLL    HSV_GREEN_DIM   // Scroll lock: Green
#define USR_COLOR_NUM       HSV_BLUE_DIM    // Num lock: Blue
#define USR_COLOR_LAYER1    HSV_MAGENTA_DIM // Layer 1: Magenta
#define USR_COLOR_LAYER2    HSV_PURPLE_DIM  // Layer 2: Purple
#define USR_COLOR_LAYER3    HSV_YELLOW_DIM  // Layer 3: Yellow
#define USR_COLOR_LAYER4    HSV_CYAN_DIM    // Layer 4: Cyan

