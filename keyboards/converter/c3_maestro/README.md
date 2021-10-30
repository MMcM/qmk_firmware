# C3 Maestro

A converter for the Ericsson C3 Maestro keyboard.

Keyboard Maintainer: [RaouldDuke-Esq](https://github.com/RaouldDuke-Esq)  
Hardware Supported: C3 Maestro, Teensy 3.2  

Make example for this keyboard (after setting up your build environment):

    make converter/c3_maestro:default

## Protocol

The keyboard protocol is TTL serial with negative polarity (idle low).

## Connections

The keyboard's cable had a DE9 connector.

| DE9   | Color | Signal               | AVR |
|-------|-------|----------------------|-----|
|   1   | red   |  +5VDC               | Vin |
|   2   | white |  Data                | RX1 |
|   4   | green |  Ground              | GND |
|   6   | bare  |  PE                  |     |
