// Copyright 2025 AkariiinL (@AkariiinMKII)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "akc_custom.h"

// Ensure default layer state is valid
static bool is_valid_default_layer(uint32_t mask) {
    return (mask == 1 || mask == 2 || mask == 4 || mask == 8);
}

void akc_env_init_layer_state(void) {
    if (!is_valid_default_layer(default_layer_state)) {
        default_layer_set(1);  // Reset to layer 0 if invalid
    }

    layer_state |= default_layer_state;
}

#ifdef AKC_AUTO_SWAP_AG
#include "eeconfig.h"

// OS-based Alt/GUI swap configuration
void akc_env_setup_swap_ag(os_variant_t host_os) {
    bool should_swap = host_os == OS_MACOS || host_os == OS_IOS;
    eeconfig_read_keymap(&keymap_config);
    if (keymap_config.swap_lalt_lgui == should_swap &&
        keymap_config.swap_ralt_rgui == should_swap) {
        return;
    }
    keymap_config.swap_lalt_lgui = should_swap;
    keymap_config.swap_ralt_rgui = should_swap;
    eeconfig_update_keymap(&keymap_config);
    clear_keyboard();
}
#endif
