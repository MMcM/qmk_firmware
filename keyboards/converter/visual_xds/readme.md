# Visual XDS

A converter for a Visual Technologies X Display Station keyboard. It is similar to the Visual 200 (LK201 clone), but adding Esc (left of Tab) and Back Space (right of Delete) keys.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: XDS; Itsy-Bitsy 5V

Make example for this keyboard (after setting up your build environment):

    make converter/visual_xds:default

## Hardware

The keyboard uses a 5-pin DIN connector.

| DIN | Signal        | AVR |
|-----|---------------|-----|
|  1  | RX (to kbd)   | TX  |
|  2  | TX (from kdb) | RX  |
|  3  | Ground        | GND |
|  4  | Ground        | GND |
|  5  | Vcc +5V       | 5V  |

The protocol is 600 baud TTL serial.
