#include <stddef.h>

#include "uart_rx.h"

UARTError uart_receive(const UARTFrame *frame,
                       const UARTConfig *config,
                       uint16_t *received_data)
{
    size_t expected_count;
    size_t bit_index;
    size_t stop_start;

    uint8_t one_count = 0U;
    uint8_t parity_bit;
    uint8_t expected_parity;

    uint16_t reconstructed_data = 0U;

    if (frame == NULL || config == NULL || received_data == NULL)
    {
        return UART_ERROR_INVALID_FRAME;
    }

    if (!uart_config_is_valid(config))
    {
        return UART_ERROR_INVALID_CONFIG;
    }

    expected_count = 1U + config->data_bits + config->stop_bits;

    if (config->parity != UART_PARITY_NONE)
    {
        expected_count++;
    }

    if (frame->bit_count != expected_count ||
        frame->bit_count > UART_MAX_FRAME_BITS)
    {
        return UART_ERROR_INVALID_FRAME;
    }

    for (bit_index = 0U; bit_index < frame->bit_count; bit_index++)
    {
        if (frame->bits[bit_index] > 1U)
        {
            return UART_ERROR_INVALID_FRAME;
        }
    }

    /* Check start bit */
    if (frame->bits[0] != 0U)
    {
        return UART_ERROR_INVALID_START;
    }

    /* Receive data bits */
    for (bit_index = 0U; bit_index < config->data_bits; bit_index++)
    {
        uint8_t bit = frame->bits[bit_index + 1U];

        reconstructed_data |= (uint16_t)((uint16_t)bit << bit_index);

        if (bit == 1U)
        {
            one_count++;
        }
    }

    stop_start = 1U + config->data_bits;

    /* Check parity */
    if (config->parity != UART_PARITY_NONE)
    {
        parity_bit = frame->bits[stop_start];

        expected_parity = (uint8_t)(one_count % 2U);

        if (config->parity == UART_PARITY_ODD)
        {
            expected_parity ^= 1U;
        }

        if (parity_bit != expected_parity)
        {
            return UART_ERROR_PARITY;
        }

        stop_start++;
    }

    /* Check stop bits */
    for (bit_index = 0U; bit_index < config->stop_bits; bit_index++)
    {
        if (frame->bits[stop_start + bit_index] != 1U)
        {
            return UART_ERROR_FRAMING;
        }
    }

    *received_data = reconstructed_data;

    return UART_ERROR_NONE;
}