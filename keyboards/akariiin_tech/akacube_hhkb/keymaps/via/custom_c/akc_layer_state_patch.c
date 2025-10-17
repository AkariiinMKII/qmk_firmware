// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "akc_custom.h"

static bool is_valid_default_layer(uint32_t mask) {
    return (mask == 1 || mask == 2 || mask == 4 || mask == 8);
}

void akc_layer_init_layer_state(void) {
    if (!is_valid_default_layer(default_layer_state)) {
        default_layer_set(1);  // Reset to layer 0 if invalid
    }

    layer_state |= default_layer_state;
}
