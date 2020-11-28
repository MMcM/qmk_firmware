# HP 262x

A converter for the 262x family of HP keyboards, including 2621, 2622, and 2623.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: 2621, 2622, Teensy 2.0

Make example for this keyboard (after setting up your build environment):

    make converter/hp_262x:default

Complete technical details are availble in Bitsavers for the [standard](http://bitsavers.org/pdf/hp/terminal/262x/13220-91001_Keyboard_Module_Jan80.pdf) and [extended](http://bitsavers.org/pdf/hp/terminal/262x/13220-91061_Extended_Keyboard_Module_Aug81.pdf) keyboard PCAs.

A DA-15 D-sub cable is connected to a header J1; both have the same pin numbering.

| J1 | Signal | AVR |
|----|--------|-----|
|  1 | KEYA0  | B0  |
|  2 | KEYA1  | B1  |
|  3 | KEYA2  | B2  |
|  4 | KEYA3  | B3  |
|  5 | KEYA4  | B4  |
|  7 | KEYA5  | B5  |
|  8 | KEYA6  | B6  |
|  9 | /KEYACT| D3  |
| 10 | GROUND | GND |
| 11 | BELL   | C6* |
| 12 | +5V    | VCC |

Note: the speaker bell is between pin 11 and +5, so the GPIO can be connected to a NPN transistor with a current limiting resistor (470Ω works fine) and then to ground and to the bell with another resistor (again 470Ω works, though the original design had only 47Ω).
