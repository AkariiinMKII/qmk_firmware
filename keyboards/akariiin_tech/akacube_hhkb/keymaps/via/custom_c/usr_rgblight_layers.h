// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "usr_config.h"

#ifndef USR_COLOR_LAYERLED_BG
#    define USR_COLOR_LAYERLED_BG     HSV_RED_DIM
#endif
#ifndef USR_COLOR_LAYERLED_MO1
#    define USR_COLOR_LAYERLED_MO1    HSV_BLUE_DIM
#endif
#ifndef USR_COLOR_LAYERLED_MO2
#    define USR_COLOR_LAYERLED_MO2    HSV_BLUE_DIM
#endif
#ifndef USR_COLOR_LAYERLED_MO3
#    define USR_COLOR_LAYERLED_MO3    HSV_BLUE_DIM
#endif
#ifndef USR_COLOR_LAYERLED_MO4
#    define USR_COLOR_LAYERLED_MO4    HSV_BLUE_DIM
#endif
#ifndef USR_COLOR_LOCKLED_BG
#    define USR_COLOR_LOCKLED_BG      HSV_RED_DIM
#endif
#ifndef USR_COLOR_LOCKLED_1
#    define USR_COLOR_LOCKLED_1       HSV_GREEN_DIM
#endif
#ifndef USR_COLOR_LOCKLED_2
#    define USR_COLOR_LOCKLED_2       HSV_GREEN_DIM
#endif
#ifndef USR_COLOR_LOCKLED_3
#    define USR_COLOR_LOCKLED_3       HSV_GREEN_DIM
#endif
#ifndef USR_COLOR_BLINK
#    define USR_COLOR_BLINK           HSV_RED_DIM
#endif

void usr_rgblight_layers_init(void);
