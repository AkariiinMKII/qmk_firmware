// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_layer_indicator.h"

// ============================================================================
// LAYER INDICATOR DISPLAY FUNCTIONS
// ============================================================================

// Show layer LEDs with optimized caching
void layer_indicator_show(layer_state_t state) {
    // Cache layer states first for efficiency
    bool layer1_active = layer_state_cmp(state, 1);
    bool layer2_active = layer_state_cmp(state, 2);
    bool layer3_active = layer_state_cmp(state, 3);
    bool layer4_active = layer_state_cmp(state, 4);

    // Enable background if any layer is active
    bool any_layer_is_active = (layer1_active || layer2_active || layer3_active || layer4_active);

    // Set background first, then individual indicators
    rgblight_set_layer_state(0, any_layer_is_active);  // Layer background
    rgblight_set_layer_state(1, layer1_active);        // Layer 1
    rgblight_set_layer_state(2, layer2_active);        // Layer 2
    rgblight_set_layer_state(3, layer3_active);        // Layer 3
    rgblight_set_layer_state(4, layer4_active);        // Layer 4
}
