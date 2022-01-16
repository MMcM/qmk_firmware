# Sharp X1 Turbo

A converter for the Sharp X1 Turbo keyboard. These have green Alps switches.

The keyboard has a slider switch on the side labeled `A - B`. Setting B enables "game" mode, where 24 of the keys accurately report their activation state.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: DSETK0011CE00, Adafruit Itsy-bitsy 5V  

Make example for this keyboard (after setting up your build environment):

    make converter/sharp_x1:default

## Protocol

The protocol is described in [this document](http://www.x1center.org/resource/x1kbd.pdf).

A bit serial protocol distinguishes 0 and 1 by means of pulse widths over the single data line.

There are two kinds of reports, regular keys and game mode. At root, the regular key reports send ASCII characters, but these are supplemented with the current state of the shift keys. Moreover, since there is a "no key" report, it is possible to mostly accurate recreate key presses and releases. The game mode reports transmit a bitmask of the 24 special keys used in gaming.

## Connections

The cable has a 3.5mm stereo audio (TRS) plug.

| PCB | Color | TRS | Signal | AVR |
|-----|-------|-----|--------|-----|
|   1 | White | T   | +5V    | Vcc |
|   2 | Red   |  R  | DATA   | PD0 |
|   3 | Black |   S | GND    | GND |
