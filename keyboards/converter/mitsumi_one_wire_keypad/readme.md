# Mitsumi One-Wire Numeric Keypads

Converters for keypads that connect to the laptop using a sub-mini audio jack with only two conductors (TR).

* [Toshiba](toshiba_pa7354e/)
* [Compaq](compaq_2697/)

## Hardware

Ring is ground.

Tip should be connected to PD2 (Arduino pin 0) for data and to the collector of a PNP transistor that is under control of (base with a 4.7k or so resistor) PD3 (Arduino pin 1) to give software-controlled +5VDC power (emitter).
