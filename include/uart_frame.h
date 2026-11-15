#ifndef UART_FRAME_H
#define UART_FRAME_H

#include <stddef.h>
#include <stdint.h>

#define UART_MAX_FRAME_BITS 13U

typedef struct
{
    uint8_t bits[UART_MAX_FRAME_BITS];
    size_t bit_count;
} UARTFrame;

#endif