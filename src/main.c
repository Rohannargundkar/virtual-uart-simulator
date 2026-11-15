#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>

#include "uart_config.h"
#include "uart_tx.h"
#include "uart_channel.h"
#include "uart_rx.h"

#define MAX_INPUT 128U

static void display_frame(const UARTFrame *frame,
                          const UARTConfig *config)
{
    size_t i;
    size_t parity_position = 1U + config->data_bits;
    size_t stop_position = parity_position;

    printf("\nUART FRAME:\n");

    for (i = 0U; i < frame->bit_count; i++)
    {
        if (i == 0U)
        {
            printf("START: %u\n", frame->bits[i]);
        }
        else if (i < parity_position)
        {
            printf("DATA[%zu]: %u\n", i - 1U, frame->bits[i]);
        }
        else if (config->parity != UART_PARITY_NONE &&
                 i == parity_position)
        {
            printf("PARITY: %u\n", frame->bits[i]);
            stop_position++;
        }
        else if (i >= stop_position)
        {
            printf("STOP: %u\n", frame->bits[i]);
        }
    }
}

static const char *error_message(UARTError error)
{
    switch (error)
    {
        case UART_ERROR_NONE:
            return "No error";

        case UART_ERROR_INVALID_START:
            return "Invalid start bit";

        case UART_ERROR_PARITY:
            return "Parity error";

        case UART_ERROR_FRAMING:
            return "Framing error";

        case UART_ERROR_INVALID_FRAME:
            return "Invalid frame";

        case UART_ERROR_INVALID_CONFIG:
            return "Invalid configuration";

        default:
            return "Unknown error";
    }
}

int main(void)
{
    char input[MAX_INPUT];
    char received[MAX_INPUT];

    size_t i;

    unsigned int parity_choice;
    unsigned int noise_probability;

    UARTConfig config = {0};

    UARTFrame tx_frame;
    UARTFrame rx_frame;

    uint16_t received_char;

    UARTError error;

    srand((unsigned int)time(NULL));

    printf("=== VIRTUAL UART SIMULATOR ===\n\n");

    printf("Enter data: ");

    if (fgets(input, sizeof(input), stdin) == NULL)
{
    printf("Input error.\n");
    return 1;
}

/* Detect input that exceeds the buffer */
if (strchr(input, '\n') == NULL && !feof(stdin))
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        /* Discard remaining input */
    }

    printf("Input is too long.\n");
    return 1;
}

input[strcspn(input, "\n")] = '\0';

    if (input[0] == '\0')
    {
        printf("Data cannot be empty.\n");
        return 1;
    }

    printf("\nEnter baud rate: ");

    if (scanf("%" SCNu32, &config.baud_rate) != 1)
    {
        printf("Invalid baud rate.\n");
        return 1;
    }

    printf("\nSelect data bits:\n");
    printf("1. 5 bits\n");
    printf("2. 6 bits\n");
    printf("3. 7 bits\n");
    printf("4. 8 bits\n");
    printf("5. 9 bits\n");
    printf("Choice: ");

    if (scanf("%u", &parity_choice) != 1 ||
        parity_choice < 1U || parity_choice > 5U)
    {
        printf("Invalid data-bit selection.\n");
        return 1;
    }

    config.data_bits = (uint8_t)(parity_choice + 4U);

    printf("\nSelect parity:\n");
    printf("1. None\n");
    printf("2. Even\n");
    printf("3. Odd\n");
    printf("Choice: ");

    if (scanf("%u", &parity_choice) != 1 ||
        parity_choice < 1U || parity_choice > 3U)
    {
        printf("Invalid parity selection.\n");
        return 1;
    }

    config.parity = (UARTParity)(parity_choice - 1U);
    config.stop_bits = 1U;

    printf("\nEnter noise probability (0-100%%): ");

    if (scanf("%u", &noise_probability) != 1 ||
        noise_probability > 100U)
    {
        printf("Invalid noise probability.\n");
        return 1;
    }

    if (!uart_config_is_valid(&config))
    {
        printf("Invalid UART configuration.\n");
        return 1;
    }

    printf("\n--- TRANSMISSION ---\n");

    for (i = 0U; input[i] != '\0'; i++)
    {
        uint16_t data = (uint16_t)(unsigned char)input[i];

        if (!uart_transmit(data, &config, &tx_frame))
        {
            printf("Transmission failed: data exceeds selected bit width.\n");
            return 1;
        }

        display_frame(&tx_frame, &config);

        if (!uart_channel_transmit(&tx_frame, &rx_frame))
        {
            printf("Channel transmission failed.\n");
            return 1;
        }

        if (!uart_channel_apply_noise(&rx_frame, noise_probability))
        {
            printf("Noise simulation failed.\n");
            return 1;
        }

        error = uart_receive(&rx_frame, &config, &received_char);

        if (error != UART_ERROR_NONE)
        {
            printf("\nReception error: %s\n", error_message(error));
            return 1;
        }

        received[i] = (char)received_char;
    }

    received[i] = '\0';

    printf("\n--- TRANSMISSION RESULT ---\n");
    printf("Baud rate:    %" PRIu32 "\n", config.baud_rate);
    printf("Data bits:    %u\n", config.data_bits);

    printf("Parity:       %s\n",
           config.parity == UART_PARITY_NONE ? "None" :
           config.parity == UART_PARITY_EVEN ? "Even" : "Odd");

    printf("Stop bits:    %u\n", config.stop_bits);
    printf("Noise:        %u%%\n", noise_probability);
    printf("Transmitted:  %s\n", input);
    printf("Received:     %s\n", received);

    printf("Status:       %s\n",
           strcmp(input, received) == 0 ? "SUCCESS" : "FAILED");

    return 0;
}