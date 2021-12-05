# SGI IRIS4D

A converter for the Silicon Graphics Professional Iris / IRIS4D keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: IRIS4D, Teensy  

Make example for this keyboard (after setting up your build environment):

    make converter/sgi:default

The protocol is described on the [keyboard (7)](https://nixdoc.net/man-pages/IRIX/man7/keyboard.7.html) man page.

## Hardware

The keyboard connects with a DA-15 cable. It needs both +12V and -12V power.

| D15 | J1 | Signal |
|-----|----|--------|
|   1 |  1 | GND    |
|   2 | 11 | GND    |
|   3 | 12 | GND    |
|   4 |  4 | KTDX   |
|   5 |  5 | KRCD   |
|   7 |  9 | +12V   |
|   8 | 10 | +12V   |
|   9 | 14 | +12V   |
|  10 |  6 | MTXD   |
|  11 |  7 |        |
|  12 |  8 |        |
|  15 | 13 | -12V   |

The keyboard protocol is 600 baud RS-423, so a level shifter is needed. It also uses 8 bits with odd parity.

## Firmware Variants

* `teensy_20` for ATMega32U4.
* `teensy_32` for Teensy 3.2.
* `teensy_lc` for Teensy LC.

The 32-bit MCUs use `UART2` (`RX3` / `TX3`) for the keyboard.
(At one time they used the default UART for serial mouse. This support is currently broken.)
If you would rather use `UART0` (`RX1` / `TX1`), create a configuration that defines `SD_KEYBOARD` to `SD1`
and change `KINETIS_SERIAL_USE_UART0` to `TRUE` (and `2` to `FALSE`) in `mcuconf.h`.
