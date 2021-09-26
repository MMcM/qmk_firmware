# QVT-101

A converter for the Qume QVT-101 and QVT-102 terminal keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: QVT-101, Teensy 2.0  

Make example for this keyboard (after setting up your build environment):

    make converter/qume/qvt_101:default

The keyboard uses a 4P4C RJ connector. The cable is crossover, so pins are reversed on the converter side.

The (single) data line is pulled up to 12V, so some kind of level shifter is needed to bring it back down. Copying the circuit in the terminal iself from the [Maintenance Manual]() works. That circuit also allows for bidirectional data, in which case PD2/RX1 should be input from the keyboard and PD3/TX1 output to the keyboard.

| Kbd | Color  | Signal | Cvt | Color  |
|-----|--------|--------|-----|--------|
| 1   | Black  | GND    | 4   | Yellow |
| 2   | Red    | +12V   | 3   | Green  |
| 3   | Green  | PE     | 2   | Red    |
| 4   | Yellow | DATA   | 1   | Black  |

**NB**: The QVT-101+ does not have a compatible pinout. It is a 5V device.
