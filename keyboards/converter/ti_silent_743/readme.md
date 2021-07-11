# TI Silent 700 Model 743/745

A converter for the TI Silent 600 Model 743/745, with the APL option, using Micro Switch board 63SD17-3 with PCB SD-16329.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: 63SD17-3, Teensy 2.0

Make example for this keyboard (after setting up your build environment):

    make converter/ti_silent_743:default

The schematic for the keyboard interface can be found in the [Maintenance Manual](https://archive.org/details/bitsavers_titerminalrC743KSR745PortableMaintenanceManualJul7_10425391/page/n136/mode/1up).

The PCB has a 25-pin FFC connector, with pins numbered 1-12 and 13-24, skipping the middle hole.

### Connections ###

| PCB | Signal              | AVR |
|-----|---------------------|-----|
| 1   | CDET-               | PC7 |
| 2   | ONLINE-             | PF5 |
| 3   | FLDPLX-             | PF6 |
| 4   | +5V                 | +5V |
| 5   | GND                 | GND |
| 6   | 30CPS-              | PF7 |
| 7   | R6-                 | PD7 |
| 8   | C5-                 | PB5 |
| 9   | C0-                 | PB0 |
| 10  | C1-                 | PB1 |
| 11  | C2-                 | PB2 |
| 12  | R0-                 | PD0 |
|     |                     |     |
| 13  | C3-                 | PB3 |
| 14  | R2-                 | PD2 |
| 15  | R4-                 | PD4 |
| 16  | R3-                 | PD3 |
| 17  | C7-                 | PB7 |
| 18  | R1-                 | PD1 |
| 19  | C6-                 | PB6 |
| 20  | R5-                 | PD5 |
| 21  | C4-                 | PB4 |
| 22  | CTRL-               | PF0 |
| 23  | SHIFT-              | PF1 |
| 24  | NUM-                | PF4 |
