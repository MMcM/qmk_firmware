
#pragma once

typedef union {
    uint8_t raw;
    struct {
        unsigned id:1;
        unsigned bell:1;
        unsigned click:1;
        unsigned caps:1;
        unsigned repeat:1;
        unsigned disable:1;
        unsigned offline:1;
    };
} z29_state_t;

extern z29_state_t z29_state;
