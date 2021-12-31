# Xerox 820-II Low Profile Keyboard

The G25 Low Profile keyboard for the Xerox 820-II made by Cortron.

Note that the 820 also supported an ASCII keyboard made by Maxi-Switch. That keyboard only sent ASCII codes, not scan codes, and so is not really suitable as a modern USB keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: G25, Teensy  

Make example for this keyboard (after setting up your build environment):

    make converter/xerox_820_lpk:default

## Protocol

The hardware protocol is strobed parallel, as is common for ASCII keyboards, as the same computer supported both.

The keyboard reports are usually two bytes, updating the status of an individual key. The Technical Reference refers to this as position-encoded, as the scan codes more or less correspond to the physical position of the keys. The details of these bytes, which can also encode optical mouse movements, are given in comments in the [code](https://archive.org/details/bitsavers_xerox820IIicalReference1984_15030341/page/n293/mode/2up) there.

## Connections

The keyboard has a DB-25 connector.

| J2  | Signal  | AVR |
|-----|---------|-----|
|  1  | DB0     | B0  |
|  2  | DB1     | B1  |
|  3  | DB2     | B2  |
|  4  | DB3     | B3  |
|  5  | DB4     | B4  |
|  6  | DB5     | B5  |
|  7  | DB6     | B6  |
|  8  | DB7     | B7  |
|  9  | /STROBE | D0  |
|10-12| N/C     |     |
| 13  | +5V     | +5V |
|14-24| N/C     |     |
| 25  | GND     | GND |
