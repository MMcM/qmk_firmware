# Sperry-Univac UDS-2000

A converter for the keypunch-like keyboard used with the Sperry-Univac UDS-2000 system
as part of the Type 3039 (UDES Master) and 3546 (UDES Workstation) cabinets.
Part number 2821175.
This keyboard has Cortron PCB 55-500252.

There are three keyboard styles: typewriter, adding machine (0 at bottom), and keypunch (0 at top).

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: Cortron 55-500252, Adafruit Itsy-bitsy 5V  

Make example for this keyboard (after setting up your build environment):

    make converter/sperry_univac_uds_2000:default

## Hardware

The keyboard has ITW magnetic valve switches and uses a custom MOS chip from ITW/Cortron that requires -12V. A boost converter from 5V works.
A successful one had a part number `DD1718PA` on [AliExpress](https://www.aliexpress.com/wholesale?SearchText=DD1718PA).
It does not need a whole lot of current and powering off the same USB port seems to work.

The cable has a keyed 26-pin IDC socketed connector. The connections are not straight through however.
Using the pin numbers of the PCB, the IDC connector is as follows.

|    |    |    |    |    |    |    |    |    |    |    |    |    |
|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
|  1 |  7 |  5 |  3 | 17 | 15 | 13 | 11 |  9 | 19 | 21 | 23 | 25 |
|  2 |  4 |  6 |  8 | 10 | 12 | 14 | 16 | 18 | 20 | 22 | 24 | XX |
|    |    |    |    |    |    |    |    |    |    |    |    |    |

## Connections

| IDC | PCB | Signal | MCU |
|----:|----:|--------|-----|
|  1  |  1  | /CLEAR | PD0 |
|  3  |  7  | B1     | PB1 |
|  5  |  5  | STROBE | PD1 |
|  7  |  3  | B7,BRK | PB7 |
|  9  | 17  | B6     | PB6 |
| 11  | 15  | B5     | PB5 |
| 13  | 13  | B4     | PB4 |
| 15  | 11  | B3     | PB3 |
| 17  |  9  | B2     | PB2 |
|19,21|19,21| -12V   |     |
|23,25|23,25| +5V    | VCC |
|2..24|2..24| GND    | GND |
