# NMB TVI

A converter for the NMB Hi-Tek 725 series keyboards used by Televideo terminals.
Specifically, 110695 for the TeleVideo 9220, 130947 for Televideo 905 / 965 (and rebranded dti 510), and 116535 for Televideo 935.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: NMB 110695, NMB 130947 (dti 510), NMB 116535, Pro Micro

Make example for this keyboard (after setting up your build environment):

    make converter/nmb_tvi:default

Not all keyboards send key up transitions. It does track the four shifting keys, `Ctrl`, `Shift`, `Lock`, and `Funct`, separately.

The 116535 can be put into a "raw" mode where it sends make / break codes.

## Hardware

The keyboard protocol is 9600 baud serial. The keyboards with 6P6C RJ jacks are powered with 12VDC.

| RJ | Color  | Signal        | AVR |
|----|--------|---------------|-----|
| 1  | White  | Reset         | PD1 |
| 2  | Black  | TX (to kbd)   | PD3 |
| 3  | Red    | RX (from kbd) | PD2 |
| 4  | Green  | Ground        | GND |
| 5  | Yellow | +12V          |     |
| 6  | Blue   | Chassis       |     |

The keyboards with 4P4C RJ jacks use 5VDC.

| RJ | Color  | Signal        | AVR |
|----|--------|---------------|-----|
| 1  | Yellow | +5V           | VCC |
| 2  | Green  | Ground        | GND |
| 3  | Red    | TX (to kbd)   | PD3 |
| 4  | Black  | RX (from kbd) | PD2 |
