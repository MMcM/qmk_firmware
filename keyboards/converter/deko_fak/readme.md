# Deko Fast Action Keyboard

A converter for the Pinnacle Deko Fast Action Keyboard, a video editing keyboard with _lots_ of vintage Cherry blacks.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: Deko FAK, Teensy  

Make example for this keyboard (after setting up your build environment):

    make converter/deko_fak:default

## Hardware

The tested hardware connection is Clock (pin 1) to XCK (D5) and Data (pin 2) to RXD (D2), in order to use the UART in synchronous mode to decode. Other arrangements, compatible with Soarer's or TMK PS2, should also work.

## Features

The keyboard has 162 keys.

The LEDs in the 40 half-height keys, along with the 3 ordinary modifier LEDs, implement an LED matrix, with two levels, representing solid and blinking.

The 20x2 VFD interfaces through a virtual serial port and should be compatible with many serial LCD controlling programs.
