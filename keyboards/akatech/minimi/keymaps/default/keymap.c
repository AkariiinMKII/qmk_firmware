// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

// VIA keymap for AkaCube HHKB keyboard
// Features: RGB indicators for locks/layers, combo keys, VIA support

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Layer 0: Base Alpha layout
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ESC│ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │BKS│
     * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤
     * │TAB │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ENT  │
     * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬────┤
     * │ SFT  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │SFT │
     * └┬───┬─┴─┬─┴──┬┴──┬┴───┴───┴──┬┴──┬┴───┼───┼───┬┘
     *  │CTL│GUI│ALT │MO1│  SPACE    │MO2│ALT │GUI│CTL│
     *  └───┴───┴────┴───┴───────────┴───┴────┴───┴───┘
     */
    [0] = LAYOUT_quark(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, MO(1),            KC_SPC,           MO(2),   KC_RALT, KC_RGUI, KC_RCTL
    ),

    // Layer 1: Numeric and Symbols
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │DEL│
     * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤
     * │TAB │   │   │   │   │ - │ = │ [ │ ] │ \ │ ENT  │
     * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬────┤
     * │ SFT  │   │   │   │   │   │ ; │ ' │ / │ ↑ │SFT │
     * └┬───┬─┴─┬─┴──┬┴──┬┴───┴───┴──┬┴──┬┴───┼───┼───┬┘
     *  │CTL│GUI│ALT │MO1│  SPACE    │MO2│  ← │ ↓ │ → │
     *  └───┴───┴────┴───┴───────────┴───┴────┴───┴───┘
     */
     [1] = LAYOUT_quark(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
        KC_TAB,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, KC_ENT,
        KC_LSFT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_SCLN, KC_QUOT, KC_SLSH, KC_UP,   KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, MO(1),            KC_SPC,           MO(2),   KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // Layer 1: Shifted Numeric and Symbols
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ ~ │ ! │ @ │ # │ $ │ % │ ^ │ & │ * │ ( │ ) │DEL│
     * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤
     * │CAPS│   │   │   │   │ _ │ + │ { │ } │ | │ ENT  │
     * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬────┤
     * │ SFT  │   │   │   │   │   │ : │ " │ ? │ ↑ │SFT │
     * └┬───┬─┴─┬─┴──┬┴──┬┴───┴───┴──┬┴──┬┴───┼───┼───┬┘
     *  │CTL│GUI│ALT │MO1│  SPACE    │MO2│  ← │ ↓ │ → │
     *  └───┴───┴────┴───┴───────────┴───┴────┴───┴───┘
     */
    [2] = LAYOUT_quark(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
        KC_CAPS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_ENT,
        KC_LSFT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_COLN, KC_DQUO, KC_QUES, KC_UP,   KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, MO(3),            KC_SPC,           MO(2),   KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // Layer 3: Function Keys
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ESC│F1 │F2 │F3 │F4 │   │   │PRT│SCR│PUS│   │   │
     * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤
     * │    │F5 │F6 │F7 │F8 │   │   │INS│HOM│PGU│ ENT  │
     * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬────┤
     * │ SFT  │F9 │F10│F11│F12│   │   │DEL│END│PGD│SFT │
     * └┬───┬─┴─┬─┴──┬┴──┬┴───┴───┴──┬┴──┬┴───┼───┼───┬┘
     *  │CTL│GUI│ALT │MO1│  SPACE    │MO2│ALT │GUI│CTL│
     *  └───┴───┴────┴───┴───────────┴───┴────┴───┴───┘
     */
    [3] = LAYOUT_quark(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_NO,   KC_NO,   KC_PSCR, KC_SCRL, KC_PAUS, KC_NO,   KC_NO,
        KC_NO,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_NO,   KC_NO,   KC_INS,  KC_HOME, KC_PGUP, KC_ENT,
        KC_LSFT, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO,   KC_NO,   KC_DEL,  KC_END,  KC_PGDN, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, MO(3),            KC_SPC,           MO(2),   KC_RALT, KC_RGUI, KC_RCTL
    ),
};
