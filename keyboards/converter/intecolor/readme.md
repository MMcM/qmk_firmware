# Intecolor 101894

A converter for the Intecolor 101894

Keyboard Maintainer: [MMcM](https://github.com/MMcM)  
Hardware Supported: 101894, Teensy  

Make example for this keyboard (after setting up your build environment):

    make converter/intecolor:default

The keyboard does not have any processing elements. Inputs load a row address (though it is physically more like a column) and outputs give the state of columns in that row. Some additional keys are have dedicated output pins.

## Connections

The cable ends in a DB-25. The PCB has a 26-pin IDC connector with the following pins:
```
13 12 11 10  9  8  7 19 18 17 16 15 14
25 24 23 22 21 20     6  5  4  3  2  1
```

| DB | Signal     | AVR |
|----|------------|-----|
|  2 | ROW BIT 1  | PD0 |
|  3 | ROW BIT 3  | PD2 |
|  7 | COLUMN 1   | PB0 |
|  8 | COLUMN 2   | PB1 |
|  9 | COLUMN 3   | PB2 |
| 10 | COLUMN 4   | PB3 |
| 11 | REPT       | PF4 |
| 12 | CONTROL    | PF0 |
| 13 | CPU RESET  | PF5 |
| 14 | ROW BIT 2  | PD1 |
| 15 | ROW BIT 4  | PD3 |
| 18 | GROUND     | GND |
| 19 | COLUMN 5   | PB4 |
| 20 | COLUMN 6   | PB5 |
| 21 | COLUMN 7   | PB6 |
| 22 | ALPHA LOCK | PF6 |
| 23 | SHIFT      | PF1 |
| 25 | +5V        | VCC |

## Keys

```
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+   +---+---+   +---+
|01 |11 |21 |31 |41 |51 |61 |71 |81 |91 |A1 |B1 |C1 |D1 |E1 |C0 |F1 |   |C5 |B5 |   |X5*|
+---+---+---+-------------------------------------------------------+   +-------+---+---+
            |55 |D0 |E0 |F0 |F5 |E5 |B6 |C6 |D6 |E6 |F6 |A0 |85 |90 |   |45 |15 |25 |35 |
+---+---+   +-------------------------------------------------------+   +---+---+---+---+
|00 |40 |   |B0 |13 |23 |33 |43 |53 |63 |73 |83 |93 |03 |D3 |A5 |05 |            
+-------+   +-------------------------------------------------------+   +---+---+---+---+
|10 |50 |   |95   |16 |76 |52 |26 |46 |96 |56 |92 |F2 |06 |02  |D5 |    |73 |83 |93 |F3 |
+-------+   ++-------------------------------------------------|   |    +---------------+
|20 |60 |    |X0   |12 |36 |42 |62 |72 |82 |A2 |B2 |C2 |B3 |A3 |   |    |43 |53 |63 |A4 |
+-------+    +-+---------------------------------------------------+    +---------------+
|30 |70 |      |X1   |A6 |86 |32 |66 |22 |E2 |D2 |C3 |E3 |F3 |X1   |    |13 |23 |33 |D3 |
+-------+      +-----+---------------------------------------+-----+    +---------------+
|X0+X1  |            |X6 |04                             |X4 |          |03 |E3 |D4 |B4 |
+-------+            +---+-------------------------------+---+          +---+---+---+---+
```

Notes:
* The `CPU RESET` signal is only activated if `SHIFT` is also pressed.
* The two `SHIFT` keys generate the same code.
* Most of the numpad keys generate the same code as some other key.
* The `COMMAND` key is equivalent to `CONTROL` and `SHIFT` together.
* The `ALPHA LOCK` key is physically locking.
