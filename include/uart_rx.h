#ifndef UART_RX_H
#define UART_RX_H

#include <stdint.h>

#include "uart_config.h"
#include "uart_frame.h"
#include "uart_errors.h"

UARTError uart_receive(const UARTFrame *frame,
                       const UARTConfig *config,
                       uint16_t *received_data);

#endif