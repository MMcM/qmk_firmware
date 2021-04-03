# DG 6246-A

A converter for the Data General 6246-A terminal keyboard for the D210/D211 terminals.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: 6246-A, Teensy 2.0  

Make example for this keyboard (after setting up your build environment):

    make converter/dg_6246a:default

The pinout of the DE-9 is given in the [user manual](https://archive.org/details/bitsavers_dgterminal0andD211DisplayTerminalsUsersManualJul83_10842530/page/n52/mode/1up).

The keyboard on the D411/D461 terminal has a very similar [layout](https://archive.org/details/bitsavers_dgterminal411D461DisplayTerminalsUsersManualMar86_5475999/page/n26/mode/1up).
The connector is round but the [pin names](https://archive.org/details/bitsavers_dgterminal411D461DisplayTerminalsUsersManualMar86_5475999/page/n33/mode/1up) are the same, so it may be that the signals are the same.

An outline of the protocol is in the [patent](https://patents.google.com/patent/US4459581A/en).

## Hardware

Pinout for J2 DE-9 / DIN-45326.

| DE | DIN | Color  | Signal     | AVR |
|----|-----|--------|------------|-----|
|  1 |     |        | PE         |     |
|  2 |  4  | brown  | CLK COMMON | GND |
|  3 |  5  | red    | +5V        | VCC |
|  4 |  3  | orange | KBC RESET  | PC7 |
|  5 |  2  | yellow | SI         | PD2 |
|  6 |  8  |        | N/C        |     |
|  7 |  6  | green  | SO         | PD3 |
|  8 |  1  | black  | /SCLK      | PD1 |
|  9 |  7  | white  | /KBIRQ     | PD0 |
