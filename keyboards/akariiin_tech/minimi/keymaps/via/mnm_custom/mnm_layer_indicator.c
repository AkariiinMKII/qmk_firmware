// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "mnm_custom.h"

// Show layer indicators with bit checks
void mnm_layer_indicator_show(layer_state_t state) {
    rgblight_set_layer_state(0, (state & 2) > 0);   // Layer 1 indicator
    rgblight_set_layer_state(1, (state & 4) > 0);   // Layer 2 indicator
    rgblight_set_layer_state(2, (state & 8) > 0);   // Layer 3 indicator
}

// Hide all layer indicators
void mnm_layer_indicator_hide(void) {
    for (uint8_t i = 0; i < 3; i++) {
        rgblight_set_layer_state(i, false);
    }
}
