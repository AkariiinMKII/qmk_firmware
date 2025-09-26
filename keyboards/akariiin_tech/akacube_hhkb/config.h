// Copyright 2024 AkariiinMKII (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* EEPROM settings */
#define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 4
#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 16

/* User datablock for VIA custom settings */
#define EECONFIG_USER_DATA_SIZE 8

/* Wear leveling settings */
#define WEAR_LEVELING_LOGICAL_SIZE 1024
#define WEAR_LEVELING_BACKING_SIZE 4096
