# QVT-101+

A converter for the Qume QVT-101+ terminal keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: QVT-101+, Teensy 2.0  

Make example for this keyboard (after setting up your build environment):

    make converter/qume/qvt_101_plus:default

The keyboard uses a 4P4C RJ connector. The cable is crossover, so pins are reversed on the converter side.

| Kbd | Color  | Signal | Cvt | Color  | AVR |
|-----|--------|--------|-----|--------|-----|
| 1   | Black  | GND    | 4   | Yellow | GND |
| 2   | Red    | +5V    | 3   | Green  | VCC |
| 3   | Green  | STROBE | 2   | Red    | PD1 |
| 4   | Yellow | SIGNAL | 1   | Black  | PD0 |
