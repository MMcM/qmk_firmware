#pragma once

void m24_init(void);
void m24_run(void);
bool m24_available(void);
uint8_t m24_recv(void);
void m24_send(uint8_t data);
