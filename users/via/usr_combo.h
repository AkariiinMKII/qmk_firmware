// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

// Simple combo system: two modifier keys + one action key

#pragma once

#include "quantum.h"
#include "usr_config.h"

// Usage: Hold MOD1 + MOD2, then press action key
// Configure combos in usr_config.h

// Call this from process_record_user()
bool usr_combo_process(uint16_t keycode, bool pressed);

// Call this from matrix_scan_user()
void usr_combo_resolver(void);
