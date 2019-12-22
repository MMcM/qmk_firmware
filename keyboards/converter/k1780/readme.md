# K1780

A converter for a Hi-Tek keyboard evidently numbered 1780.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: K1780, Teensy 2.0  

Make example for this keyboard (after setting up your build environment):

    make converter/k1780:default

# Protocol

The keyboard has a 4P4C modular (telephone) connector.

The board requires 12V DC (which it immediately regulates down to 5V).

Communication is serial at around 600 baud.

There are no up transitions and shifts (CTRL and SHIFT) are sent as a prefix byte when changing.

| RJ11   | Signal |
|--------|--------|
| Black  | RXD    |
| Red    | TXD    |
| Green  | GND    |
| Yellow | 12V    |
