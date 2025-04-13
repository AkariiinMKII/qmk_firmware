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
SRC += akc_custom/akc_rgb_colors.c      # RGB color definitions
SRC += akc_custom/akc_rgblight_layers.c # RGB light layer management
SRC += akc_custom/akc_led_control.c     # LED control coordination
SRC += akc_custom/akc_layer_indicator.c # Layer indicator system library
SRC += akc_custom/akc_lock_indicator.c  # Lock indicator system library
SRC += akc_custom/akc_led_blink.c       # LED blink effects
SRC += akc_custom/akc_combo.c           # Combo key sequences
SRC += akc_custom/akc_via_config.c       # VIA configuration system
SRC += akc_custom/akc_layer_state_patch.c # Layer state initialization fix
