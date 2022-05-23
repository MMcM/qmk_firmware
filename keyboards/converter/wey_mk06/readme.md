# Wey MK06

A converter for the Wey Technologies MK06. Should also work with other keyboards supporting the same Connector Boxes.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: MK06; Teensy LC

Make example for this keyboard (after setting up your build environment):

    make converter/wey_mk06:default

## Hardware

The keyboard has 9 direct ports, implementing various hardware bit-serial protocols.

| Port  | Protocol                  |
|-------|---------------------------|
| P1    | TTL Clock/Data (AT/PS2)   |
| P2    | TTL Clock/Data (AT/PS2)   |
| P3a   | TTL serial inverted (Sun) |
| P3d   | TTL serial inverted (Sun) |
| P4    | RS-232                    |
| P5    | RS-232                    |
| EXT   | RS-423                    |
| HPA   | RS-423                    |
| HPB   | RS-423                    |

A Connector Box exposes the first 6 of these with appropriate connectors (mini-DIN, D-Sub).

Up to 14 virtual ports can be defined by assigning them a DLINK address using the keyboard's Setup
menus. Again, a Connector Box would expose some DLINK addresses as physical connectors. One of the 3
RS-423 ports then needs to be defined as the DLINK port, which communicates with the Connector Box
-- or this converter -- to multiplex them.

16 workstations (WS) are selectable using special keys on the keyboard and assigned to these various ports.

### Connections

The main keyboard connector is a 36-pin mini-Centronics, also known as Half-Pitch Centronics
(HPCN36) or Mini Delta Ribbon (MDR). It was also used by some HP printers and some SCSI cables.  A
cable will have 18 twisted pairs and the signals often come in pairs.

| Pin | Signal      | | Pin | Signal      |
|----:|-------------|-|----:|-------------|
|   1 | GND         | |  19 | GND         |
|   2 | speaker L+  | |  20 | speaker L-  |
|   3 | HPA RXD     | |  21 | HPA TXD     |
|   4 | HPB RXD     | |  22 | HPB TXD     |
|   5 | +12V        | |  23 | RES2        |
|   6 | RES1        | |  24 | ??          |
|   7 | RES5        | |  25 | RES4        |
|   8 | speaker R+  | |  26 | speaker R-  |
|   9 | microphone  | |  27 | microphone  |
|  10 | EXT TXD     | |  28 | EXT RXD     |
|  11 | GND         | |  29 | +5V ??      |
|  12 | P1 CLK      | |  30 | P1 DAT      |
|  13 | P2 CLK      | |  31 | P2 DAT      |
|  14 | P3b RXD     | |  32 | P3b TXD     |
|  15 | P3a RXD     | |  33 | P3a TXD     |
|  16 | P5 RXD      | |  34 | P5 TXD      |
|  17 | P4 RXD      | |  35 | P4 TXD      |
|  18 | +12V        | |  36 | +12V        |

(RX/TX is from the perspective of the keyboard.)

The keyboard also has:
* 1 USB device port, implementing a CDC device (and not a keyboard)
* 2 USB host ports, for plugging in a mouse and thumb drive
* 1 PS2 mouse port
* 1 headphone jack
* 1 microphone jack

## Interfacing

The easiest way to interface without a Connector Box using PS2 and not this converter. Build a cable
that gives 12VDC from a wall wart to the two ends of the HPCN36 and connects Clock, Data, and Ground
in the center to a 6-pin mini-DIN male.
Then, if USB is required, use a dumb converter or Soarer's or TMK.

Even though Port 2 is labeled on Connector Boxes for a mouse, it can also be assigned to a WS. This
means that by connecting two DIN connectors to each of P1 and P2 it is possible to build two-way
KVM output without any components other than connectors.

This converter interfaces to any of the remaining serial ports and to DLINK ports. It enumerates to
USB as a single keyboard (and mouse). Different layouts can be assigned to different workstations or
ports.

The 32-bit Teensies suported by QMK have 3 UARTs, which can be assigned to ports. The normal setup
is UART0 to Host Port A as Host Terminal and UART1 to External Port as DLINK.

Port 3 is serial at 5V TTL voltage levels and so can only be used directly with a 5V tolerant MCU.
The other ports are RS-232 or RS-423 voltage levels and will require a serial level shifter like a
MAX3232.

### Firmware Variants

* `teensy_lc` for Teensy LC.

* `teensy_32` for Teensy 3.2.
