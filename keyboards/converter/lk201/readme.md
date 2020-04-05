# DEC LK201

A converter for the Digital LK201 / LK401 keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: LK201, LK401; Teensy 2.0, Teensy LC

Make example for this keyboard (after setting up your build environment):

    make converter/lk201:default

## Hardware

The keyboard protocol is 4800 baud RS-423. The keyboard is powered with +12V.

| RJ | Color  | Signal        |
|----|--------|---------------|
| 1  | Black  | TX (to kbd)   |
| 2  | Red    | Ground        |
| 3  | Green  | +12V          |
| 4  | Yellow | RX (from kbd) |

The interface board must supply power to the keyboard and convert from serial to TTL levels.

Two approaches to this are possible.

### RS-232 converter

The signal levels are also compatible with RS-232, for which there are simple all-in-one converters such as the MAX232.

One additional advantage of this approach is that by using a 3V converter, such as MAX3232, a Teensy 3 (LC or 3.n) MCU can be used.

12V is used solely to power the keyboard.

### RS-423 receiver and driver

This is how the keyboard itself and the VT-200 terminal worked. The schematic for the keyboard is at
http://bitsavers.org/pdf/dec/terminal/lk201/MP01395_LK201_Schematic_Oct83.pdf (page 16/21) and for the terminal at
http://bitsavers.org/pdf/dec/terminal/vt220/VT220_Schematic_Aug83.pdf (page 5/17).

A uA9639 differential receiver converts RX.

A uA9636 driver converts TX. It needs Vcc+ (+12V) and Vcc- (-12V).
This can be gotten from the same 12V power source using a DC/DC dual output converter like the RB-1212D.

## Firmware Variants

All of these use the first hardware UART serial port.

* `teensy_20` for ATMega32U4.

* `teensy_32` for Teensy 3.2.

* `teensy_lc` for Teensy LC. There isn't enough space to enable the debug console.

## Elektronica MS 7004

The same protocol is used by the Электроника МС 7004, but with an ОНЦ-ВГ-4-5/16-В, ГОСТ 12368-78 = DIN-5 41524 connector.

| КТ1 | КТ2 | Сигнал | Signal        |
|-----|-----|--------|---------------|
| 3,4 |  2  | Вход   | TX (to kbd)   |
| 7,8 |  1  | +12В   | +12V          |
| 1,2 |  4  | Общий  | Ground        |
| 5,6 |  3  | Выход  | RX (from kbd) |
