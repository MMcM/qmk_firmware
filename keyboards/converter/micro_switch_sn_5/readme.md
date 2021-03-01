# Micro Switch SN-series 5-key keypad

A subassembly for some kind of control equipment. Part number appears to be C59731095-001.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: A59731097-B, DFRobot Beetle  
Hardware Availability: surplue from eBay

Make example for this keyboard (after setting up your build environment):

    make converter/micro_switch_sn_5:default

## Connections

There is an 8-pin header with one pin missing.

| J1 | Color  | Signal | MCU | Beetle | 
|----|--------|--------|-----|--------|
| 1  | Brown  | A/C    | B0  | D10    |
| 2  | Red    | PB UP  | B1  | D9     |
| 3  | Orange | +5V    | VCC | +      |
| 4  | Yellow | GND    | GND | -      |
| 5  | Green  | S/F    | B2  | A0     |
| 6  | Blue   |        |     |        |
| 7  | Violet | PB DWN | B3  | A1     |
| 8  | Gray   | B/D    | B4  | A2     |
