#include "uart_config.h"
#include <stddef.h>

bool uart_config_is_valid(const UARTConfig *config)
{
    if (config == NULL)
    {
        return false;
    }

    if (config->baud_rate == 0U)
    {
        return false;
    }

    if (config->data_bits < 5U || config->data_bits > 9U)
    {
        return false;
    }

    if (config->parity != UART_PARITY_NONE &&
        config->parity != UART_PARITY_EVEN &&
        config->parity != UART_PARITY_ODD)
    {
        return false;
    }

    if (config->stop_bits != 1U && config->stop_bits != 2U)
    {
        return false;
    }

    return true;
}