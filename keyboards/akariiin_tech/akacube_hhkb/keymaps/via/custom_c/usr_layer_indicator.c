// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_layer_indicator.h"

// Show layer indicators with bit checks
void layer_indicator_show(layer_state_t state) {
    rgblight_set_layer_state(0, state > 1);         // Background
    rgblight_set_layer_state(1, (state & 2) > 0);   // Layer 1
    rgblight_set_layer_state(2, (state & 4) > 0);   // Layer 2
    rgblight_set_layer_state(3, (state & 8) > 0);   // Layer 3
    rgblight_set_layer_state(4, (state & 16) > 0);  // Layer 4
}
