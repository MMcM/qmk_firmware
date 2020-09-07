# CTM

A converter for the CTM Cherry 601-1518 keyboard.

The part number for this is G80-1114HAC/03.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: 601-1518, Teensy 3.2, Teensy 2.0  

Make example for this keyboard (after setting up your build environment):

    make converter/ctm:default

## Protocol

The keyboard protocol is TTL serial with negative polarity (idle low).

There are several choices for how to deal with this.

* `soft_serial` Use bit-banging; connect `RXD` to `D2` and `TXD` to `D3`.
* `hard_serial` Install an inverter IC between the MCU's UART ports and the keyboard pins.
* `teensy_32` Use an MCU that has registers for inverting the polarity.

The default assumes the last of these.

## Connections

The cable from the keyboard has a DE9 connector.

| DE9 | S1 | color  | Signal        |
|-----|----|--------|---------------|
| 1   | 5  | yellow | GND           |
| 2   | 1  | white  | +5V           |
| 3   |    |        | N/C           |
| 4   | 3  | brown  | TX (to kbd)   |
| 5   | 7  | blue   | RESET         |
| 6   | 4  | green  | RX (from kbd) |
| 7   |    |        | N/C           |
| 8   | 6  | gray   | GND           |
| 9   | 2  | pink   | N/C           |
