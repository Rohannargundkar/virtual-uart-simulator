
#ifndef UART_TX_H
#define UART_TX_H

#include <stdbool.h>
#include <stdint.h>

#include "uart_config.h"
#include "uart_frame.h"

bool uart_transmit(uint16_t data,
                   const UARTConfig *config,
                   UARTFrame *frame);

#endif
