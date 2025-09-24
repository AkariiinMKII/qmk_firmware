// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

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

void led_blink_show(void);
void led_blink_hide(void);
void led_blink_timer(void);
