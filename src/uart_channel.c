#include <stddef.h>
#include <stdlib.h>

#include "uart_channel.h"

bool uart_channel_transmit(const UARTFrame *tx_frame,
                           UARTFrame *rx_frame)
{
    size_t i;

    if (tx_frame == NULL || rx_frame == NULL)
    {
        return false;
    }

    if (tx_frame->bit_count == 0U ||
        tx_frame->bit_count > UART_MAX_FRAME_BITS)
    {
        return false;
    }

    rx_frame->bit_count = tx_frame->bit_count;

    for (i = 0U; i < tx_frame->bit_count; i++)
    {
        if (tx_frame->bits[i] > 1U)
        {
            return false;
        }

        rx_frame->bits[i] = tx_frame->bits[i];
    }

    return true;
}

bool uart_channel_corrupt_bit(UARTFrame *frame, size_t bit_position)
{
    if (frame == NULL ||
        frame->bit_count == 0U ||
        frame->bit_count > UART_MAX_FRAME_BITS ||
        bit_position >= frame->bit_count ||
        frame->bits[bit_position] > 1U)
    {
        return false;
    }

    frame->bits[bit_position] ^= 1U;

    return true;
}

bool uart_channel_apply_noise(UARTFrame *frame,
                              unsigned int probability)
{
    size_t i;

    if (frame == NULL ||
        frame->bit_count == 0U ||
        frame->bit_count > UART_MAX_FRAME_BITS ||
        probability > 100U)
    {
        return false;
    }

    for (i = 0U; i < frame->bit_count; i++)
    {
        if (frame->bits[i] > 1U)
        {
            return false;
        }
    }

    for (i = 0U; i < frame->bit_count; i++)
    {
        if ((unsigned int)(rand() % 100) < probability)
        {
            frame->bits[i] ^= 1U;
        }
    }

    return true;
}