// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "akc_config.h"
#include "akc_led_control.h"

#ifndef AKC_COLOR_LAYERLED_BG
#    define AKC_COLOR_LAYERLED_BG     HSV_RED_DIM
#endif
#ifndef AKC_COLOR_LAYERLED_MO0
#    define AKC_COLOR_LAYERLED_MO0    HSV_BLUE_DIM
#endif
#ifndef AKC_COLOR_LAYERLED_MO1
#    define AKC_COLOR_LAYERLED_MO1    HSV_BLUE_DIM
#endif
#ifndef AKC_COLOR_LAYERLED_MO2
#    define AKC_COLOR_LAYERLED_MO2    HSV_BLUE_DIM
#endif
#ifndef AKC_COLOR_LAYERLED_MO3
#    define AKC_COLOR_LAYERLED_MO3    HSV_BLUE_DIM
#endif
#ifndef AKC_COLOR_LOCKLED_BG
#    define AKC_COLOR_LOCKLED_BG      HSV_RED_DIM
#endif
#ifndef AKC_COLOR_LOCKLED_0
#    define AKC_COLOR_LOCKLED_0       HSV_GREEN_DIM
#endif
#ifndef AKC_COLOR_LOCKLED_1
#    define AKC_COLOR_LOCKLED_1       HSV_GREEN_DIM
#endif
#ifndef AKC_COLOR_LOCKLED_2
#    define AKC_COLOR_LOCKLED_2       HSV_GREEN_DIM
#endif
#ifndef AKC_COLOR_BLINK
#    define AKC_COLOR_BLINK           HSV_RED_DIM
#endif

#if AKC_LOCKLED_0 > 0
#    define AKC_COLOR_LOCKLED_BG0 AKC_COLOR_LOCKLED_BG
#else
#    define AKC_COLOR_LOCKLED_BG0 HSV_BLACK
#endif
#if AKC_LOCKLED_1 > 0
#    define AKC_COLOR_LOCKLED_BG1 AKC_COLOR_LOCKLED_BG
#else
#    define AKC_COLOR_LOCKLED_BG1 HSV_BLACK
#endif
#if AKC_LOCKLED_2 > 0
#    define AKC_COLOR_LOCKLED_BG2 AKC_COLOR_LOCKLED_BG
#else
#    define AKC_COLOR_LOCKLED_BG2 HSV_BLACK
#endif

void akc_rgblight_layers_init(void);
