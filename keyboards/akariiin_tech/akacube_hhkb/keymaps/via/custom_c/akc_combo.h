// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "akc_config.h"

#ifndef AKC_COMBO_MOD1
#    define AKC_COMBO_MOD1 KC_LSFT
#endif
#ifndef AKC_COMBO_MOD2
#    define AKC_COMBO_MOD2 KC_RSFT
#endif

bool akc_combo_check(uint16_t keycode, bool pressed);
void akc_combo_handler(void);
bool akc_combo_any_active(void);
