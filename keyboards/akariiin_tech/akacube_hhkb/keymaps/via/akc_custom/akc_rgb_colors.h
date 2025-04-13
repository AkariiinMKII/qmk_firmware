// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

// HSV color definitions for LED effects

#pragma once

// Brightness levels
#define HSV_VAL_DIM      96   // Dimmed brightness level
#define HSV_VAL_BRIGHT   192  // Bright brightness level
#define HSV_VAL_MAX      255  // Maximum brightness level
#define HSV_VAL_DARK     48   // Dark brightness level
#define HSV_VAL_OFF      0    // Off brightness level

// Basic Colors - Full Brightness
#define HSV_RED_FULL     0,   255, HSV_VAL_MAX
#define HSV_ORANGE_FULL  21,  255, HSV_VAL_MAX
#define HSV_YELLOW_FULL  43,  255, HSV_VAL_MAX
#define HSV_LIME_FULL    64,  255, HSV_VAL_MAX
#define HSV_GREEN_FULL   85,  255, HSV_VAL_MAX
#define HSV_TEAL_FULL    107, 255, HSV_VAL_MAX
#define HSV_CYAN_FULL    128, 255, HSV_VAL_MAX
#define HSV_AZURE_FULL   149, 255, HSV_VAL_MAX
#define HSV_BLUE_FULL    170, 255, HSV_VAL_MAX
#define HSV_PURPLE_FULL  191, 255, HSV_VAL_MAX
#define HSV_MAGENTA_FULL 213, 255, HSV_VAL_MAX
#define HSV_ROSE_FULL    234, 255, HSV_VAL_MAX

// Basic Colors - Bright Level
#define HSV_RED_BRIGHT     0,   255, HSV_VAL_BRIGHT
#define HSV_ORANGE_BRIGHT  21,  255, HSV_VAL_BRIGHT
#define HSV_YELLOW_BRIGHT  43,  255, HSV_VAL_BRIGHT
#define HSV_LIME_BRIGHT    64,  255, HSV_VAL_BRIGHT
#define HSV_GREEN_BRIGHT   85,  255, HSV_VAL_BRIGHT
#define HSV_TEAL_BRIGHT    107, 255, HSV_VAL_BRIGHT
#define HSV_CYAN_BRIGHT    128, 255, HSV_VAL_BRIGHT
#define HSV_AZURE_BRIGHT   149, 255, HSV_VAL_BRIGHT
#define HSV_BLUE_BRIGHT    170, 255, HSV_VAL_BRIGHT
#define HSV_PURPLE_BRIGHT  191, 255, HSV_VAL_BRIGHT
#define HSV_MAGENTA_BRIGHT 213, 255, HSV_VAL_BRIGHT
#define HSV_ROSE_BRIGHT    234, 255, HSV_VAL_BRIGHT

// Basic Colors - Dimmed Level (Original)
#define HSV_RED_DIM      0,   255, HSV_VAL_DIM
#define HSV_ORANGE_DIM   21,  255, HSV_VAL_DIM
#define HSV_YELLOW_DIM   43,  255, HSV_VAL_DIM
#define HSV_LIME_DIM     64,  255, HSV_VAL_DIM
#define HSV_GREEN_DIM    85,  255, HSV_VAL_DIM
#define HSV_TEAL_DIM     107, 255, HSV_VAL_DIM
#define HSV_CYAN_DIM     128, 255, HSV_VAL_DIM
#define HSV_AZURE_DIM    149, 255, HSV_VAL_DIM
#define HSV_BLUE_DIM     170, 255, HSV_VAL_DIM
#define HSV_PURPLE_DIM   191, 255, HSV_VAL_DIM
#define HSV_MAGENTA_DIM  213, 255, HSV_VAL_DIM
#define HSV_ROSE_DIM     234, 255, HSV_VAL_DIM
#define HSV_WHITE_DIM    0,   0,   HSV_VAL_DIM

// Basic Colors - Dark Level
#define HSV_RED_DARK      0,   255, HSV_VAL_DARK
#define HSV_ORANGE_DARK   21,  255, HSV_VAL_DARK
#define HSV_YELLOW_DARK   43,  255, HSV_VAL_DARK
#define HSV_LIME_DARK     64,  255, HSV_VAL_DARK
#define HSV_GREEN_DARK    85,  255, HSV_VAL_DARK
#define HSV_TEAL_DARK     107, 255, HSV_VAL_DARK
#define HSV_CYAN_DARK     128, 255, HSV_VAL_DARK
#define HSV_AZURE_DARK    149, 255, HSV_VAL_DARK
#define HSV_BLUE_DARK     170, 255, HSV_VAL_DARK
#define HSV_PURPLE_DARK   191, 255, HSV_VAL_DARK
#define HSV_MAGENTA_DARK  213, 255, HSV_VAL_DARK
#define HSV_ROSE_DARK     234, 255, HSV_VAL_DARK

// Pastel Colors (Lower Saturation)
#define HSV_RED_PASTEL      0,   128, HSV_VAL_BRIGHT
#define HSV_ORANGE_PASTEL   21,  128, HSV_VAL_BRIGHT
#define HSV_YELLOW_PASTEL   43,  128, HSV_VAL_BRIGHT
#define HSV_LIME_PASTEL     64,  128, HSV_VAL_BRIGHT
#define HSV_GREEN_PASTEL    85,  128, HSV_VAL_BRIGHT
#define HSV_TEAL_PASTEL     107, 128, HSV_VAL_BRIGHT
#define HSV_CYAN_PASTEL     128, 128, HSV_VAL_BRIGHT
#define HSV_AZURE_PASTEL    149, 128, HSV_VAL_BRIGHT
#define HSV_BLUE_PASTEL     170, 128, HSV_VAL_BRIGHT
#define HSV_PURPLE_PASTEL   191, 128, HSV_VAL_BRIGHT
#define HSV_MAGENTA_PASTEL  213, 128, HSV_VAL_BRIGHT
#define HSV_ROSE_PASTEL     234, 128, HSV_VAL_BRIGHT

// Gray variations
#define HSV_GRAY         0, 0, 128
#define HSV_GRAY_LIGHT   0, 0, 160
#define HSV_GRAY_DARK    0, 0, 64

// Black
#define HSV_BLACK        0, 0, 0
