// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

// LED control for lock and layer indicators

#pragma once

#include "quantum.h"
#include "usr_config.h"

// Configuration fallback
#ifndef USR_LOCKLED_KEEPTIME
#    define USR_LOCKLED_KEEPTIME 3000  // Lock LED keep time (ms)
#endif

// Update lock indicators
void lock_indicator_update(led_t led_state);

// Update layer indicators
void layer_indicator_update(layer_state_t state);

// Handle lock timeout
void lock_indicator_timer(layer_state_t state);
