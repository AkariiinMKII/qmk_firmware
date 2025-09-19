// Copyright 2025 AkariiinL(@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// ------------------ Reset Combo Configuration ------------------
#ifndef RESET_COMBO_KEY
#    define RESET_COMBO_KEY KC_R           // Default third key for reset combo
#endif
#ifndef RESET_COMBO_HOLD_TIME
#    define RESET_COMBO_HOLD_TIME 3000     // Milliseconds to hold combo for reset
#endif

// ------------------ Easter Egg Configuration ------------------
#ifndef EASTER_EGG_KEY
#    define EASTER_EGG_KEY KC_C            // Easter egg trigger key
#endif
#ifndef EASTER_EGG_HOLD_TIME
#    define EASTER_EGG_HOLD_TIME 3000      // Milliseconds to hold for easter egg
#endif

// --- LED Layout & Behavior (0-7) ---:
// LED 0-1 : NumLock indicator (blue dim) - Animated on state change
// LED 2-3 : CapsLock indicator (red dim) - Direct on/off
// LED 4-5 : ScrollLock indicator (green dim) - Animated on state change
// LED 6-7 : Layer indicators (cyan/yellow/purple/magenta) - Layer dependent
//
// Animation Types:
// - NumLock/ScrollLock ON: 3 quick flashes (300ms on, 200ms off)
// - NumLock/ScrollLock OFF: Long pulse (800ms + 200ms wait + 100ms)
//
// Reset Combo (configurable):
// - Default: Left Shift + Right Shift + R held for 3 seconds
// - Customize: Override RESET_COMBO_KEY and/or RESET_COMBO_HOLD_TIME
//
// Easter Egg (configurable):
// - Default: Left Shift + Right Shift + C held for 3 seconds types "ciallo"
// - Customize: Override EASTER_EGG_KEY and/or EASTER_EGG_HOLD_TIME

// Define half brightness HSV colors
// #define HSV_RED_HALF 0, 255, 128
// #define HSV_ORANGE_HALF 21, 255, 128
// #define HSV_YELLOW_HALF 43, 255, 128
// #define HSV_CHARTREUSE_HALF 64, 255, 128
// #define HSV_GREEN_HALF 85, 255, 128
// #define HSV_SPRINGGREEN_HALF 106, 255, 128
// #define HSV_CYAN_HALF 128, 255, 128
// #define HSV_AZURE_HALF 148, 255, 128
// #define HSV_BLUE_HALF 170, 255, 128
// #define HSV_PURPLE_HALF 191, 255, 128
// #define HSV_MAGENTA_HALF 213, 255, 128
// #define HSV_PINK_HALF 234, 255, 128
// #define HSV_WHITE_HALF 0, 0, 128

// Define dimmer brightness HSV colors (val = 96)
#define HSV_RED_DIM 0, 255, 96
#define HSV_YELLOW_DIM 43, 255, 96
#define HSV_GREEN_DIM 85, 255, 96
#define HSV_CYAN_DIM 128, 255, 96
#define HSV_BLUE_DIM 170, 255, 96
#define HSV_PURPLE_DIM 191, 255, 96
#define HSV_MAGENTA_DIM 213, 255, 96

// ------------------ Layer LED Mapping ------------------
// NumLock -> LED 0-1
const rgblight_segment_t PROGMEM user_layer_num[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_BLUE_DIM}
);

// CapsLock -> LED 2-3
const rgblight_segment_t PROGMEM user_layer_caps[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 2, HSV_RED_DIM}
);

// ScrollLock -> LED 4-5
const rgblight_segment_t PROGMEM user_layer_scroll[] = RGBLIGHT_LAYER_SEGMENTS(
    {4, 2, HSV_GREEN_DIM}
);

// Layer -> LED 6-7
const rgblight_segment_t PROGMEM user_layer_1[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 2, HSV_MAGENTA_DIM}
);

const rgblight_segment_t PROGMEM user_layer_2[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 2, HSV_PURPLE_DIM}
);

