// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "mnm_custom.h"
#include "mnm_rgb_colors.h"

// Initialize layer indicator layers
static rgblight_segment_t light_layer_layerled_mo1[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 0, 0, 0});
static rgblight_segment_t light_layer_layerled_mo2[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 0, 0, 0});
static rgblight_segment_t light_layer_layerled_mo3[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 0, 0, 0});

// Initialize lock indicator layers
static rgblight_segment_t light_layer_lockled_bg0[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 0, 0, 0});
static rgblight_segment_t light_layer_lockled_bg1[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 0, 0, 0});
static rgblight_segment_t light_layer_lockled_0[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 0, 0, 0});
static rgblight_segment_t light_layer_lockled_1[] = RGBLIGHT_LAYER_SEGMENTS({0, 0, 0, 0, 0});

// Initialize blink effect layers
static const rgblight_segment_t PROGMEM light_layer_blink_bg[] = RGBLIGHT_LAYER_SEGMENTS({0, RGBLIGHT_LED_COUNT, HSV_BLACK});
static const rgblight_segment_t PROGMEM light_layer_blink[] = RGBLIGHT_LAYER_SEGMENTS({0, RGBLIGHT_LED_COUNT, MNM_COLOR_BLINK});

// Initialize light layer mapping (priority: lowest → highest)
static const rgblight_segment_t* const PROGMEM mnm_rgblight_layers[] = RGBLIGHT_LAYERS_LIST(
    light_layer_layerled_mo1,         // 0: Layer 1 indicator (on state color)
    light_layer_layerled_mo2,         // 1: Layer 2 indicator (on state color)
    light_layer_layerled_mo3,         // 2: Layer 3 indicator (on state color)
    light_layer_lockled_bg0,          // 3: Lock 0 background (off state color)
    light_layer_lockled_bg1,          // 4: Lock 1 background (off state color)
    light_layer_lockled_0,            // 5: Lock 0 indicator (on state color)
    light_layer_lockled_1,            // 6: Lock 1 indicator (on state color)
    light_layer_blink_bg,             // 7: Blink background (all black)
    light_layer_blink                 // 8: Blink color
);

// Helper function for LED color update
static void set_rgblight_layer_color(rgblight_segment_t* segment, uint8_t start_led, uint8_t led_count, HSV color) {
    segment->index = start_led;
    segment->count = led_count;
    segment->hue = color.h;
    segment->sat = color.s;
    segment->val = color.v;
}

// Indicator LED positions
static const uint8_t layerled_positions[] = MNM_LAYERLED_POSITIONS;
static const uint8_t lockled_positions[] = MNM_LOCKLED_POSITIONS;

void mnm_rgblight_layers_init(void) {
    // Set on state colors for each layer LED position
    rgblight_segment_t* layer_on_segments[] = {
        light_layer_layerled_mo1,
        light_layer_layerled_mo2
    };
    HSV layer_on_color = mnm_color_pick_dim_color(mnm_via_get_config(LAYER_LED, ON_COLOR));
    for (uint8_t i = 0; i < 2; i++) {
        set_rgblight_layer_color(layer_on_segments[i], layerled_positions[i], MNM_LAYERLED_LENGTH, layer_on_color);
    }
    HSV layer3_on_color = mnm_color_pick_dim_color(mnm_via_get_config(LAYER_LED, L3_COLOR));
    set_rgblight_layer_color(light_layer_layerled_mo3, 0, 4, layer3_on_color);

    // Set off state colors for each lock LED position
    rgblight_segment_t* lock_bg_segments[] = {
        light_layer_lockled_bg0,
        light_layer_lockled_bg1
    };
    for (uint8_t i = 0; i < 2; i++) {
        HSV lock_bg_color = mnm_color_pick_dim_color(mnm_via_get_config(i, OFF_COLOR));
        set_rgblight_layer_color(lock_bg_segments[i], lockled_positions[i], MNM_LOCKLED_LENGTH, lock_bg_color);
    }

    // Set on state colors for each lock LED position
    rgblight_segment_t* lock_on_segments[] = {
        light_layer_lockled_0,
        light_layer_lockled_1
    };
    for (uint8_t i = 0; i < 2; i++) {
        HSV lock_on_color = mnm_color_pick_dim_color(mnm_via_get_config(i, ON_COLOR));
        set_rgblight_layer_color(lock_on_segments[i], lockled_positions[i], MNM_LOCKLED_LENGTH, lock_on_color);
    }

    // Refresh RGB layer definitions
    rgblight_layers = mnm_rgblight_layers;

    // Initialize all layers to off state
    for (uint8_t i = 0; i < 9; i++) {
        rgblight_set_layer_state(i, false);
    }
}
