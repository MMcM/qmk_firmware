# Wyse 4P4C

A converter for the TI Professional Computer keyboard using a DIN-5 connector.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: Low-Profile, Teensy 3.2

Make example for this keyboard (after setting up your build environment):

    make converter/tipc/teensy_32:default

## Protocol

See [Maintanence Handbook](https://archive.org/details/bitsavers_tiprofessiaintenanceHandbook020183_13063686/page/n33/mode/2up) for a summary of the signals.

The protocol is inverted (idle low) TTL serial with even parity. The from keyboard direction is 2440 baud and the to keyboard is 305 baud, so two UARTs with separate clock registers are needed.

## Connections

The keyboard has a 5V regulator, so power around 9-12V is needed.

Pins 2 and 3 are connected inside the keyboard, so that the computer can tell whether a keyboard is plugged in. See [ROM init routine](https://archive.org/details/bitsavers_tiprofessiomputerSystemRomListingv1.23_15910660/page/n187/mode/2up) for example.

| DIN | Signal        | MCU |
|-----|---------------|-----|
|   1 | Ground        | GND |
|   2 | TX (to kbd)   | TX3 |
|   3 | loopback      | RX3 |
|   4 | +12VDC        |     |
|   5 | RX (from kbd) | RX1 |

It is important that `UART2` is used for transmit, because otherwise 300ish baud is too slow for a 48MHz system clock (not enough divider bits) and that one uses the peripheral clock, which can be slowed down.

## Key Codes

See [Technical Reference](https://archive.org/details/bitsavers_tiprofessiTechRefMay1984_25647170/page/n201/mode/2up).

```
+---|---+---+---+      +---+---+---+---+      +---+---+---+---+                 +---+---+---+---+
|101|102|103|104|      |  1|  2|  3|  4|      |  5|  6|  7|  8|                 | 47| 48|100| 90|
+---|---+---+---+      +---+---+---+---+      +---+---+---+---+                 +---+---+---+---+

+----+---+---+---+---+---+---+---+---+---+---+---+---+----+---+                 +---+---+---+---+
|  65|  9| 10| 11| 12| 13| 14| 15| 16| 17| 18| 19| 20|  21| 22|                 | 23| 24| 25| 26|
+-------------------------------------------------------------+      +---+      +---------------+
|    49| 50| 51| 52| 53| 54| 55| 56| 57| 58| 59| 60| 61|  | 62|      | 64|      | 39| 40| 33| 34|
+------------------------------------------------------|  |---+  +---+---+---+  +---------------+
|   |   | 66| 67| 68| 69| 70| 71| 72| 73| 74| 75| 76|   77| 78|  | 79| 80| 46|  | 31| 32| 41| 42|
+-------------------------------------------------------------+  +---+---+---+  +---------------+
|   |     | 82| 83| 84| 85| 86| 87| 88| 89| 91| 92|     |            | 96|      | 27| 35| 43| 30|
+---+-----+---+-------------------------------+---+-----+            +---+      +---+---+---|   |
              |                             81|                                 |     29| 44|   |
              +-------------------------------+                                 +-------+---+---+
```
