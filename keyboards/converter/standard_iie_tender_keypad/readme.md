# Standard IIe Tender Keypad

A converter for the Track House standard IIe tender keypad.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: KPD-010, Teensy LC

Make example for this keyboard (after setting up your build environment):

    make converter/standard_iie_tender_keypad:default

## Hardware

A DB-25 connector is wired to a PCB with a 26-pin header and a matrix of switches.

| DB | AMP | LC | MCU |
|----|-----|----|-----|
|  1 |  20 |  0 | B16 |
|  2 |  16 |    |     |
|  3 |   5 |  1 | B17 |
|  4 |   4 |  2 | D0  |
|  5 |  11 |  3 | A1  |
|  6 |  22 |    |     |
|  7 |   7 |  4 | A2  |
|  8 |  20 |    |     |
|  9 |  18 |    |     |
| 10 |  19 |    |     |
| 11 |  15 |    |     |
| 12 |   6 |    |     |
| 13 |   1 |  5 | D7  |
| 14 |   2 |  6 | D4  |
| 15 |   3 |  7 | D2  |
| 16 |     |    |     |
| 17 |     |    |     |
| 18 |   8 |    |     |
| 19 |   9 |    |     |
| 20 |     |    |     |
| 21 |  16 |  8 |  D3 |
| 22 |  17 |  9 |  C3 |
| 23 |  10 | 10 |  C4 |
| 24 |  21 | 11 |  C6 |
| 25 |  14 | 12 |  C7 |
