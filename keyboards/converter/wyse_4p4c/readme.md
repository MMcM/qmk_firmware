# Wyse 4P4C

A converter for the Wyse keyboards using a 4P4C connector.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: WY60 ASCII, WY85, PCE / US; Teensy 2.0, Teensy 3.2

Make example for this keyboard (after setting up your build environment):

    make converter/wyse_4p4c:wy85

## Hardware

The connector is a 4P4C RJ modular jack. This wiring is the same as for Soarer's WYSEverter.

| Pin | Color  | Signal | AVR |
|-----|--------|--------|-----|
|   1 | Black  | Data   | D1  |
|   2 | Red    | Vcc    | +5V |
|   3 | Green  | Clock  | D0  |
|   4 | Yellow | Ground | GND |

## Firmware Variants

All of these use the first hardware UART serial port.

* `teensy_20` for ATMega32U4.

* `teensy_32` for Teensy 3.2.

## Layout Variants

* `wy60` for WY60

* `wy85` for WY85

* `pce` for PCE

The layout must match the keyboard; there is no real commonality in key numbering.
