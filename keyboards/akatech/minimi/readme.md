# MiniMi

![MiniMi](https://imgur.com/a70gAfw.jpg)
*40% keyboard in quark-like layout*

## Info

* Keyboard Maintainer: [AkariiinMKII](https://github.com/AkariiinMKII)
* Hardware Supported: MiniMi
* Hardware Availability: https://github.com/AkariiinMKII/MiniMi

Make example for this keyboard (after setting up your build environment):

    make akatech/minimi:default

Flashing example for this keyboard:

    make akatech/minimi:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the ESC key or BOOTMAGIC button on the back of PCB and plug in the keyboard (NOTE: this will clear EEPROM that cause your custom settings to be lost)

* **Physical reset button**: Press the RESET button on the back of the PCB twice

* **Hold combo keys**: Hold down two SHIFT keys then press R key for 5 seconds
