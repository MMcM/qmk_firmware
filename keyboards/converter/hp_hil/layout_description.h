
#pragma once

typedef struct {
    uint8_t keyset;
    uint8_t device_id;
    uint8_t data_address;
} layout_description_t;

extern const layout_description_t layout_descriptions[];
