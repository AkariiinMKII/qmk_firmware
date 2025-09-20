// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_layer_indicator.h"

// ============================================================================
// LAYER INDICATOR DISPLAY FUNCTIONS
// ============================================================================

// Initialize layer indicator system
void layer_indicator_init(void) {
    // Nothing needed - RGB layers handled elsewhere
}

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
    rgblight_set_layer_state(USR_LAYER_LAYERLED_BG, any_layer_is_active);
    rgblight_set_layer_state(USR_LAYER_LAYERLED_MO1, layer1_active);
    rgblight_set_layer_state(USR_LAYER_LAYERLED_MO2, layer2_active);
    rgblight_set_layer_state(USR_LAYER_LAYERLED_MO3, layer3_active);
    rgblight_set_layer_state(USR_LAYER_LAYERLED_MO4, layer4_active);
}
