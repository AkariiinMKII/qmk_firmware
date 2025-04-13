// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "akc_custom.h"

// Show layer indicators with bit checks
void akc_layer_indicator_show(layer_state_t state) {
    rgblight_set_layer_state(0, true);              // Layer background
    rgblight_set_layer_state(1, (state & 1) > 0);   // Layer 0 indicator
    rgblight_set_layer_state(2, (state & 2) > 0);   // Layer 1 indicator
    rgblight_set_layer_state(3, (state & 4) > 0);   // Layer 2 indicator
    rgblight_set_layer_state(4, (state & 8) > 0);   // Layer 3 indicator
}

// Hide all layer indicators
void akc_layer_indicator_hide(void) {
    rgblight_set_layer_state(0, false);
    rgblight_set_layer_state(1, false);
    rgblight_set_layer_state(2, false);
    rgblight_set_layer_state(3, false);
    rgblight_set_layer_state(4, false);
}
