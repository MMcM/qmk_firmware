# Ampex 219

A converter for the Ampex 219 terminal keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: Ampex 219, Teensy

Make example for this keyboard (after setting up your build environment):

    make converter/ampex_219:default

The keyboard does not send up transitions.
The mapping of shifts is handled specially and so not very flexible.

## Hardware

The keyboard requires 8-16VDC (nominal 12V) power for the 5V regulator.

The connector is a 4P4C RJ modular jack.

| Pin | Color  | Signal         | AVR |
|-----|--------|----------------|-----|
|   1 | Black  | Chassis ground | GND |
|   2 | Red    | Vin            |     |
|   3 | Green  | Data           | D0  |
|   4 | Yellow | Signal ground  | GND |
