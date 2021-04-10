# Micro Switch SD-16604

A converter for a Honeywell BKBD keyboard assembly 108SD30-4.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: SD-16604, Teensy 2.0

Make example for this keyboard (after setting up your build environment):

    make converter/micro_switch_sd_16604:default

Connection to the keyboard is through a DB-25.

### Connections ###

| IDC | Signal              | AVR |
|-----|---------------------|-----|
|6,7,8|
|9    | GND                 | GND |
|10,11|
|12,13| +5V                 | +5V |
|     |                     |     |
|  4  | STROBE              | PD0 |
| 19  | CHAR BIT 1          | PB0 |
| 20  | CHAR BIT 2          | PB1 |
| 18  | CHAR BIT 3          | PB2 |
| 17  | CHAR BIT 4          | PB3 |
| 16  | CHAR BIT 5          | PB4 |
| 15  | CHAR BIT 6          | PB5 |
| 14  | CHAR BIT 7          | PB6 |
| 23  | /BREAK              | PB7 |
|  2  | SPEAKER             | PC6*|
| 21  | /DATA SET READY     | PC7 |
| 25  | /SHIFT              | PD1 |
| 24  | /CAPS LOCK          | PD2 |
|  1  | /CTRL               | PD3 |
|  5  | /AUTO LF            | PD4 |
| 22  | /LOCAL              | PD5 |
