// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

// LED Blink Control - Simple show/hide interface for LED 0-7 blink effect

#pragma once

#include "quantum.h"
#include "usr_config.h"

// Fallback values for blink timing
#ifndef USR_BLINK_TIME_ON
#    define USR_BLINK_TIME_ON 300
#endif
#ifndef USR_BLINK_TIME_IDLE
#    define USR_BLINK_TIME_IDLE 200
#endif

// Show LED blink effect on LEDs 0-7
void led_blink_show(void);

// Hide LED blink effect
void led_blink_hide(void);

// Handle blink timing
void led_blink_timer(void);
