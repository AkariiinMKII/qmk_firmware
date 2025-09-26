// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "usr_config.h"
#include "usr_via_config.h"

#ifndef USR_LOCKLED_KEEPTIME
#    define USR_LOCKLED_KEEPTIME 1000
#endif
#ifndef USR_LOCKLED_1
#    define USR_LOCKLED_1 1
#endif
#ifndef USR_LOCKLED_2
#    define USR_LOCKLED_2 2
#endif
#ifndef USR_LOCKLED_3
#    define USR_LOCKLED_3 4
#endif

void lock_indicator_update(led_t led_state);
void lock_indicator_timer(layer_state_t state);
void layer_indicator_update(layer_state_t state);
void usr_refresh_indicator(void);
