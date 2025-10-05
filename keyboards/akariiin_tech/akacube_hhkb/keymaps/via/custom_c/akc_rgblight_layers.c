// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "akc_rgblight_layers.h"
#include "akc_rgb_colors.h"
#include "akc_via_config.h"

// RGB Layer Definitions (ordered by priority: lowest → highest)

// 1. Layer LED background layer (lowest priority - overrides default animations)
static rgblight_segment_t akc_layer_layerled_bg[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_BLACK}, {1, 1, HSV_BLACK}, {2, 1, HSV_BLACK}, {3, 1, HSV_BLACK},
    {4, 1, HSV_BLACK}, {5, 1, HSV_BLACK}, {6, 1, HSV_BLACK}, {7, 1, HSV_BLACK}
);

// 2-5. Layer indicators (single LEDs): layer 0(LED1), layer 1(LED3), layer 2(LED5), layer 3(LED7)
static rgblight_segment_t akc_layer_layerled_mo0[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_BLACK}    // LED 1: Layer 0 (set in init)
);
static rgblight_segment_t akc_layer_layerled_mo1[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 1, HSV_BLACK}    // LED 3: Layer 1 (set in init)
);
static rgblight_segment_t akc_layer_layerled_mo2[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 1, HSV_BLACK}    // LED 5: Layer 2 (set in init)
);
static rgblight_segment_t akc_layer_layerled_mo3[] = RGBLIGHT_LAYER_SEGMENTS(
    {7, 1, HSV_BLACK}    // LED 7: Layer 3 (set in init)
);

// 6. All-black background layer (base layer for all lock LEDs)
static const rgblight_segment_t PROGMEM akc_layer_lockled_bg[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_BLACK}                 // LEDs 0-7: All black
);

// 7-9. Lock LED background layers (show background color if enabled)
static rgblight_segment_t akc_layer_lockled_bg0[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_BLACK}      // LEDs 0-1: Lock 0 area background (set in init)
);
static rgblight_segment_t akc_layer_lockled_bg1[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 2, HSV_BLACK}      // LEDs 3-4: Lock 1 area background (set in init)
);
static rgblight_segment_t akc_layer_lockled_bg2[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 2, HSV_BLACK}      // LEDs 6-7: Lock 2 area background (set in init)
);

// 10-12. Lock indicators (highest priority): lock0(0-1), lock1(3-4), lock2(6-7)
static rgblight_segment_t akc_layer_lockled_0[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_BLACK}       // LEDs 0-1: Lock 0 (set in init)
);
static rgblight_segment_t akc_layer_lockled_1[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 2, HSV_BLACK}       // LEDs 3-4: Lock 1 (set in init)
);
static rgblight_segment_t akc_layer_lockled_2[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 2, HSV_BLACK}       // LEDs 6-7: Lock 2 (set in init)
);

// 13-14. Blink layers (highest priority)
static const rgblight_segment_t PROGMEM akc_layer_blink_bg[] = RGBLIGHT_LAYER_SEGMENTS({0, 8, HSV_BLACK});
static const rgblight_segment_t PROGMEM akc_layer_blink[] = RGBLIGHT_LAYER_SEGMENTS({0, 8, AKC_COLOR_BLINK});

// Layer mapping array
// Priority order: layer background → layer indicators → lock black bg → lock color bgs → lock indicators → blink layers
const rgblight_segment_t* const PROGMEM akc_rgblight_layers[] = RGBLIGHT_LAYERS_LIST(
    akc_layer_layerled_bg,            // 0: Layer background
    akc_layer_layerled_mo0,           // 1: Layer 0
    akc_layer_layerled_mo1,           // 2: Layer 1
    akc_layer_layerled_mo2,           // 3: Layer 2
    akc_layer_layerled_mo3,           // 4: Layer 3
    akc_layer_lockled_bg,             // 5: All-black lock background
    akc_layer_lockled_bg0,            // 6: Lock 0 color background
    akc_layer_lockled_bg1,            // 7: Lock 1 color background
    akc_layer_lockled_bg2,            // 8: Lock 2 color background
    akc_layer_lockled_0,              // 9: Lock 0 indicator
    akc_layer_lockled_1,              // 10: Lock 1 indicator
    akc_layer_lockled_2,              // 11: Lock 2 indicator
    akc_layer_blink_bg,               // 12: Blink background
    akc_layer_blink                   // 13: Blink color
);

// Helper function to safely set LED color(s) in a layer segment
static void set_rgblight_layer_color(rgblight_segment_t* segment, uint8_t start_led, uint8_t led_count, HSV color) {
    segment->index = start_led;
    segment->count = led_count;
    segment->hue = color.h;
    segment->sat = color.s;
    segment->val = color.v;
}

void akc_rgblight_layers_init(void) {
    // Load VIA config colors
    HSV layer_bg_color = akc_pick_dim_color(akc_via_get_config(LAYER_LED, OFF_COLOR));
    HSV layer_on_color = akc_pick_dim_color(akc_via_get_config(LAYER_LED, ON_COLOR));

    for (uint8_t i = 1; i < 8; i += 2) {
        set_rgblight_layer_color(&akc_layer_layerled_bg[i], i, 1, layer_bg_color);
    }

    rgblight_segment_t* layer_on_segments[] = {
        akc_layer_layerled_mo0,
        akc_layer_layerled_mo1,
        akc_layer_layerled_mo2,
        akc_layer_layerled_mo3
    };
    for (uint8_t i = 0; i < 4; i++) {
        set_rgblight_layer_color(layer_on_segments[i], i * 2 + 1, 1, layer_on_color);
    }

    rgblight_segment_t* lock_bg_segments[] = {
        akc_layer_lockled_bg0,
        akc_layer_lockled_bg1,
        akc_layer_lockled_bg2
    };
    for (uint8_t i = 0; i < 3; i++) {
        HSV lock_bg_color = akc_pick_dim_color(akc_via_get_config(i, OFF_COLOR));
        set_rgblight_layer_color(lock_bg_segments[i], i * 3, 2, lock_bg_color);
    }

    rgblight_segment_t* lock_on_segments[] = {
        akc_layer_lockled_0,
        akc_layer_lockled_1,
        akc_layer_lockled_2
    };
    for (uint8_t i = 0; i < 3; i++) {
        HSV lock_on_color = akc_pick_dim_color(akc_via_get_config(i, ON_COLOR));
        set_rgblight_layer_color(lock_on_segments[i], i * 3, 2, lock_on_color);
    }

    // Set up the RGB layer definitions
    rgblight_layers = akc_rgblight_layers;

    // Initialize all layers to off state
    for (uint8_t i = 0; i < 14; i++) {
        rgblight_set_layer_state(i, false);
    }
}
