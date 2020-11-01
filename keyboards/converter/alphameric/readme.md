# Alphameric Type 140

A converter for a Alphameric Type 140 4170 keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: Alphameric, Teensy 2.0

Make example for this keyboard (after setting up your build environment):

    make converter/alphameric:default

The connector is a DIN-5, with signals the same as a IBM PC/XT or AT/PS2, with a RESET line.

The converter assumes the same connections as Soarer's Controller [xt_usb](../xt_usb).

| DIN | AVR | Signal    |
|-----|-----|-----------|
| 1   | PD1 | CLOCK     | 
| 2   | PD0 | DATA      | 
| 3   | PB7 | -RESET    | 
| 4   | GND | GROUND    |
| 5   | VCC | +5 VDC    |
