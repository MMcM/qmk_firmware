# Sperry-Univac UTS

Low Profile Expanded Typewriter keyboard for UTS-10, -20, -30, and -40 systems.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: Low Profile, Adafruit Itsy-bitsy 5V  

Make example for this keyboard (after setting up your build environment):

    make converter/uts:default

## Protocol

The keyboard protocol is 9600 baud TTL serial.

Each report consists of two bytes, the first of which has the high bit set and the second of which has it clear.
In general, the first byte indicates shift state, and the second byte is the scan code.
The to-keyboard direction must have sent data (any data) recently in order for the keyboard to report.

## Connections

The keyboard cable terminates in a 9-pin d-sub (DE-9).

| PCB | Color  | DE9 | Signal        |
|-----|--------|-----|---------------|
|  2  | Orange |  1  | GND           |
|  3  | Brown  |  8  | TX (to kbd)   |
|  4  | Pink   |  6  | -RX           |
|  5  | Yellow |  7  | RX (from kbd) |
|  8  | Red    |  2  | +5V           |
