// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usr_rgb_layers.h"
#include "usr_config.h"

// RGB Layer Definitions
// Black background layer (overrides default animations)
static const rgblight_segment_t PROGMEM usr_layer_bg[] = 
    RGBLIGHT_LAYER_SEGMENTS({0, USR_LED_COUNT, HSV_BLACK});

// Lock indicators (2 LEDs each): num(0-1), caps(2-3), scroll(4-5)
static const rgblight_segment_t PROGMEM usr_layer_num[] = 
    RGBLIGHT_LAYER_SEGMENTS({0, 2, USR_COLOR_NUM});
static const rgblight_segment_t PROGMEM usr_layer_caps[] = 
    RGBLIGHT_LAYER_SEGMENTS({2, 2, USR_COLOR_CAPS});
static const rgblight_segment_t PROGMEM usr_layer_scroll[] = 
    RGBLIGHT_LAYER_SEGMENTS({4, 2, USR_COLOR_SCROLL});

// Layer indicators (2 LEDs each, same position 6-7)
static const rgblight_segment_t PROGMEM usr_layer_1[] = 
    RGBLIGHT_LAYER_SEGMENTS({6, 2, USR_COLOR_LAYER1});
static const rgblight_segment_t PROGMEM usr_layer_2[] = 
    RGBLIGHT_LAYER_SEGMENTS({6, 2, USR_COLOR_LAYER2});
static const rgblight_segment_t PROGMEM usr_layer_3[] = 
    RGBLIGHT_LAYER_SEGMENTS({6, 2, USR_COLOR_LAYER3});
static const rgblight_segment_t PROGMEM usr_layer_4[] = 
    RGBLIGHT_LAYER_SEGMENTS({6, 2, USR_COLOR_LAYER4});

// Layer mapping array
const rgblight_segment_t* const PROGMEM usr_rgblight_layers[] = RGBLIGHT_LAYERS_LIST(
    usr_layer_bg,
    usr_layer_num,
    usr_layer_caps,
    usr_layer_scroll,
    usr_layer_1,
    usr_layer_2,
    usr_layer_3,
    usr_layer_4
);

void usr_rgb_layers_init(void) {
    rgblight_layers = usr_rgblight_layers;
    rgblight_set_layer_state(USR_LAYER_BG, false);  // Start with background off
}
