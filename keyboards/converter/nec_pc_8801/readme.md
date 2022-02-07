# NEC PC-8801

A converter for the earlier NEC PC-8801 models before it switched to mini-DIN-5.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: 8801mkIISR, Teensy  

Make example for this keyboard (after setting up your build environment):

    make converter/nec_pc_8801:default

The keyboard's only active component is a 74159 demux. Input pins load the row selector and output pins give the state of columns in that row.

On the original 8801, a 2x8 header, CN1, connects to a cable ending in a DIN-14.
(This is a somewhat unusual connector, also found in the Atari floppy drive. Looking at the recepticle with the notch at the top, clockwise from top-right is 10, 8, 6, 4, 2, 1, 3, 5, 7, 9, 11, then inside again, 12, 14, 13. Such a PCB connector with three rows of pins has 7, 3, 1, 2, 6; 5, 13, 12, 4; 11, 9, 14, 8, 10.)

On the mkII, a 1x14 connects to a DIN-13, with the ground connection on the connector's shell.

The numbering is everywhere the same.

| Pin | Color        | DIN-14 | DIN-13 | AVR |
|-----|--------------|--------|--------|-----|
|   1 | yellow       |      1 |      1 | PB0 |
|   2 | green        |      2 |      2 | PB1 |
|   3 | orange       |      3 |      3 | PB2 |
|   4 | blue         |      4 |      4 | PB3 |
|   5 | red          |      5 |      5 | PB4 |
|   6 | violet       |      6 |      6 | PB5 |
|   7 | brown        |      7 |      7 | PB6 |
|   8 | gray         |      8 |      8 | PB7 |
|   9 | black        |      9 |      9 | PD0 |
|  10 | white        |     10 |     10 | PD1 |
|  11 | red+black    |     11 |     11 | PD2 |
|  12 | brown+black  |     12 |     12 | PD3 |
|  13 | orange+black |     13 |     13 | VCC |
|  14 | yellow+black |     14 |  shell | GND |
