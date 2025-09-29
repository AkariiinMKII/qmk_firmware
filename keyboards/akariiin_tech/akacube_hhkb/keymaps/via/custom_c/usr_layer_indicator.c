// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_layer_indicator.h"

// Show layer indicators with bit checks
void layer_indicator_show(layer_state_t state) {
    rgblight_set_layer_state(0, state > 1);         // Layer background
    rgblight_set_layer_state(1, (state & 2) > 0);   // Layer 1 indicator
    rgblight_set_layer_state(2, (state & 4) > 0);   // Layer 2 indicator
    rgblight_set_layer_state(3, (state & 8) > 0);   // Layer 3 indicator
    rgblight_set_layer_state(4, (state & 16) > 0);  // Layer 4 indicator
}

// Hide all layer indicators
void layer_indicator_hide(void) {
    rgblight_set_layer_state(0, false);
    rgblight_set_layer_state(1, false);
    rgblight_set_layer_state(2, false);
    rgblight_set_layer_state(3, false);
    rgblight_set_layer_state(4, false);
}
