// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "usr_config.h"

#define disable     0
#define num_lock    1
#define caps_lock   2
#define scroll_lock 4
#define compose     8
#define kana        16

#ifndef USR_LOCKLED_KEEPTIME
#    define USR_LOCKLED_KEEPTIME 3000
#endif
#ifndef USR_LOCKLED_1
#    define USR_LOCKLED_1 num_lock
#endif
#ifndef USR_LOCKLED_2
#    define USR_LOCKLED_2 caps_lock
#endif
#ifndef USR_LOCKLED_3
#    define USR_LOCKLED_3 scroll_lock
#endif

#if (USR_LOCKLED_1 | USR_LOCKLED_2 | USR_LOCKLED_3) > 0
#    define LOCKLED_SYSTEM_ENABLE
#endif

#ifdef LOCKLED_SYSTEM_ENABLE
void lock_indicator_update(led_t led_state);
void lock_indicator_timer(layer_state_t state);
#endif
void layer_indicator_update(layer_state_t state);
