// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "mnm_custom/mnm_custom.h"

// Initialize VIA configuration on startup
void keyboard_post_init_user(void) {
    mnm_env_init_layer_state();  // Workaround for layer_state initialization issue
    mnm_via_init_config();  // Load VIA configurations
    mnm_led_init_lockled();  // Initialize RGB light layers
}

// OS-based configurations on host OS detection event
bool process_detected_host_os_user(os_variant_t host_os) {
    if (host_os == OS_UNSURE) return true;
    if (mnm_via_get_flag(AUTO_SWAP)) { mnm_env_setup_swap_ag(host_os); }
    if (mnm_via_get_flag(AUTO_DISABLE)) { mnm_led_init_lockled(); }
    return true;
}

// Update RGB indicators when lock states change
bool led_update_user(led_t led_state) {
    mnm_led_lock_indicator_update(led_state);
    return true;
}

// Update RGB indicators when layers change
layer_state_t layer_state_set_user(layer_state_t state) {
    mnm_led_layer_indicator_update(state);
    return state;
}

// Process combo detection for key events
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return mnm_combo_check(keycode, record->event.pressed);
}

// Process LED timeouts and combo updates
void matrix_scan_user(void) {
    if (mnm_led_lockled_timer_active()) { mnm_led_lock_indicator_timer(); }
    if (mnm_led_layerled_timer_active()) { mnm_led_layer_indicator_timer(); }
    if (mnm_combo_any_active()) { mnm_combo_handler(); }
    if (mnm_led_blink_timer_active()) { mnm_led_blink_timer(); }
}

// Keymap definitions
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
     *  │CTL│GUI│ALT │TG3│  SPACE    │MO2│  ← │ ↓ │ → │
     *  └───┴───┴────┴───┴───────────┴───┴────┴───┴───┘
     */
    [2] = LAYOUT_quark(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
        KC_CAPS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_ENT,
        KC_LSFT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_COLN, KC_DQUO, KC_QUES, KC_UP,   KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, TG(3),            KC_SPC,           MO(2),   KC_LEFT, KC_DOWN, KC_RGHT
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
     *  │CTL│GUI│ALT │TG3│  SPACE    │TG3│ALT │GUI│CTL│
     *  └───┴───┴────┴───┴───────────┴───┴────┴───┴───┘
     */
    [3] = LAYOUT_quark(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_NO,   KC_NO,   KC_PSCR, KC_SCRL, KC_PAUS, KC_NO,   KC_NO,
        KC_NO,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_NO,   KC_NO,   KC_INS,  KC_HOME, KC_PGUP, KC_ENT,
        KC_LSFT, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO,   KC_NO,   KC_DEL,  KC_END,  KC_PGDN, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, TG(3),            KC_SPC,           TG(3),   KC_RALT, KC_RGUI, KC_RCTL
    ),
};
