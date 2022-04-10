
#include "debug.h"
#include "wait.h"
#include "m24.h"

#define DATA_PORT PORTD
#define DATA_PIN PIND
#define DATA_DDR DDRD
#define DATA_MASK (1 << 0)
#define CLOCK_MASK (1 << 1)
#define LED_MASK (1 << 6)
#define PULSE_HALF_WIDTH_MICROS 50

#define QUEUE_SIZE 16

typedef struct {
    uint8_t entries[QUEUE_SIZE];
    uint8_t in, out;
} queue;

static inline void queue_clear(queue *queue) {
    queue->in = queue->out = 0;
}

static inline bool queue_is_empty(const queue *queue) {
    return (queue->in == queue->out);
}

static inline bool queue_is_full(const queue *queue) {
    // One entry wasted to be able to check this easily.
    return (((queue->in + 1) % QUEUE_SIZE) == queue->out);
}

static inline uint8_t queue_remove(queue *queue) {
    uint8_t entry = queue->entries[queue->out];
    queue->out = (queue->out + 1) % QUEUE_SIZE;
    return entry;
}

static inline void queue_add(queue *queue, uint8_t entry) {
    queue->entries[queue->in] = entry;
    queue->in = (queue->in + 1) % QUEUE_SIZE;
}

static queue recv_queue, send_queue;

void m24_init(void) {
    queue_clear(&recv_queue);
    queue_clear(&send_queue);

    DATA_DDR |= CLOCK_MASK;
    DATA_PORT |= DATA_MASK | CLOCK_MASK;
}

void m24_run(void) {
    if (!queue_is_empty(&send_queue)) {
        uint8_t send_byte = queue_remove(&send_queue);

        DATA_DDR |= DATA_MASK;
        DATA_PORT &= ~DATA_MASK;
        DATA_PORT &= ~CLOCK_MASK;
        wait_us(PULSE_HALF_WIDTH_MICROS);

        for (uint8_t i = 0; i < 8; i++) {
            DATA_PORT |= CLOCK_MASK;
            wait_us(PULSE_HALF_WIDTH_MICROS);
            if (send_byte & (1 << i)) {
                DATA_PORT |= DATA_MASK;
            } else {
                DATA_PORT &= ~DATA_MASK;
            }
            DATA_PORT &= ~CLOCK_MASK;
            wait_us(PULSE_HALF_WIDTH_MICROS);
        }

        DATA_PORT |= DATA_MASK;
        DATA_PORT |= CLOCK_MASK;
        DATA_DDR &= ~DATA_MASK;
    } else {
        DATA_PORT &= ~CLOCK_MASK;
        wait_us(PULSE_HALF_WIDTH_MICROS);
        DATA_PORT |= CLOCK_MASK;
        wait_us(PULSE_HALF_WIDTH_MICROS);            
        if ((DATA_PIN & DATA_MASK) == 0) {
            uint8_t recv_byte = 0;
            for (uint8_t i = 0; i < 8; i++) {
                DATA_PORT &= ~CLOCK_MASK;
                wait_us(PULSE_HALF_WIDTH_MICROS);
                if ((DATA_PIN & DATA_MASK) != 0) {
                    recv_byte |= (1 << i);
                }
                DATA_PORT |= CLOCK_MASK;
                wait_us(PULSE_HALF_WIDTH_MICROS);
            }
            queue_add(&recv_queue, recv_byte);
        }
    }
}

bool m24_available(void) {
    return !queue_is_empty(&recv_queue);
}

uint8_t m24_recv(void) {
    uint8_t entry = queue_remove(&recv_queue);
    dprintf("R %02X\n", entry);
    return entry;
}

void m24_send(uint8_t data) {
    if (!queue_is_full(&send_queue)) {
        dprintf("S %02X\n", data);
        queue_add(&send_queue, data);
    }
}
