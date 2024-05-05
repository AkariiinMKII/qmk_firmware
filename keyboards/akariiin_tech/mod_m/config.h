// Copyright 2024 AkariiinMKII (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* define if matrix has ghost */
#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Use ESC for Bootmagic feature */
#define BOOTMAGIC_ROW 0
#define BOOTMAGIC_COLUMN 2

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
