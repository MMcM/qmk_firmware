# PS/2 keyboard with Serial Mouse

A converter for the a PS/2 (DIN-5) keyboard (scan code set 2) with a Serial (DE-9) mouse (Microsoft protocol).

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: Ortek MCK-106-TB, Teensy  

Make example for this keyboard (after setting up your build environment):

    make converter/ps2_serial_mouse:default

The DIN-5 keyboard connector has Data on D0 and Clock on D1.

The serial port needs an RS-232 level shifter like a MAX232 and is then connected to RXD1 (D2) and TXD1 (D3).

RTS and DTR also need to be set, since that is how the mouse gets power. RTS can be wired to Vs+ from the MAX232 and DTR to the second transmit line, controlled by GPIO C6.

## Keys

Standard 101-key layout. Note that a trackball often takes the place of the arrow keys.

```
+---+   +---+---+---+---+  +---+---+---+---+  +---+---+---+---+  +---+---+---+
| 76|   | 05| 06| 04| 0C|  | 03| 0B| 83| 0A|  | 01| 09| 78| 07|  |17C| 7E|277|
+---+   +---+---+---+---+  +---+---+---+---+  +---+---+---+---+  +---+---+---+
+---+---+---+---+---+---+---+---+---+---+---+---+---+---------+  +---+---+---+  +---+---+---+---+
| 0E| 16| 1E| 26| 25| 2E| 36| 3D| 3E| 46| 45| 4E| 55|       66|  |170|16C|17D|  | 77|14A| 7C| 7B|
+-------------------------------------------------------------+  +-----------+  +---------------+
|   0D| 15| 1D| 24| 2D| 2C| 35| 3C| 43| 44| 4D| 54| 5B|     5D|  |171|169|17A|  | 6C| 75| 7D| 79|
+-------------------------------------------------------------+  +-----------+  +------------   +
|    58| 1C| 1B| 23| 2B| 34| 33| 3B| 42| 4B| 4C| 52|        5A|                 | 6B| 73| 74|   |
+-------------------------------------------------------------+      +---+      +---------------+
|      12| 1A| 22| 21| 2A| 32| 31| 3A| 41| 49| 4A|          59|      |175|      | 69| 72| 7A|15A|
+-------------------------------------------------------------+  +---+---+---+  +------------   +
|   14|    |  11 |           29              | 111 |    |  114|  |16B|172|174|  |     70| 71|   |
+-----+    +---------------------------------------+    +-----+  +---+---+---+  +---------------+
```
