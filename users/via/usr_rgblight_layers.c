// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_rgblight_layers.h"
#include "usr_config.h"

// RGB Layer Definitions
// Lock LED background layer (overrides default animations)
// Dim red for lock positions (0,1,3,4,6,7), black for layer-only positions (2,5)
static const rgblight_segment_t PROGMEM usr_layer_lockled_bg[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_RED_DIM},      // LEDs 0-1: Dim red (num lock area)
    {2, 1, HSV_BLACK},        // LED 2: Black (layer-only area)
    {3, 2, HSV_RED_DIM},      // LEDs 3-4: Dim red (caps lock area)
    {5, 1, HSV_BLACK},        // LED 5: Black (layer-only area)
    {6, 2, HSV_RED_DIM}       // LEDs 6-7: Dim red (scroll lock area)
);

// Lock indicators: num(0-1), caps(3-4), scroll(6-7)
static const rgblight_segment_t PROGMEM usr_layer_lockled_num[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, USR_COLOR_NUM}     // LEDs 0-1: Num lock
);
static const rgblight_segment_t PROGMEM usr_layer_lockled_caps[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 2, USR_COLOR_CAPS}    // LEDs 3-4: Caps lock
);
static const rgblight_segment_t PROGMEM usr_layer_lockled_scroll[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 2, USR_COLOR_SCROLL}  // LEDs 6-7: Scroll lock
);

// Layer indicators (single LEDs): layer 1(LED1), layer 2(LED3), layer 3(LED5), layer 4(LED7)
static const rgblight_segment_t PROGMEM usr_layer_layerled_mo1[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, USR_COLOR_LAYER1}  // LED 1: Layer 1
);
static const rgblight_segment_t PROGMEM usr_layer_layerled_mo2[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 1, USR_COLOR_LAYER2}  // LED 3: Layer 2
);
static const rgblight_segment_t PROGMEM usr_layer_layerled_mo3[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 1, USR_COLOR_LAYER3}  // LED 5: Layer 3
);
static const rgblight_segment_t PROGMEM usr_layer_layerled_mo4[] = RGBLIGHT_LAYER_SEGMENTS(
    {7, 1, USR_COLOR_LAYER4}  // LED 7: Layer 4
);

// Layer LED background layer (overrides default animations for layer display)
// Dim red for layer positions (1,3,5,7), black for others (0,2,4,6)
static const rgblight_segment_t PROGMEM usr_layer_layerled_bg[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_BLACK},        // LED 0: Black
    {1, 1, HSV_RED_DIM},      // LED 1: Dim red (layer 1 area)
    {2, 1, HSV_BLACK},        // LED 2: Black
    {3, 1, HSV_RED_DIM},      // LED 3: Dim red (layer 2 area)
    {4, 1, HSV_BLACK},        // LED 4: Black
    {5, 1, HSV_RED_DIM},      // LED 5: Dim red (layer 3 area)
    {6, 1, HSV_BLACK},        // LED 6: Black
    {7, 1, HSV_RED_DIM}       // LED 7: Dim red (layer 4 area)
);

// Layer mapping array
// Priority order: layer background (lowest) → layer indicators → lock background → lock indicators (highest priority)
const rgblight_segment_t* const PROGMEM usr_rgblight_layers[] = RGBLIGHT_LAYERS_LIST(
    usr_layer_layerled_bg,
    usr_layer_layerled_mo1,
    usr_layer_layerled_mo2,
    usr_layer_layerled_mo3,
    usr_layer_layerled_mo4,
    usr_layer_lockled_bg,
    usr_layer_lockled_num,
    usr_layer_lockled_caps,
    usr_layer_lockled_scroll
);

void usr_rgblight_layers_init(void) {
    // Set up the RGB layer definitions
    rgblight_layers = usr_rgblight_layers;
    
    // Initialize all layers to known states (all off)
    // Layer LED system
    rgblight_set_layer_state(USR_LAYER_LAYERLED_BG, false);   // Layer background off
    rgblight_set_layer_state(USR_LAYER_LAYERLED_MO1, false);  // Layer 1 off
    rgblight_set_layer_state(USR_LAYER_LAYERLED_MO2, false);  // Layer 2 off
    rgblight_set_layer_state(USR_LAYER_LAYERLED_MO3, false);  // Layer 3 off
    rgblight_set_layer_state(USR_LAYER_LAYERLED_MO4, false);  // Layer 4 off
    
    // Lock LED system
    rgblight_set_layer_state(USR_LAYER_LOCKLED_BG, false);    // Lock background off
    rgblight_set_layer_state(USR_LAYER_LOCKLED_NUM, false);   // Num lock off
    rgblight_set_layer_state(USR_LAYER_LOCKLED_CAPS, false);  // Caps lock off
    rgblight_set_layer_state(USR_LAYER_LOCKLED_SCROLL, false); // Scroll lock off
}
