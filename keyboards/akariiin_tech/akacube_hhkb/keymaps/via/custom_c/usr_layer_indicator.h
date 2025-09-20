// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

// Layer Indicator Display Functions - LED display with optimized caching

#pragma once

#include "quantum.h"
#include "usr_config.h"

// Show layer LEDs based on layer state (cached layer_state_cmp calls)
void layer_indicator_show(layer_state_t state);
