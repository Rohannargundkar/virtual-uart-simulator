#ifndef UART_CONFIG_H
#define UART_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    UART_PARITY_NONE,
    UART_PARITY_EVEN,
    UART_PARITY_ODD
} UARTParity;

typedef struct
{
    uint32_t baud_rate;
    uint8_t data_bits;
    UARTParity parity;
    uint8_t stop_bits;
} UARTConfig;

bool uart_config_is_valid(const UARTConfig *config);

#endif