// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

// LED control for lock states and layer indicators

#pragma once

#include "quantum.h"
#include "usr_config.h"

// Update lock LED indicators and start timeout timer
void usr_led_lock_update(led_t led_state);

// Update layer LED indicators
void usr_led_layer_update(layer_state_t state);

// Handle LED timeout (call from matrix_scan_user)
void usr_led_scan(layer_state_t state);

