# Deko Fast Action Keyboard

A converter for the Pinnacle Deko Fast Action Keyboard, a video editing keyboard with _lots_ of vintage Cherry blacks.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: Deko FAK, Teensy  

Make example for this keyboard (after setting up your build environment):

    make converter/deko_fak:default

## Hardware

Should work with any of the possible wirings for `PS2_DRIVER`.

* `usart`: Clock (pin 1) to `XCK` (`D5`) and Data (pin 2) to `RXD` (`D2`).
* `interrupt`: Clock to `D1` and Data to `D0`.
* `busywait`: Same.

## Features

The keyboard has 162 keys.

The LEDs in the 40 half-height keys, along with the 3 ordinary modifier LEDs, implement an LED matrix, with two levels, representing solid and blinking.

The 20x2 VFD interfaces through a virtual serial port and should be compatible with many serial LCD controlling programs.

## Keys ##

```
.---.---.  .---.   .---.---.---.---.  .---.---.---.---.   .---.---.  .---.---.  .---.---.
| 60| 17|  | 1F|   | 27| 2F| 37| 3F|  | 56| 5E| 6F| 13|   | 19| 39|  | 51| 53|  | 5C| 62|  +---+---+     +---+   +-----+
.-------.  .---.   .---------------.  .---------------.   .-------.  .-------.  .-------.  | 63| 64|     | 67|   |   68|
| 6A| 6D|  |E56|   |E5E|E08|E10|E18|  |E20|E28|E30|E38|   |E40|E48|  |E50|E57|  |E6F|E13|  +---+---+     +---+   +-----+
.---.---.  .---.   .---.---.---.---.  .---.---.---.---.   .---.---.  .---.---.  .---.---.
+---+---+  +---+   +---+---+---+---+  +---+---+---+---+  +---+---+---+---+  +---+---+---+
| 57| 5F|  | 76|   | 05| 06| 04| 0C|  | 03| 0B| 83| 0A|  | 01| 09| 78| 07|  |E7C| 7E|E77|
+---+---+  +---+   +---+---+---+---+  +---+---+---+---+  +---+---+---+---+  +---+---+---+
+---+---+  +---+---+---+---+---+---+---+---+---+---+---+---+---+---------+  +---+---+---+  .---.---.  +---+---+---+---+
| 08| 10|  | 0E| 16| 1E| 26| 25| 2E| 36| 3D| 3E| 46| 45| 4E| 55|       66|  |E70|E6C|E7D|  |E19|E39|  | 77|E4A| 7C| 7B|
+-------+  +-------------------------------------------------------------+  +-----------+  .-------.  +---------------+
| 18| 20|  |   0D| 15| 1D| 24| 2D| 2C| 35| 3C| 43| 44| 4D| 54| 5B|     5D|  |E71|E69|E7A|  |E51|E53|  | 6C| 75| 7D| 79|
+-------+  +-------------------------------------------------------------+  +---+---+---+  .-------.  +------------   +
| 28| 30|  |    58| 1C| 1B| 23| 2B| 34| 33| 3B| 42| 4B| 4C| 52|        5A|      |E75|      .---.---.  | 6B| 73| 74|   |
+-------+  +-------------------------------------------------------------+  +---+---+---+  |E5C|E5F|  +---------------+
| 38| 40|  |      12| 1A| 22| 21| 2A| 32| 31| 3A| 41| 49| 4A|          59|  |E6B|E72|E74|  .---.---.  | 69| 72| 7A|E5A|
+-------+  +-------------------------------------------------------------+  +---+---+---+  +-------+  +------------   +
| 48| 50|  |   14|    |  11 |           29              | E11 |    |  E14|  |E62|E63|E64|  |E67|E68|  |     70| 71|   |
+-------+  +-----+    +---------------------------------------+    +-----+  +---+---+---+  +-------+  +---------------+
```

`E` indicates `E0` prefix (`E1` in the case of Pause). `83` and `E08` can share a matrix row to save space.
