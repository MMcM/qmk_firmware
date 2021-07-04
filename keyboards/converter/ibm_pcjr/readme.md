# IBM PCjr

A converter for the IBM PCjr keyboard.

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: PCjr chiclet & regular keys, RJ & IR, DataVue 25 IR, Teensy 2.0  

Make example for this keyboard (after setting up your build environment):

    make converter/ibm_pcjr:default

## Protocol

Scan codes are the same as XT (set 2).

They are Manchester encoded as one start bit, eight data bits, and a parity bit, with a half-bit width of 220µs.

A wired connection indicates 0 and 1 half-bits as high and low.

A wireless connection distinguishes with 6 cycles of a 40kHz infrared signal at the start of a 1 half-bit.

Details in the [Technical Reference](https://archive.org/details/bitsavers_ibmpcpcjrPceNov83_24513363/page/n129/mode/2up).

## Connections

The wired connection is by a 6P6C RJ receptacle with a special locking connector that can detect when a cable is inserted, in order to disable IR. No additional wiring is needed, but it does take a little extra insertion force.

| RJ | Signal | AVR |
|----|--------|-----|
| 2  | /DATA  | D2  |
| 5  | +5V    | VCC |
| 6  | GND    | GND |

The wireless connection should present a digital version of the IR pulse to D0. I used a LM358 op-amp as a voltage comparator, with a 10kΩ resistor in series with a photodiode and a 10kΩ trim-pot as a reference voltage.

To leave out wireless, connect D0 to ground. To leave out wired, just leave D2 unconnected; it has a pull-up.

## DataVue 25

This keyboard uses the same IR protocol. The keyboard layout is different but all the scan codes are still standard.

Its wired connection uses a mini-DIN-3 connector.
