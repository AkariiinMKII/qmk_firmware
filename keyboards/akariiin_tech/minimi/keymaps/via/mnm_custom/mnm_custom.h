// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "via.h"
#include "akc_config.h"

// akc_via_config.c
enum akc_config_rows {
    LOCK_LED_0 = 0,
    LOCK_LED_1 = 1,
    LOCK_LED_2 = 2,
    LAYER_LED = 3
};

enum akc_config_cols {
    BITMASK = 0,
    OFF_COLOR = 1,
    ON_COLOR = 2
};

enum akc_config_flags {
    OVERRIDE_LAYERLED = 0,
    AUTO_DISABLE = 1,
    AUTO_SWAP = 2
};

void akc_via_init_config(void);
void akc_via_save_config(void);
uint8_t akc_via_get_config(uint8_t row, uint8_t col);
uint8_t akc_via_get_led_timeout(void);
bool akc_via_get_flag(uint8_t flag_index);
bool akc_via_lock_system_enabled(void);
void via_custom_value_command_kb(uint8_t *data, uint8_t length);

// akc_rgblight_layers.c
#ifndef AKC_COLOR_LAYERLED_BG
#    define AKC_COLOR_LAYERLED_BG     HSV_RED_DIM
#endif
#ifndef AKC_COLOR_LAYERLED_MO0
#    define AKC_COLOR_LAYERLED_MO0    HSV_BLUE_DIM
#endif
#ifndef AKC_COLOR_LAYERLED_MO1
#    define AKC_COLOR_LAYERLED_MO1    HSV_BLUE_DIM
#endif
#ifndef AKC_COLOR_LAYERLED_MO2
#    define AKC_COLOR_LAYERLED_MO2    HSV_BLUE_DIM
#endif
#ifndef AKC_COLOR_LAYERLED_MO3
#    define AKC_COLOR_LAYERLED_MO3    HSV_BLUE_DIM
#endif
#ifndef AKC_COLOR_LOCKLED_BG
#    define AKC_COLOR_LOCKLED_BG      HSV_RED_DIM
#endif
#ifndef AKC_COLOR_LOCKLED_0
#    define AKC_COLOR_LOCKLED_0       HSV_GREEN_DIM
#endif
#ifndef AKC_COLOR_LOCKLED_1
#    define AKC_COLOR_LOCKLED_1       HSV_GREEN_DIM
#endif
#ifndef AKC_COLOR_LOCKLED_2
#    define AKC_COLOR_LOCKLED_2       HSV_GREEN_DIM
#endif
#ifndef AKC_COLOR_BLINK
#    define AKC_COLOR_BLINK           HSV_RED_DIM
#endif
#ifndef AKC_LAYERLED_POSITIONS
#    define AKC_LAYERLED_POSITIONS {0, 1, 2, 3}
#endif
#ifndef AKC_LAYERLED_LENGTH
#    define AKC_LAYERLED_LENGTH 1
#endif
#if AKC_LAYERLED_LENGTH < 1
#    undef AKC_LAYERLED_LENGTH
#    define AKC_LAYERLED_LENGTH 1
#endif
#ifndef AKC_LOCKLED_POSITIONS
#    define AKC_LOCKLED_POSITIONS {0, 1, 2}
#endif
#ifndef AKC_LOCKLED_LENGTH
#    define AKC_LOCKLED_LENGTH 1
#endif
#if AKC_LOCKLED_LENGTH < 1
#    undef AKC_LOCKLED_LENGTH
#    define AKC_LOCKLED_LENGTH 1
#endif
#if AKC_LOCKLED_0 > 0
#    define AKC_COLOR_LOCKLED_BG0 AKC_COLOR_LOCKLED_BG
#else
#    define AKC_COLOR_LOCKLED_BG0 HSV_BLACK
#endif
#if AKC_LOCKLED_1 > 0
#    define AKC_COLOR_LOCKLED_BG1 AKC_COLOR_LOCKLED_BG
#else
#    define AKC_COLOR_LOCKLED_BG1 HSV_BLACK
#endif
#if AKC_LOCKLED_2 > 0
#    define AKC_COLOR_LOCKLED_BG2 AKC_COLOR_LOCKLED_BG
#else
#    define AKC_COLOR_LOCKLED_BG2 HSV_BLACK
#endif

void akc_rgblight_layers_init(void);

// akc_layer_indicator.c
void akc_layer_indicator_show(layer_state_t state);
void akc_layer_indicator_hide(void);

// akc_lock_indicator.c
void akc_lock_indicator_show(uint8_t lock_state);
void akc_lock_indicator_hide(void);

// akc_led_blink.c
#ifndef AKC_BLINK_TIME_ON
#    define AKC_BLINK_TIME_ON 200
#endif
#ifndef AKC_BLINK_TIME_IDLE
#    define AKC_BLINK_TIME_IDLE 200
#endif

void akc_led_blink_show(void);
void akc_led_blink_hide(void);
void akc_led_blink_timer(void);
bool akc_led_blink_timer_active(void);

// akc_combo.c
#ifndef AKC_COMBO_MOD1
#    define AKC_COMBO_MOD1 KC_LSFT
#endif
#ifndef AKC_COMBO_MOD2
#    define AKC_COMBO_MOD2 KC_RSFT
#endif
bool akc_combo_check(uint16_t keycode, bool pressed);
void akc_combo_handler(void);
bool akc_combo_any_active(void);

// akc_led_control.c
#ifndef AKC_LED_KEEPTIME
#    define AKC_LED_KEEPTIME 1500
#endif
#ifndef AKC_LOCKLED_0
#    define AKC_LOCKLED_0 1
#endif
#ifndef AKC_LOCKLED_1
#    define AKC_LOCKLED_1 2
#endif
#ifndef AKC_LOCKLED_2
#    define AKC_LOCKLED_2 4
#endif

void akc_led_lock_indicator_update(led_t led_state);
void akc_led_lock_indicator_timer(void);
void akc_led_layer_indicator_update(layer_state_t state);
void akc_led_layer_indicator_timer(void);
void akc_led_refresh_lockled(void);
void akc_led_refresh_layerled(void);
void akc_led_init_lockled(void);
void akc_led_init_layerled(void);
bool akc_led_lockled_timer_active(void);
bool akc_led_layerled_timer_active(void);

// akc_rgb_colors.c
HSV akc_color_pick_dim_color(uint8_t color_index);

// akc_env_patch.c
void akc_env_init_layer_state(void);
void akc_env_setup_swap_ag(os_variant_t host_os);
