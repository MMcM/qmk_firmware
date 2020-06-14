# Zenith Z-29

A converter for the Zenith Z-29 keyboard.
This terminal is the same as the Heathkit H-29 and OEM'ed as the Morrow MDT-60.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: Z-29 keyboard, Pro Micro

Make example for this keyboard (after setting up your build environment):

    make converter/z29:default

The keyboard does not send up transitions.
A converter needs also needs to reverse the affects of Ctrl and Shift on ASCII characters, and so is not very flexible.

## Hardware

The keyboard communicates using a proprietary 8-bit serial protocol. The keyboard is powered with 12VDC.

| RJ | Color  | Std Color | Signal        |
|----|--------|-----------|---------------|
| 1  | Blue   | White     | +12V          |
| 2  | Yellow | Black     | Reset         |
| 3  | Green  | Red       | RX (from kbd) |
| 4  | Red    | Green     | TX (to kbd)   |
| 5  | White  | Yellow    | Ground        |
| 6  | Black  | Blue      | Ground        |
