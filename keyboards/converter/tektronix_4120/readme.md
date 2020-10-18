# Tektronix 4120

A converter for the Tektronix 4120 series keyboard.

The keyboard has thirteen LEDs, of which nine are underneath keys.
There are two thumbwheels.
The keyboard can also apparently interface to a serial mouse and a joystick.

This is a Keytronic foam and foil keyboard with part number 119-1836-00.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: Tek 4120, Teensy 2.0  

Make example for this keyboard (after setting up your build environment):

    make converter/tektronix_4120:default

## Protocol

The keyboard protocol is 1200 baud TTL serial.

## Connections

The keyboard has two 5V regulators, so power around 8-12V is needed.

The cable from the keyboard has a DIN-5 connector.

| DIN | J1 | color  | Signal        |
|-----|----|--------|---------------|
| 1   | 1  | red    | TD (to kbd)   |
| 2   | 2  | green  | RX (from kbd) |
| 3   | 4  | black  | /RESET        |
| 4   | 5  | white  | GND           |
| 5   | 6  | orange | +12VDC        |
