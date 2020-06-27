# Pericom 2506

A converter for the Pericom graphics terminal keyboard

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: Pericom 2506, Teensy 3.2  

Make example for this keyboard (after setting up your build environment):

    make converter/pericom:default

## Hardware

The protocol is 1200 baud TTL-level serial, but with idle low.

The cable from the keyboard has a 5-pin DIN 41525 connector.

| DIN | Signal |
|-----|--------|
| 1   | +5V    |
| 3   | RXD    |
| 4   | TXD    |
| 5   | GND    |
