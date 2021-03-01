# Omron Turbo

Some laptop(?) keyboard using amber Omron switches with a QWERTZ layout and a Turbo button

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  

Make example for this keyboard (after setting up your build environment):

    make omron_turbo:qwertz

The Turbo switch is a locking key with each side connected separately to the IDC header.

| IDC | Signal | LC | MCU |
|-----|--------|----|-----|
| 1   | Col 0  | 0  | B16 |
| 2   | Row 0  | 23 | C2  |
| 3   | Col 1  | 1  | B17 |
| 4   | Row 1  | 22 | C1  |
| 5   | Col 2  | 2  | D0  |
| 6   | Row 2  | 21 | D6  |
| 7   | Col 3  | 3  | A1  |
| 8   | Row 3  | 20 | D5  |
| 9   | Col 4  | 4  | A2  |
| 10  | Row 4  | 19 | B2  |
| 11  | Col 5  | 5  | D7  |
| 12  | Row 5  | 18 | B3  |
| 13  | Col 6  | 6  | D4  |
| 14  | Row 6  | 17 | B1  |
| 15  | Col 7  | 7  | D2  |
| 16  | Row 7  | 16 | B0  |
| 17  | Row 10 | 8  | D3  |
| 18  | Row 8  | 15 | C0  |
| 19  | N/C    |    |     |
| 20  | Row 9  | 14 | D1  |
| 21  | Row 11 | 9  | C3  |
| 22  | R1-R8  | 3V |     |
| 23  | Turbo  | 11 | C6  |
| 24  | Turbo  | 12 | C7  |
