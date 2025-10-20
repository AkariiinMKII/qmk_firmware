// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "akc_custom/akc_custom.h"

// Initialize VIA configuration on startup
void keyboard_post_init_user(void) {
    akc_env_init_layer_state();  // Workaround for layer_state initialization issue
    akc_via_init_config();  // Load VIA configuration
    akc_led_init_lockled();  // Initialize RGB layers with VIA colors
}

// OS-based configuration on host OS detection event
bool process_detected_host_os_user(os_variant_t host_os) {
    if (host_os == OS_UNSURE) return true;
#ifdef AKC_AUTO_SWAP_AG
    akc_env_setup_swap_ag(host_os);
#endif
    akc_led_init_lockled();
    return true;
}

// Update RGB indicators when lock states change
bool led_update_user(led_t led_state) {
    akc_led_lock_indicator_update(led_state);
    return true;
}

// Update RGB indicators when layers change
layer_state_t layer_state_set_user(layer_state_t state) {
    akc_led_layer_indicator_update(state);
    return state;
}

// Process key presses for combo detection
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return akc_combo_check(keycode, record->event.pressed);
}

// Handle LED timeouts and combo updates
void matrix_scan_user(void) {
    if (akc_led_lockled_timer_active()) { akc_led_lock_indicator_timer(); }
    if (akc_led_layerled_timer_active()) { akc_led_layer_indicator_timer(); }
    if (akc_combo_any_active()) { akc_combo_handler(); }
    if (akc_led_blink_timer_active()) { akc_led_blink_timer(); }
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
     *       │GUI│ Alt │                           │ Alt │GUI│
     *       └───┴─────┴───────────────────────────┴─────┴───┘
     */
    [0] = LAYOUT_hhkb(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(1),
                          KC_LGUI, KC_LALT, KC_NO,            KC_SPC,  KC_NO,                    KC_RALT, KC_RGUI
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
     *       │GUI│ Alt │                           │ Alt │GUI│
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
