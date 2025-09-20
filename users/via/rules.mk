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
SRC += usr_rgb_layers.c      # RGB layer management
SRC += usr_led_control.c     # Lock/Layer LED control
SRC += usr_combo.c           # Combo key sequences
