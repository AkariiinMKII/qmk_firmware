// Copyright 2025 AkariiinL(@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// --- LED layout (0-7) ---:
// LED 0-1 : CapsLock indicator (red)
// LED 2-3 : Layer indicator
// LED 4-7 : decorative RGB animations

// Define half brightness HSV colors
#define HSV_RED_HALF 0, 255, 128
#define HSV_CYAN_HALF 128, 255, 128
#define HSV_GREEN_HALF 85, 255, 128
#define HSV_PURPLE_HALF 170, 255, 128
#define HSV_MAGENTA_HALF 191, 255, 128

// CapsLock -> LED 0-1
const rgblight_segment_t PROGMEM user_layer_caps[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_RED_HALF}
);

// Layer -> LED 2-3
const rgblight_segment_t PROGMEM user_layer_1[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 2, HSV_CYAN_HALF}
);

const rgblight_segment_t PROGMEM user_layer_2[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 2, HSV_GREEN_HALF}
);

const rgblight_segment_t PROGMEM user_layer_3[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 2, HSV_PURPLE_HALF}
);

const rgblight_segment_t PROGMEM user_layer_4[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 2, HSV_MAGENTA_HALF}
);

// Register layers.
// Index 0 = user_layer_caps, 1 = user_layer_1, 2 = user_layer_2, etc.
const rgblight_segment_t* const PROGMEM user_rgblight_layers[] = RGBLIGHT_LAYERS_LIST(
    user_layer_caps,
    user_layer_1,
    user_layer_2,
    user_layer_3,
    user_layer_4
);

void keyboard_post_init_user(void) {
    // enable layer system
    rgblight_layers = user_rgblight_layers;
}

// CapsLock change -> control layer index 0
bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

// Layer changes -> control layer indices 1 and 2
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, 1)); // MO(1)
    rgblight_set_layer_state(2, layer_state_cmp(state, 2)); // MO(2)
    rgblight_set_layer_state(3, layer_state_cmp(state, 3)); // MO(3)
    rgblight_set_layer_state(4, layer_state_cmp(state, 4)); // MO(4)
    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ \ │ ` │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ Bspc│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │ Ctrl │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift│MO1│
     * └─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┘
     *       │Alt│ GUI │                           │ GUI │Alt│
     *       └───┴─────┴───────────────────────────┴─────┴───┘
     */
    [0] = LAYOUT_hhkb(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(1),
                          KC_LALT, KC_LGUI, KC_NO,            KC_SPC,  KC_NO,                    KC_RGUI, KC_RALT
    ),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│Ins│Del│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
     * │Caps │Prv│Ply│Nxt│VlU│ T │ Y │ U │PSc│Scr│Pse│ ↑ │ ] │ Bspc│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │ Ctrl │VAL│SAT│HUE│Mut│ G │ * │ / │Hom│PgU│ ← │ → │  Enter │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
     * │ Shift  │RGB│NXT│SPD│VlD│ B │ + │ - │End│PgD│ ↓ │ Shift│MO1│
     * └─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┘
     *       │Alt│ GUI │                           │ GUI │Alt│
     *       └───┴─────┴───────────────────────────┴─────┴───┘
     */
    [1] = LAYOUT_hhkb(
        _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
        KC_CAPS, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, KC_UP,   _______, _______,
        _______, UG_VALU, UG_SATU, UG_HUEU, KC_MUTE, _______, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT,          KC_PENT,
        _______,          UG_TOGG, UG_NEXT, UG_SPDU, KC_VOLD, _______, KC_PPLS, KC_PMNS, KC_END,  KC_PGDN, KC_DOWN, _______, _______,
                          _______, _______, _______,          _______, _______,                   _______, _______
    )
};
