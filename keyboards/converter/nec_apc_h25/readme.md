# NEC APC-H25

A converter for the NEC APC-H25 keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: NEC APC-H25, Teensy

Make example for this keyboard (after setting up your build environment):

    make converter/nec_apc_h25:default

The keyboard does not send up transitions.
The mapping of shifts is handled specially and so not very flexible.

## Hardware

The schematic and general description of the protocol can be found in the [System Reference Guide](http://bitsavers.org/pdf/nec/APC/819-000100-1003_APC_System_Reference_Guide_Apr83.pdf).

The keyboard connects to the PC with an AMP 24-pin Centronix-style connector.
Inside the keyboard this connects to a 26-pin header, labeled `CN1` in the schematic.

| CN1 | Signal | AMP | MCU |
|-----|--------|-----|-----|
|  3  | SD1    |  2  | B0  |
|  4  | SD2    | 14  | B1  |
|  5  | SD3    |  3  | B2  |
|  6  | SD4    | 15  | B3  |
|  7  | SD5    |  4  | B4  |
|  8  | SD6    | 16  | B5  |
|  9  | SD7    |  5  | B6  |
| 10  | SD8    | 17  | B7  |
| 12  | DSTB   | 18  | D0  |
| 14  | PBSTB  | 19  | D2  |
| 16  | SWSTB  | 20  | D1  |
| 19  | DBG    | 10  | D3  |
| 20  | OP1    |     |     |
| 21  | OP2    | 11  |     |
| 22  | OP3    |     |     |
