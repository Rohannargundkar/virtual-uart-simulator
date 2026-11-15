#ifndef UART_CHANNEL_H
#define UART_CHANNEL_H

#include <stddef.h>
#include <stdbool.h>

#include "uart_frame.h"

bool uart_channel_transmit(const UARTFrame *tx_frame,
                           UARTFrame *rx_frame);

bool uart_channel_corrupt_bit(UARTFrame *frame,
                              size_t bit_position);

bool uart_channel_apply_noise(UARTFrame *frame,
                              unsigned int probability);

#endif