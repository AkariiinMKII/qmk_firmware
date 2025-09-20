// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

// HSV color definitions for LED effects

#pragma once

#include "quantum.h"

#define HSV_VAL_DIM 96  // Dimmed brightness level

// HSV colors (Hue, Saturation, Value)
#define HSV_RED_DIM      0,   255, HSV_VAL_DIM
#define HSV_YELLOW_DIM   43,  255, HSV_VAL_DIM
#define HSV_GREEN_DIM    85,  255, HSV_VAL_DIM
#define HSV_CYAN_DIM     128, 255, HSV_VAL_DIM
#define HSV_BLUE_DIM     170, 255, HSV_VAL_DIM
#define HSV_PURPLE_DIM   191, 255, HSV_VAL_DIM
#define HSV_MAGENTA_DIM  213, 255, HSV_VAL_DIM
#define HSV_BLACK        0,     0, 0