const rgblight_segment_t PROGMEM user_layer_3[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 2, HSV_YELLOW_DIM}
);

const rgblight_segment_t PROGMEM user_layer_4[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 2, HSV_CYAN_DIM}
);

// ------------------ RGB Layer Mapping ------------------
const rgblight_segment_t* const PROGMEM user_rgblight_layers[] = RGBLIGHT_LAYERS_LIST(
    user_layer_num,
    user_layer_caps,
    user_layer_scroll,
    user_layer_1,
    user_layer_2,
    user_layer_3,
    user_layer_4
);

void keyboard_post_init_user(void) {
    rgblight_layers = user_rgblight_layers;
}

// ------------------ LED Animation Struct ------------------
// Animation behavior:
// - Key ON:  3 quick flashes (300ms on, 200ms off)
// - Key OFF: Long pulse (800ms on, 200ms wait, 100ms on)
typedef struct {
    bool last_state;     // Previous key state to detect changes
    enum { LED_IDLE, LED_FLASH_ON, LED_FLASH_OFF, LED_LONG_ON1, LED_LONG_WAIT, LED_LONG_ON2 } state;
    uint16_t timer;      // Timer for animation timing
    uint8_t flash_count; // Counter for flash animation
    uint8_t layer_index; // RGB layer index for this animation
} led_anim_t;

static led_anim_t numlock_anim   = {false, LED_IDLE, 0, 0, 0}; // NumLock -> layer 0
static led_anim_t scrolllock_anim = {false, LED_IDLE, 0, 0, 2}; // ScrollLock -> layer 2

// ------------------ Reusable Combo System ------------------
// Generic combo structure for reusable combo handling
typedef struct {
    uint16_t key;           // Third key for the combo
    uint16_t hold_time;     // Time to hold combo (ms)
    bool key_held;          // State of the third key
    uint16_t timer;         // Timer for combo timing
    void (*action)(void);   // Function to execute when combo triggers
} combo_t;

// Combo actions
static void reset_action(void) {
    reset_keyboard();
}

static void easter_egg_action(void) {
    send_string("ciallo");
}

// Define combos using the generic structure
static combo_t combos[] = {
    {RESET_COMBO_KEY, RESET_COMBO_HOLD_TIME, false, 0, reset_action},
    {EASTER_EGG_KEY, EASTER_EGG_HOLD_TIME, false, 0, easter_egg_action},
};

#define NUM_COMBOS (sizeof(combos) / sizeof(combos[0]))

// Shared state for shift keys
static bool lshift_held = false;
static bool rshift_held = false;

// Check if a key is part of any combo
static bool is_combo_key(uint16_t keycode) {
    if (keycode == KC_LSFT || keycode == KC_RSFT) return true;
    
    for (uint8_t i = 0; i < NUM_COMBOS; i++) {
        if (keycode == combos[i].key) {
            return true;
        }
    }
    return false;
}

// Check if any combo is currently fully active (all keys pressed)
static bool is_combo_fully_active(void) {
    if (!lshift_held || !rshift_held) return false;
    
    for (uint8_t i = 0; i < NUM_COMBOS; i++) {
        if (combos[i].key_held) {
            return true;  // At least one combo is fully pressed
        }
    }
    return false;
}

// ------------------ Helper Functions ------------------

// Generic combo handler function
// Handles Left Shift + Right Shift + configurable key combos
static void handle_combo(combo_t *combo) {
    if (lshift_held && rshift_held && combo->key_held) {
        if (combo->timer == 0) {
            combo->timer = timer_read();  // Start timing
        } else if (timer_elapsed(combo->timer) >= combo->hold_time) {
            combo->action();  // Execute combo action
            combo->timer = 0; // Prevent multiple triggers
        }
    } else {
        combo->timer = 0;  // Any key released, abort combo
    }
}

// Process all combos
static void handle_all_combos(void) {
    for (uint8_t i = 0; i < NUM_COMBOS; i++) {
        handle_combo(&combos[i]);
    }
}

// Generic LED animation update function
// Handles state transitions when lock keys are pressed/released

