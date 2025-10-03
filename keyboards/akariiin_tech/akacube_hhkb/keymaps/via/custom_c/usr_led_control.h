// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "usr_config.h"
#include "usr_via_config.h"

#ifndef USR_LED_KEEPTIME
#    define USR_LED_KEEPTIME 1000
#endif
#ifndef USR_LOCKLED_1
#    define USR_LOCKLED_1 1
#endif
#ifndef USR_LOCKLED_2
#    define USR_LOCKLED_2 2
#endif
#ifndef USR_LOCKLED_3
#    define USR_LOCKLED_3 4
#endif

void usr_lock_indicator_update(led_t led_state);
void usr_lock_indicator_timer(void);
void usr_layer_indicator_update(layer_state_t state);
void usr_layer_indicator_timer(void);
void usr_refresh_lockled(void);
void usr_refresh_layerled(void);
bool usr_lockled_timer_active(void);
bool usr_layerled_timer_active(void);
