// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "akc_config.h"

#ifndef AKC_BLINK_TIME_ON
#    define AKC_BLINK_TIME_ON 200
#endif
#ifndef AKC_BLINK_TIME_IDLE
#    define AKC_BLINK_TIME_IDLE 200
#endif

void akc_led_blink_show(void);
void akc_led_blink_hide(void);
void akc_led_blink_timer(void);
bool akc_led_blink_timer_active(void);
