// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

// LED control for lock and layer indicators

#pragma once

#include "quantum.h"
#include "usr_config.h"

// Initialize LED systems
void usr_led_control_init(void);

// Update lock indicators
void lock_indicator_update(led_t led_state);

// Update layer indicators
void layer_indicator_update(layer_state_t state);

// Handle lock timeout
void lock_indicator_timer(layer_state_t state);
