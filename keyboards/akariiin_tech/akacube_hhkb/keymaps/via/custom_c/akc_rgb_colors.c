// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "akc_rgb_colors.h"
#include "akc_custom.h"

// Convert color index to HSV value
HSV akc_pick_dim_color(uint8_t color_index) {
    switch (color_index) {
        // Index 0 reserved for EEPROM reset detection
        case 1:  return (HSV){HSV_RED_DIM};     // Red
        case 2:  return (HSV){HSV_ORANGE_DIM};  // Orange
        case 3:  return (HSV){HSV_YELLOW_DIM};  // Yellow
        case 4:  return (HSV){HSV_LIME_DIM};    // Lime
        case 5:  return (HSV){HSV_GREEN_DIM};   // Green
        case 6:  return (HSV){HSV_TEAL_DIM};    // Teal
        case 7:  return (HSV){HSV_CYAN_DIM};    // Cyan
        case 8:  return (HSV){HSV_AZURE_DIM};   // Azure
        case 9:  return (HSV){HSV_BLUE_DIM};    // Blue
        case 10: return (HSV){HSV_PURPLE_DIM};  // Purple
        case 11: return (HSV){HSV_MAGENTA_DIM}; // Magenta
        case 12: return (HSV){HSV_ROSE_DIM};    // Rose
        case 13: return (HSV){HSV_WHITE_DIM};   // White
        case 14: return (HSV){HSV_BLACK};       // Black
        default: return (HSV){HSV_BLACK};       // Black (invalid)
    }
}