static void update_led_anim(led_anim_t *anim, bool current_state) {
    if (current_state != anim->last_state) {
        anim->last_state = current_state;
        if (current_state) {
            anim->state = LED_FLASH_ON;
            anim->flash_count = 0;
            anim->timer = timer_read();
            rgblight_set_layer_state(anim->layer_index, true);
        } else {
            anim->state = LED_LONG_ON1;
            anim->timer = timer_read();
            rgblight_set_layer_state(anim->layer_index, true);
        }
    }
}

// ------------------ Key Processing ------------------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Update key states first
    switch (keycode) {
        case KC_LSFT: lshift_held = record->event.pressed; break;
        case KC_RSFT: rshift_held = record->event.pressed; break;
        default:
            // Check all combos for matching keys
            for (uint8_t i = 0; i < NUM_COMBOS; i++) {
                if (keycode == combos[i].key) {
                    combos[i].key_held = record->event.pressed;
                    break;
                }
            }
            break;
    }
    
    // Suppress key events when combo is fully active
    if (is_combo_key(keycode) && is_combo_fully_active()) {
        return false;  // Don't process this key event further
    }
    
    return true;  // Process key normally
}

// ------------------ LED Update ------------------
bool led_update_user(led_t led_state) {
    // CapsLock: Direct layer control (immediate on/off)
    rgblight_set_layer_state(1, led_state.caps_lock);

    // NumLock and ScrollLock: Animated indicators
    update_led_anim(&numlock_anim, led_state.num_lock);
    update_led_anim(&scrolllock_anim, led_state.scroll_lock);

    return true;
}

// LED animation state machine function
// Processes LED animation timing and state transitions
static void scan_led_anim(led_anim_t *anim) {
    uint16_t elapsed = timer_elapsed(anim->timer);
    switch (anim->state) {
        case LED_FLASH_ON:     // Flash animation: LED on phase (300ms)
            if (elapsed >= 300) {
                rgblight_set_layer_state(anim->layer_index, false);
                anim->state = LED_FLASH_OFF;
                anim->timer = timer_read();
            }
            break;
        case LED_FLASH_OFF:    // Flash animation: LED off phase (200ms)
            if (elapsed >= 200) {
                anim->flash_count++;
                if (anim->flash_count >= 3) {  // After 3 flashes, go idle
                    rgblight_set_layer_state(anim->layer_index, false);
                    anim->state = LED_IDLE;
                } else {                        // Continue flashing
                    rgblight_set_layer_state(anim->layer_index, true);
                    anim->state = LED_FLASH_ON;
                }
                anim->timer = timer_read();
            }
            break;
        case LED_LONG_ON1:     // Long pulse: First long on phase (800ms)
            if (elapsed >= 800) {
                rgblight_set_layer_state(anim->layer_index, false);
                anim->state = LED_LONG_WAIT;
                anim->timer = timer_read();
            }
            break;
        case LED_LONG_WAIT:    // Long pulse: Wait phase (200ms)
            if (elapsed >= 200) {
                rgblight_set_layer_state(anim->layer_index, true);
                anim->state = LED_LONG_ON2;
                anim->timer = timer_read();
            }
            break;
        case LED_LONG_ON2:     // Long pulse: Final short on phase (100ms)
            if (elapsed >= 100) {
                rgblight_set_layer_state(anim->layer_index, false);
                anim->state = LED_IDLE;
            }
            break;
        default: break;
    }
}

// ------------------ Matrix Scan (LED Animations + Combos) ------------------
void matrix_scan_user(void) {
    // Process LED animations for NumLock and ScrollLock
    scan_led_anim(&numlock_anim);
    scan_led_anim(&scrolllock_anim);

    // Handle all combos
    handle_all_combos();
}

// ------------------ Layer RGB Control ------------------
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(3, layer_state_cmp(state, 1));
    rgblight_set_layer_state(4, layer_state_cmp(state, 2));
    rgblight_set_layer_state(5, layer_state_cmp(state, 3));
    rgblight_set_layer_state(6, layer_state_cmp(state, 4));
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
