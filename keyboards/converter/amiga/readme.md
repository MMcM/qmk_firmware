# Amiga

A converter for a Commodore Amiga keyboards.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: A1000, Teensy 2.0

Information about the protocol can be found in the [Hardware Reference Manual](https://archive.org/details/amiga-hardware-reference-manual-3rd-edition/page/357/mode/2up).

Make example for this keyboard (after setting up your build environment):

    make converter/amiga:default

The Amiga 1000 has a 4P4C connector. Note that the cable that comes with the keyboard is crossover.

The Amiga 2000 has a 5-pin DIN connector.

| PCB | Color | RJ | Color  | DIN | Signal | AVR |
|-----|-------|----|--------|-----|--------|-----|
| 1   | Black | 4  | Yellow | 4   | Ground | GND |
| 2   | Red   | 1  | Black  | 5   | +5V    | VCC |
| 3   | White | 3  | Green  | 2   | Data   | PD0 |
| 4   | Green | 2  | Red    | 1   | Clock  | PD1 |
