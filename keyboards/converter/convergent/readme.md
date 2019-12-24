# Convergent CT-64

A converter for the Convegent Technologies AWS / CTOS keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: CT-64-00164, Teensy 3.2  

Make example for this keyboard (after setting up your build environment):

    make converter/convergent:default

## Protocol

All the details of the keyboard, including schematic, can be found in
[Workstation Hardware](http://bitsavers.org/pdf/convergent/aws_iws/A-09-00016-01-B_WorkstationHardware_Apr1981.pdf) in section 9 (starting at page 414 of 528). The table of scan codes is imperfect; there is another one in
[another edition](http://bitsavers.org/pdf/convergent/aws_iws/A-09-00111-01-A_AWS-2x0_HardwareManual_Vol1_Apr1982.pdf), but even together they don't get them all correct.

The keyboard protocol is TTL serial with negative polarity (idle low).

There are several choices for how to deal with this.

* `soft_serial` Use bit-banging; connect `RXD` to `D2` and `TXD` to `D3`.
* `hard_serial` Install an inverter IC between the MCU's UART ports and the keyboard pins.
* `teensy_32` Use an MCU that has registers for inverting the polarity.

The default assumes the last of these.

## Connections

The cable from the keyboard has a DE9 connector.

| DE9 | Signal  |
|-----|---------|
| 1   | RXD     |
| 2   | GND     |
| 3   | TXD     |
| 4   | GND     |
| 5   | RESET   |
| 6   | +5V     |
| 7   | +5V     |
| 8   | GND     |
| 9   | GND     |
