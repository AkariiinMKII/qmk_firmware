// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_rgblight_layers.h"
#include "usr_via_config.h"
#include "usr_rgb_colors.h"

// Function to get HSV dim color directly from VIA config

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

// 6. All-black background layer (base layer for all lock LEDs)
static const rgblight_segment_t PROGMEM usr_layer_lockled_bg[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_BLACK}                 // LEDs 0-7: All black
);

// 7-9. Lock LED background layers (show background color if enabled)
static const rgblight_segment_t PROGMEM usr_layer_lockled_bg0[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, USR_COLOR_LOCKLED_BG}      // LEDs 0-1: Lock 0 area background
);
static const rgblight_segment_t PROGMEM usr_layer_lockled_bg1[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 2, USR_COLOR_LOCKLED_BG}      // LEDs 3-4: Lock 1 area background
);
static const rgblight_segment_t PROGMEM usr_layer_lockled_bg2[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 2, USR_COLOR_LOCKLED_BG}      // LEDs 6-7: Lock 2 area background
);

// 10-12. Lock indicators (highest priority): lock0(0-1), lock1(3-4), lock2(6-7)
static const rgblight_segment_t PROGMEM usr_layer_lockled_0[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, USR_COLOR_LOCKLED_0}       // LEDs 0-1: Lock 0
);
static const rgblight_segment_t PROGMEM usr_layer_lockled_1[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 2, USR_COLOR_LOCKLED_1}       // LEDs 3-4: Lock 1
);
static const rgblight_segment_t PROGMEM usr_layer_lockled_2[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 2, USR_COLOR_LOCKLED_2}       // LEDs 6-7: Lock 2
);

// 13-14. Blink layers (highest priority)
static const rgblight_segment_t PROGMEM usr_layer_blink_bg[] = RGBLIGHT_LAYER_SEGMENTS({0, 8, HSV_BLACK});
static const rgblight_segment_t PROGMEM usr_layer_blink[] = RGBLIGHT_LAYER_SEGMENTS({0, 8, USR_COLOR_BLINK});

// Layer mapping array
// Priority order: layer background → layer indicators → lock black bg → lock color bgs → lock indicators → blink layers
const rgblight_segment_t* const PROGMEM usr_rgblight_layers[] = RGBLIGHT_LAYERS_LIST(
    usr_layer_layerled_bg,            // 0: Layer background
    usr_layer_layerled_mo1,           // 1: Layer 1
    usr_layer_layerled_mo2,           // 2: Layer 2
    usr_layer_layerled_mo3,           // 3: Layer 3
    usr_layer_layerled_mo4,           // 4: Layer 4
    usr_layer_lockled_bg,             // 5: All-black lock background
    usr_layer_lockled_bg0,            // 6: Lock 0 color background
    usr_layer_lockled_bg1,            // 7: Lock 1 color background
    usr_layer_lockled_bg2,            // 8: Lock 2 color background
    usr_layer_lockled_0,              // 9: Lock 0 indicator
    usr_layer_lockled_1,              // 10: Lock 1 indicator
    usr_layer_lockled_2,              // 11: Lock 2 indicator
    usr_layer_blink_bg,               // 12: Blink background
    usr_layer_blink                   // 13: Blink color
);

void usr_rgblight_layers_init(void) {
    // Set up the RGB layer definitions
    rgblight_layers = usr_rgblight_layers;

    // Initialize all layers to known states (all off)
    // Layer indicators
    rgblight_set_layer_state(0, false);   // Layer background off
    rgblight_set_layer_state(1, false);   // Layer 1 off
    rgblight_set_layer_state(2, false);   // Layer 2 off
    rgblight_set_layer_state(3, false);   // Layer 3 off
    rgblight_set_layer_state(4, false);   // Layer 4 off

    // Lock LED layers
    rgblight_set_layer_state(5, false);   // All-black lock background off
    rgblight_set_layer_state(6, false);   // Lock 0 color background off
    rgblight_set_layer_state(7, false);   // Lock 1 color background off
    rgblight_set_layer_state(8, false);   // Lock 2 color background off
    rgblight_set_layer_state(9, false);   // Lock 0 indicator off
    rgblight_set_layer_state(10, false);  // Lock 1 indicator off
    rgblight_set_layer_state(11, false);  // Lock 2 indicator off

    // Blink layers
    rgblight_set_layer_state(12, false);  // Blink background off
    rgblight_set_layer_state(13, false);  // Blink color off
}
