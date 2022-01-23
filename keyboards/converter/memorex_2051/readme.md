# Memorex 2051

A converter for the Memorex 2051 keyboard. The assembly is Micro Switch 83SD30-9 with 3-pin SD switches. The PCB is SD-16682.

The layout, key legends, and even some aspects of the communications protocol are copied from the IBM 5251.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: 83SD30-9, Teensy 2.0  

Make example for this keyboard (after setting up your build environment):

    make converter/memorex_2051:default

## Protocol

Like the 5251, the protocol is strobed parallel scan codes with a separate delay / ack signal in the other direction.

The scan codes are not the same, though.

## Connections

The cable connects with a DB25, also like the 5251, but again the pinout is not the same and only 5V power is needed.

The cable connects to the PCB with a 2x13 header, with all of the pins aligned, except that 8, 10, 12, 14, and 16 on the PCB are not connected and pin 26 on the PCB is connected to pin 16 on the d-sub connector.

The ID bits are just fixed jumpers, so it isn't really necessary to connect them. There does not seem to be any cable check (loopback) connection like on the 5251.

| DB25 | Signal | AVR |
|------|--------|-----|
|    1 | GND    | GND |
|    3 | ID0    | PF4 |
|    5 | ID1    | PF5 |
|    7 | ID2    | PF6 |
|    9 | ID3    | PF7 |
|   11 | DB2    | PB2 |
|   13 | DB1    | PB1 |
|   15 | DB0    | PB0 |
|   17 | DB3    | PB3 |
|   19 | DB4    | PB4 |
|   21 | DB5    | PB5 |
|   23 | DB6    | PB6 |
|   25 | DB7    | PB7 |
| 2,18 | +5V    | VCC |
|   20 | POR    | PD2 |
|   22 | CLICK  | PD3 |
|   24 | DELAY  | PD0 |
|   16 | DATA   | PD1 |
