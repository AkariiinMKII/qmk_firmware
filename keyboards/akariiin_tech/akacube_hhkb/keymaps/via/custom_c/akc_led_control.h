// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "akc_config.h"
#include "akc_via_config.h"

#ifndef AKC_LED_KEEPTIME
#    define AKC_LED_KEEPTIME 1500
#endif
#ifndef AKC_LOCKLED_1
#    define AKC_LOCKLED_1 1
#endif
#ifndef AKC_LOCKLED_2
#    define AKC_LOCKLED_2 2
#endif
#ifndef AKC_LOCKLED_3
#    define AKC_LOCKLED_3 4
#endif

void akc_lock_indicator_update(led_t led_state);
void akc_lock_indicator_timer(void);
void akc_layer_indicator_update(layer_state_t state);
void akc_layer_indicator_timer(void);
void akc_refresh_lockled(void);
void akc_refresh_layerled(void);
bool akc_lockled_timer_active(void);
bool akc_layerled_timer_active(void);
