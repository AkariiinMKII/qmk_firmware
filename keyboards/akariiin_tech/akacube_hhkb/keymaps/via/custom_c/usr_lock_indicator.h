// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

// Lock Indicator Display Functions - LED display with show/hide interface

#pragma once

#include "quantum.h"

// Display lock indicators with background
void lock_indicator_show(bool num_lock, bool caps_lock, bool scroll_lock);

// Hide all lock indicators
void lock_indicator_hide(void);
