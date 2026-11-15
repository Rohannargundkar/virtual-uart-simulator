#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "uart_config.h"
#include "uart_tx.h"
#include "uart_channel.h"
#include "uart_rx.h"

int main(void)
{
       
    UARTConfig config = {
        .baud_rate = 9600U,
        .data_bits = 8U,
        .parity = UART_PARITY_NONE,
        .stop_bits = 1U
    };

    UARTFrame tx_frame;
    UARTFrame rx_frame;

    uint16_t received_data = 0U;
    uint8_t data_bits;
    /* Test invalid configurations */

    config.baud_rate = 0U;
    assert(!uart_config_is_valid(&config));

    config.baud_rate = 9600U;

    config.data_bits = 4U;
    assert(!uart_config_is_valid(&config));

    config.data_bits = 8U;

    config.parity = (UARTParity)99;
    assert(!uart_config_is_valid(&config));

    config.parity = UART_PARITY_NONE;

    config.stop_bits = 3U;
    assert(!uart_config_is_valid(&config));

    /* Restore valid configuration */
    config.stop_bits = 1U;
    assert(uart_config_is_valid(&config));
    /* Test all supported data widths */
    for (data_bits = 5U; data_bits <= 9U; data_bits++)
    {
        config.data_bits = data_bits;

        assert(uart_config_is_valid(&config));
        assert(uart_transmit(1U, &config, &tx_frame));
        assert(uart_channel_transmit(&tx_frame, &rx_frame));

        assert(uart_receive(&rx_frame, &config, &received_data)
               == UART_ERROR_NONE);

        assert(received_data == 1U);
    }
    /* Test two stop bits */
config.data_bits = 8U;
config.parity = UART_PARITY_NONE;
config.stop_bits = 2U;

assert(uart_transmit('A', &config, &tx_frame));
assert(uart_channel_transmit(&tx_frame, &rx_frame));

assert(uart_receive(&rx_frame, &config, &received_data)
       == UART_ERROR_NONE);

assert(received_data == 'A');

/* Restore one stop bit for subsequent tests */
config.stop_bits = 1U;
    /* Test all parity modes */
    config.data_bits = 8U;

    for (config.parity = UART_PARITY_NONE;
         config.parity <= UART_PARITY_ODD;
         config.parity++)
    {
        assert(uart_transmit('A', &config, &tx_frame));
        assert(uart_channel_transmit(&tx_frame, &rx_frame));

        assert(uart_receive(&rx_frame, &config, &received_data)
               == UART_ERROR_NONE);

        assert(received_data == 'A');
    }

    /* Test parity error */
    config.parity = UART_PARITY_EVEN;

    assert(uart_transmit('A', &config, &tx_frame));
    assert(uart_channel_transmit(&tx_frame, &rx_frame));

    assert(uart_channel_corrupt_bit(&rx_frame, 1U));

    assert(uart_receive(&rx_frame, &config, &received_data)
           == UART_ERROR_PARITY);

    /* Test framing error */
    config.parity = UART_PARITY_NONE;

    assert(uart_transmit('A', &config, &tx_frame));
    assert(uart_channel_transmit(&tx_frame, &rx_frame));

    assert(uart_channel_corrupt_bit(&rx_frame,
                                    rx_frame.bit_count - 1U));

    assert(uart_receive(&rx_frame, &config, &received_data)
           == UART_ERROR_FRAMING);

    /* Test start bit error */
    assert(uart_transmit('A', &config, &tx_frame));
    assert(uart_channel_transmit(&tx_frame, &rx_frame));

    assert(uart_channel_corrupt_bit(&rx_frame, 0U));

    assert(uart_receive(&rx_frame, &config, &received_data)
           == UART_ERROR_INVALID_START);
/* Test invalid bit value */
assert(uart_transmit('A', &config, &tx_frame));
assert(uart_channel_transmit(&tx_frame, &rx_frame));

rx_frame.bits[1] = 2U;

assert(uart_receive(&rx_frame, &config, &received_data)
       == UART_ERROR_INVALID_FRAME);
    /* Test random noise at 0% */
    assert(uart_transmit('A', &config, &tx_frame));
    assert(uart_channel_transmit(&tx_frame, &rx_frame));

    srand(1U);

    assert(uart_channel_apply_noise(&rx_frame, 0U));

    assert(uart_receive(&rx_frame, &config, &received_data)
           == UART_ERROR_NONE);

    /* Test random noise at 100% */
    assert(uart_transmit('A', &config, &tx_frame));
    assert(uart_channel_transmit(&tx_frame, &rx_frame));

    assert(uart_channel_apply_noise(&rx_frame, 100U));

    assert(uart_receive(&rx_frame, &config, &received_data)
           != UART_ERROR_NONE);

    /* Invalid probability */
    assert(!uart_channel_apply_noise(&rx_frame, 101U));

    puts("All UART tests passed!");

    return 0;
}