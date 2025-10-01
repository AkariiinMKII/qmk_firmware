// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "custom_c/usr_config.h"
#include "custom_c/usr_rgblight_layers.h"
#include "custom_c/usr_led_control.h"
#include "custom_c/usr_led_blink.h"
#include "custom_c/usr_combo.h"
#include "custom_c/usr_via_config.h"

// Initialize RGB layers and VIA configuration on startup
void keyboard_post_init_user(void) {
    usr_rgblight_layers_init();     // Initialize RGB layers first with default colors
    usr_via_config_init();          // Then load VIA config and update colors
}

// Update RGB indicators when lock states change
bool led_update_user(led_t led_state) {
    lock_indicator_update(led_state);
    return true;
}

// Update RGB indicators when layers change
layer_state_t layer_state_set_user(layer_state_t state) {
    layer_indicator_update(state);
    return state;
}

// Process key presses for combo detection
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return usr_combo_check(keycode, record->event.pressed);
}

// Handle LED timeouts and combo updates
void matrix_scan_user(void) {
    if (usr_lockled_timer_active()) { lock_indicator_timer(); }
    if (usr_layerled_timer_active()) { layer_indicator_timer(); }
    usr_combo_handler();
    led_blink_timer();
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Layer 0: Base QWERTY layout
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

    // Layer 1: Function keys and media controls
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│Ins│Del│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
     * │Caps │Prv│Ply│Nxt│VlU│ T │ Y │Num│PSc│Scr│Pse│ ↑ │ ] │ Bspc│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │ Ctrl │HUE│SAT│VAL│Mut│ G │ * │ / │Hom│PgU│ ← │ → │  Enter │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
     * │ Shift  │RGB│NXT│SPD│VlD│ B │ + │ - │End│PgD│ ↓ │ Shift│MO1│
     * └─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┘
     *       │Alt│ GUI │                           │ GUI │Alt│
     *       └───┴─────┴───────────────────────────┴─────┴───┘
     */
    [1] = LAYOUT_hhkb(
        _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
        KC_CAPS, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU, _______, _______, KC_NUM,  KC_PSCR, KC_SCRL, KC_PAUS, KC_UP,   _______, _______,
        _______, UG_HUEU, UG_SATU, UG_VALU, KC_MUTE, _______, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT,          KC_PENT,
        _______,          UG_TOGG, UG_NEXT, UG_SPDU, KC_VOLD, _______, KC_PPLS, KC_PMNS, KC_END,  KC_PGDN, KC_DOWN, _______, _______,
                          _______, _______, _______,          _______, _______,                   _______, _______
    )
};
