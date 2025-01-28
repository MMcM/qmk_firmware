# Tektronix 4120

A converter for the Tektronix 4120 series keyboard.

The keyboard has thirteen LEDs, of which nine are underneath keys.
There are two thumbwheels.
The keyboard can also apparently interface to a serial mouse and a joystick.

This is a Keytronic foam and foil keyboard with part number 119-1836-00.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: Tek 4120, Teensy 2.0  

Make example for this keyboard (after setting up your build environment):

    make converter/tektronix_4120:default

## Protocol

The keyboard protocol is 1200 baud TTL serial.

## Connections

The keyboard has two 5V regulators, so power around 8-12V is needed.

The cable from the keyboard has a DIN-5 connector.

| DIN | J1 | color  | Signal        |
|-----|----|--------|---------------|
| 1   | 1  | red    | TD (to kbd)   |
| 2   | 2  | green  | RX (from kbd) |
| 3   | 4  | black  | /RESET        |
| 4   | 5  | white  | GND           |
| 5   | 6  | orange | +12VDC        |

## Keys

```
                        +---+---+---+---+     +---+---+---+---+    +---+---+---+---+
                        |2D |2E |2C |2F |     |1D |1C |1F |1E |    |1B |1A |19 |18 |
                        +---+---+---+---+     +---+---+---+---+    +---+---+---+---+
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+  +---+---+---+---+     +---+
|24 |25 |54 |55 |44 |45 |34 |35 |3C |3D |4C |4D |0C |0D |14 |15 |  |07 |5C |5D |5E |     |28 |
+---------------------------------------------------------------+  +---------------+     +---+
|26   |27 |56 |57 |46 |47 |36 |37 |3E |3F |4E |4F |0E |0F   |16 |  |04 |05 |06 |5F |     |29 |
+--------------------------------------------------------------++  +---------------+     +---+
 |22   |20 |52 |50 |42 |40 |32 |30 |3A |38 |4A |48 |0A |08     |   |01 |02 |03 |60 |     |2A |
 +-+-----------------------------------------------------------+   +-----------|   |     +---+
   |21 |23   |51 |53 |41 |43 |31 |33 |39 |3B |49 |4B |09   |0B |   |00     |61 |   |     |2B |
   +---+-----+---+-------------------------------+---+-----+---+   +-------+---+---+     +---+
                 |13                             |
                 +-------------------------------+
```
