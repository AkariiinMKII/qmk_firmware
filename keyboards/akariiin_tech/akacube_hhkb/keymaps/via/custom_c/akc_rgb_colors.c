// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "akc_rgb_colors.h"
#include "akc_custom.h"

// Convert color index to HSV value
HSV akc_pick_dim_color(uint8_t color_index) {
    switch (color_index) {
        // Index 0 reserved for EEPROM reset detection
        case 1:  return (HSV){0,   255, HSV_VAL_DIM};  // Red
        case 2:  return (HSV){21,  255, HSV_VAL_DIM};  // Orange
        case 3:  return (HSV){43,  255, HSV_VAL_DIM};  // Yellow
        case 4:  return (HSV){64,  255, HSV_VAL_DIM};  // Lime
        case 5:  return (HSV){85,  255, HSV_VAL_DIM};  // Green
        case 6:  return (HSV){107, 255, HSV_VAL_DIM};  // Teal
        case 7:  return (HSV){128, 255, HSV_VAL_DIM};  // Cyan
        case 8:  return (HSV){149, 255, HSV_VAL_DIM};  // Azure
        case 9:  return (HSV){170, 255, HSV_VAL_DIM};  // Blue
        case 10: return (HSV){191, 255, HSV_VAL_DIM};  // Purple
        case 11: return (HSV){213, 255, HSV_VAL_DIM};  // Magenta
        case 12: return (HSV){234, 255, HSV_VAL_DIM};  // Rose
        case 13: return (HSV){0,   0,   HSV_VAL_DIM};  // White
        case 14: return (HSV){0,   0,   0};            // Black
        default: return (HSV){0,   0,   0};            // Black (invalid)
    }
}
