// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "usr_config.h"

// Configuration fallback
#ifndef USR_LOCKLED_KEEPTIME
#    define USR_LOCKLED_KEEPTIME 3000  // Lock LED keep time (ms)
#endif

void lock_indicator_update(led_t led_state);
void layer_indicator_update(layer_state_t state);
void lock_indicator_timer(layer_state_t state);
