// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_rgblight_layers.h"
#include "usr_config.h"

// RGB Layer Definitions (ordered by priority: lowest → highest)

// 1. Layer LED background layer (lowest priority - overrides default animations)
// Background color for layer positions (1,3,5,7), black for others (0,2,4,6)
static const rgblight_segment_t PROGMEM usr_layer_layerled_bg[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_BLACK},                // LED 0: Black
    {1, 1, USR_COLOR_LAYERLED_BG},    // LED 1: Layer 1 area background
    {2, 1, HSV_BLACK},                // LED 2: Black
    {3, 1, USR_COLOR_LAYERLED_BG},    // LED 3: Layer 2 area background
    {4, 1, HSV_BLACK},                // LED 4: Black
    {5, 1, USR_COLOR_LAYERLED_BG},    // LED 5: Layer 3 area background
    {6, 1, HSV_BLACK},                // LED 6: Black
    {7, 1, USR_COLOR_LAYERLED_BG}     // LED 7: Layer 4 area background
);

// 2-5. Layer indicators (single LEDs): layer 1(LED1), layer 2(LED3), layer 3(LED5), layer 4(LED7)
static const rgblight_segment_t PROGMEM usr_layer_layerled_mo1[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, USR_COLOR_LAYERLED_MO1}    // LED 1: Layer 1
);
static const rgblight_segment_t PROGMEM usr_layer_layerled_mo2[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 1, USR_COLOR_LAYERLED_MO2}    // LED 3: Layer 2
);
static const rgblight_segment_t PROGMEM usr_layer_layerled_mo3[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 1, USR_COLOR_LAYERLED_MO3}    // LED 5: Layer 3
);
static const rgblight_segment_t PROGMEM usr_layer_layerled_mo4[] = RGBLIGHT_LAYER_SEGMENTS(
    {7, 1, USR_COLOR_LAYERLED_MO4}    // LED 7: Layer 4
);

// 6. Lock LED background layer
// Background color for lock positions (0,1,3,4,6,7), black for layer-only positions (2,5)
static const rgblight_segment_t PROGMEM usr_layer_lockled_bg[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, USR_COLOR_LOCKLED_BG},     // LEDs 0-1: Num lock area background
    {2, 1, HSV_BLACK},                // LED 2: Black
    {3, 2, USR_COLOR_LOCKLED_BG},     // LEDs 3-4: Caps lock area background
    {5, 1, HSV_BLACK},                // LED 5: Black
    {6, 2, USR_COLOR_LOCKLED_BG}      // LEDs 6-7: Scroll lock area background
);

// 7-9. Lock indicators (highest priority): num(0-1), caps(3-4), scroll(6-7)
static const rgblight_segment_t PROGMEM usr_layer_lockled_num[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, USR_COLOR_LOCKLED_NUM}     // LEDs 0-1: Num lock
);
static const rgblight_segment_t PROGMEM usr_layer_lockled_caps[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 2, USR_COLOR_LOCKLED_CAPS}    // LEDs 3-4: Caps lock
);
static const rgblight_segment_t PROGMEM usr_layer_lockled_scroll[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 2, USR_COLOR_LOCKLED_SCROLL}  // LEDs 6-7: Scroll lock
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
    // Layer indicators
    rgblight_set_layer_state(0, false);  // Layer background off
    rgblight_set_layer_state(1, false);  // Layer 1 off
    rgblight_set_layer_state(2, false);  // Layer 2 off
    rgblight_set_layer_state(3, false);  // Layer 3 off
    rgblight_set_layer_state(4, false);  // Layer 4 off

    // Lock indicators
    rgblight_set_layer_state(5, false);  // Lock background off
    rgblight_set_layer_state(6, false);  // Num lock off
    rgblight_set_layer_state(7, false);  // Caps lock off
    rgblight_set_layer_state(8, false);  // Scroll lock off
}
