# Teleray 20HE

A converter for the Research Inc. Teleray 20HE terminal keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: KBD 20HE, Teensy 3.2  

Make example for this keyboard (after setting up your build environment):

    make converter/teleray_20he:default

## Protocol

The keyboard protocol is 4800 baud at TTL levels with inverted polarity. The keyboard is powered with +12V.

| RJ | Color  | Signal        |
|----|--------|---------------|
| 1  | Black  | RX (from kbd) |
| 2  | Red    | +12V          |
| 3  | Green  | Ground        |
| 4  | Yellow | TX (to kbd)   |
