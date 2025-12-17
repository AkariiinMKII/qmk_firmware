# Copyright 2025 AkariiinL (@AkariiinMKII)
# SPDX-License-Identifier: GPL-2.0-or-later

# VIA user space build configuration
# This file defines the build settings and source files for the
# VIA keymap user space modules.

# ------------------ Feature Enables ------------------
VIA_ENABLE = yes             # VIA keymap configuration support
MOUSEKEY_ENABLE = yes        # Mouse key support
OS_DETECTION_ENABLE = yes    # Operating system detection support

# ------------------ Drivers ------------------
WEAR_LEVELING_DRIVER = embedded_flash  # Use embedded flash for wear leveling

# ------------------ User Space Source Files ------------------
SRC += mnm_custom/mnm_combo.c           # Combo key sequences
SRC += mnm_custom/mnm_env_patch.c       # Environment initialization fix
SRC += mnm_custom/mnm_layer_indicator.c # Layer indicator system library
SRC += mnm_custom/mnm_led_blink.c       # LED blink effects
SRC += mnm_custom/mnm_led_control.c     # LED control coordination
SRC += mnm_custom/mnm_lock_indicator.c  # Lock indicator system library
SRC += mnm_custom/mnm_rgb_colors.c      # RGB color definitions
SRC += mnm_custom/mnm_rgblight_layers.c # RGB light layer management
SRC += mnm_custom/mnm_via_config.c      # VIA configuration system
