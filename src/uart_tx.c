#include <stddef.h>

#include "uart_tx.h"

bool uart_transmit(uint16_t data,
                   const UARTConfig *config,
                   UARTFrame *frame)
{
    size_t bit_index;
    uint8_t one_count = 0U;
    uint8_t parity_bit;
    uint16_t max_data;

    if (config == NULL || frame == NULL)
    {
        return false;
    }

    if (!uart_config_is_valid(config))
    {
        return false;
    }

    max_data = (uint16_t)((1U << config->data_bits) - 1U);

    if (data > max_data)
    {
        return false;
    }

    frame->bit_count = 0U;

    /* Start bit */
    frame->bits[frame->bit_count++] = 0U;

    /* Data bits: LSB first */
    for (bit_index = 0U; bit_index < config->data_bits; bit_index++)
    {
        uint8_t bit = (uint8_t)((data >> bit_index) & 1U);

        frame->bits[frame->bit_count++] = bit;

        if (bit == 1U)
        {
            one_count++;
        }
    }

    /* Parity bit */
    if (config->parity != UART_PARITY_NONE)
    {
        parity_bit = (uint8_t)(one_count % 2U);

        if (config->parity == UART_PARITY_ODD)
        {
            parity_bit ^= 1U;
        }

        frame->bits[frame->bit_count++] = parity_bit;
    }

    /* Stop bits */
    for (bit_index = 0U; bit_index < config->stop_bits; bit_index++)
    {
        frame->bits[frame->bit_count++] = 1U;
    }

    return true;
}