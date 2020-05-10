# Tandy 1000

A converter for a Tandy 1000 keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: Tandy 1000, Teensy 2.0

Make example for this keyboard (after setting up your build environment):

    make converter/tandy_1000:default

The protocol and keycodes are described in the [Tandy 1000 Technical Reference Manual](ftp://ftp.oldskool.org/pub/tvdog/tandy1000/documents/1ktech.zip).

The Tandy 1000 keyboard has a DIN 8 connector (see J5 - Keyboard Interface on page 7).

Other similar keyboards seem to have the same protocol, but a different connector, such as the Tandy 2000, which has a DIN 5.

There is a 6-pin header on the PCB, to which the protocol description refers.

| DIN | PCB | AVR | Signal    |
|-----|-----|-----|-----------|
| 1   | 1   | D1  | KBDDATA   | 
| 2   | 4   | D2  | KBDBUSY*  | 
| 3   | 6   | GND | Ground    | 
| 4   | 3   | D0  | KBDCLOCK  |
| 5   | 5   | VCC | +5 VDC    |
| 6   | 2   | D3  | KBDRST    |
| 7   | N/C | N/C | MULTIDATA |
| 8   | N/C | N/C | MULTICLK  |
