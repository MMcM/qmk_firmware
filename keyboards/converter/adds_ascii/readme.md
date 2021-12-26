# ADDS ASCII

ADDS ASCII keyboard in ADDS Mode.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: ADDS ASCII, Teensy  

Make example for this keyboard (after setting up your build environment):

    make converter/adds_ascii:default

## Protocol

The PCB has a series of jumpers to select between PC/AT mode and ADDS mode.

When ADDS mode is selected, the AT DATA line is always pulled low and the RESET line is not connected. Only the AT CLOCK line does anything.

The protocol requires the terminal to strobe the signal line periodically and the keyboard then sends 8 bits of scan code, MSB-first, with a long pulse for 1 and a short pulse for 0. The scan codes are based on ASCII characters, but unchanged by shift state. Only a few keys send separate up transition codes.

## Connections

The keyboard cable goes from J1 on the PCB to a 6P6C RJ plug.

Connections for PC/AT mode (for instance, using Soarer's) are also shown here, although the additional lines do not need to be connected for this converter to work.

| J1 | Color  | RJ | PC/AT | ADDS   | AVR |
|----|--------|----|-------|--------|-----|
|  1 | White  |  5 | Vcc   | Vcc    | +5V |
|  2 | Black  |  4 | Gnd   | Gnd    | GND |
|  3 | Yellow |  1 | Clock | Signal | PD1 |
|  4 | Black  |  6 | PE    | Gnd    | GND |
|  5 | Green  |  2 | Data  | Low    | PD0 |
|  6 | Red    |  3 | Reset | N/C    | PB7 |
