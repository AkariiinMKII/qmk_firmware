# Copyright 2025 AkariiinL (@AkariiinMKII)
# SPDX-License-Identifier: GPL-2.0-or-later

# VIA user space build configuration
# This file defines the build settings and source files for the
# VIA keymap user space modules.

# ------------------ Feature Enables ------------------
MOUSEKEY_ENABLE = yes        # Mouse key support
LTO_ENABLE = yes             # Link Time Optimization for smaller firmware
RGBLIGHT_ENABLE = yes        # RGB lighting support
VIA_ENABLE = yes             # VIA keymap configuration support

# ------------------ Drivers ------------------
WEAR_LEVELING_DRIVER = embedded_flash  # Use embedded flash for wear leveling

# ------------------ User Space Source Files ------------------
SRC += custom_c/usr_rgblight_layers.c # RGB light layer management
SRC += custom_c/usr_led_control.c     # LED control coordination
SRC += custom_c/usr_layer_indicator.c # Layer indicator system library
SRC += custom_c/usr_lock_indicator.c  # Lock indicator system library
SRC += custom_c/usr_led_blink.c       # LED blink effects
SRC += custom_c/usr_combo.c           # Combo key sequences
SRC += custom_c/usr_via_config.c       # VIA configuration system
