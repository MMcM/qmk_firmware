# Apollo

A converter for the Apollo Domain keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: 007121, Teensy 2.0  

Make example for this keyboard (after setting up your build environment):

    make converter/apollo:default

## Protocol

The keyboard protocol is 1200 baud TTL serial with even parity.
It is documented in the [Technical Reference](https://archive.org/details/bitsavers_apollo008704000TechnicalReferenceAug87_8288958/page/n141/mode/2up).

## Connections

The keyboard has a 5V regulators, so power around 8-12V is needed.

The cable from the keyboard has a DE-9 M connector (the right-hand one; the left-hand F connector is for a mouse).

| DE-9 | Signal       | AVR |
|------|--------------|-----|
| 2    | +12VDC       |     |
| 3    | RESET*       | D1  |
| 4    | TXD (to CPU) | D2  |
| 5    | RXD (to kbd) | D3  |
| 6    | GND          | GND |
| 7    | GND          | GND |
