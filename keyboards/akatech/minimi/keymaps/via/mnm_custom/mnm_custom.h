// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "via.h"
#include "mnm_config.h"

// mnm_via_config.c
enum mnm_config_rows {
    LOCK_LED_0 = 0,
    LOCK_LED_1 = 1,
    LAYER_LED = 2
};

enum mnm_config_cols {
    BITMASK = 0,
    OFF_COLOR = 1,
    ON_COLOR = 2,
    L3_COLOR = 1
};

enum mnm_config_flags {
    OVERRIDE_LAYERLED = 0,
    AUTO_DISABLE = 1,
    AUTO_SWAP = 2
};

void mnm_via_init_config(void);
void mnm_via_save_config(void);
uint8_t mnm_via_get_config(uint8_t row, uint8_t col);
uint8_t mnm_via_get_led_timeout(void);
bool mnm_via_get_flag(uint8_t flag_index);
bool mnm_via_lock_system_enabled(void);
void via_custom_value_command_kb(uint8_t *data, uint8_t length);

// mnm_rgblight_layers.c
#ifndef MNM_COLOR_LAYERLED_MO1
#    define MNM_COLOR_LAYERLED_MO1    HSV_BLUE_DIM
#endif
#ifndef MNM_COLOR_LAYERLED_MO2
#    define MNM_COLOR_LAYERLED_MO2    HSV_BLUE_DIM
#endif
#ifndef MNM_COLOR_LAYERLED_MO3
#    define MNM_COLOR_LAYERLED_MO3    HSV_BLUE_DIM
#endif
#ifndef MNM_COLOR_LOCKLED_BG
#    define MNM_COLOR_LOCKLED_BG      HSV_RED_DIM
#endif
#ifndef MNM_COLOR_LOCKLED_0
#    define MNM_COLOR_LOCKLED_0       HSV_GREEN_DIM
#endif
#ifndef MNM_COLOR_LOCKLED_1
#    define MNM_COLOR_LOCKLED_1       HSV_GREEN_DIM
#endif
#ifndef MNM_COLOR_BLINK
#    define MNM_COLOR_BLINK           HSV_RED_DIM
#endif
#ifndef MNM_LAYERLED_POSITIONS
#    define MNM_LAYERLED_POSITIONS {0, 1}
#endif
#ifndef MNM_LAYERLED_LENGTH
#    define MNM_LAYERLED_LENGTH 1
#endif
#if MNM_LAYERLED_LENGTH < 1
#    undef MNM_LAYERLED_LENGTH
#    define MNM_LAYERLED_LENGTH 1
#endif
#ifndef MNM_LOCKLED_POSITIONS
#    define MNM_LOCKLED_POSITIONS {0, 1}
#endif
#ifndef MNM_LOCKLED_LENGTH
#    define MNM_LOCKLED_LENGTH 1
#endif
#if MNM_LOCKLED_LENGTH < 1
#    undef MNM_LOCKLED_LENGTH
#    define MNM_LOCKLED_LENGTH 1
#endif
#if MNM_LOCKLED_0 > 0
#    define MNM_COLOR_LOCKLED_BG0 MNM_COLOR_LOCKLED_BG
#else
#    define MNM_COLOR_LOCKLED_BG0 HSV_BLACK
#endif
#if MNM_LOCKLED_1 > 0
#    define MNM_COLOR_LOCKLED_BG1 MNM_COLOR_LOCKLED_BG
#else
#    define MNM_COLOR_LOCKLED_BG1 HSV_BLACK
#endif

void mnm_rgblight_layers_init(void);

// mnm_layer_indicator.c
void mnm_layer_indicator_show(layer_state_t state);
void mnm_layer_indicator_hide(void);

// mnm_lock_indicator.c
void mnm_lock_indicator_show(uint8_t lock_state);
void mnm_lock_indicator_hide(void);

// mnm_led_blink.c
#ifndef MNM_BLINK_TIME_ON
#    define MNM_BLINK_TIME_ON 200
#endif
#ifndef MNM_BLINK_TIME_IDLE
#    define MNM_BLINK_TIME_IDLE 200
#endif

void mnm_led_blink_show(void);
void mnm_led_blink_hide(void);
void mnm_led_blink_timer(void);
bool mnm_led_blink_timer_active(void);

// mnm_combo.c
#ifndef MNM_COMBO_MOD1
#    define MNM_COMBO_MOD1 KC_LSFT
#endif
#ifndef MNM_COMBO_MOD2
#    define MNM_COMBO_MOD2 KC_RSFT
#endif
bool mnm_combo_check(uint16_t keycode, bool pressed);
void mnm_combo_handler(void);
bool mnm_combo_any_active(void);

// mnm_led_control.c
#ifndef MNM_LED_KEEPTIME
#    define MNM_LED_KEEPTIME 1500
#endif
#ifndef MNM_LOCKLED_0
#    define MNM_LOCKLED_0 1
#endif
#ifndef MNM_LOCKLED_1
#    define MNM_LOCKLED_1 2
#endif
#ifndef MNM_LOCKLED_2
#    define MNM_LOCKLED_2 4
#endif

void mnm_led_lock_indicator_update(led_t led_state);
void mnm_led_lock_indicator_timer(void);
void mnm_led_layer_indicator_update(layer_state_t state);
void mnm_led_layer_indicator_timer(void);
void mnm_led_refresh_lockled(void);
void mnm_led_refresh_layerled(void);
void mnm_led_init_lockled(void);
void mnm_led_init_layerled(void);
bool mnm_led_lockled_timer_active(void);
bool mnm_led_layerled_timer_active(void);

// mnm_rgb_colors.c
HSV mnm_color_pick_dim_color(uint8_t color_index);

// mnm_env_patch.c
void mnm_env_init_layer_state(void);
void mnm_env_setup_swap_ag(os_variant_t host_os);
