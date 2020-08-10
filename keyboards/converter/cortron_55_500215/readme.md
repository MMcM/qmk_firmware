# Cortron 55-500215

A converter for the Cortron 55-500215 and 55-500582 keyboard.
These keyboards were part of the CPT 8000 series standalone word processor.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: Cortron 55-500215, 55-500582, Teensy  

Make example for this keyboard (after setting up your build environment):

    make converter/cortron_55_500215:default

## Hardware

The keyboard has ITW magnetic valve switches and uses a custom MOS chip from ITW/Cortron that requires -12V. A boost converter from 5V works.
A successful one had a part number `DD1718PA` on [AliExpress](https://www.aliexpress.com/wholesale?SearchText=DD1718PA).
It does not need a whole lot of current and powering off the same USB port seems to work.

The 80-551646 PCB has a keyed 26-pin IDC socketed connector and a ribbon cable.
The 55-500215 has an IDC connector at the both ends while the 55-500582 has a DB-25 with the pins properly numbered.

| Pin    | Signal   | MCU |
|--------|----------|-----|
| 1,14,  | Ground   | GND | 
| 8,9,10 |          |     |
| 2,15   | +5V      | VCC |
| 3,16   | -12V     |     |
| 4      | B1       | B0  |
| 17     | B2       | B1  |
| 5      | B3       | B2  |
| 18     | B4       | B3  |
| 6      | B5       | B4  |
| 19     | B6       | B5  |
| 7      | B7       | B6  |
| 20     | Key down | D0  |
| 21     | ? output | D1  |
| 22     | ? input  | D2  |
| 23     | ? input  | D3  |
| 11,12, | N/C      |     |
|24,25,26|          |     |
| 13     | no pin   |     |
