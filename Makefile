CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow

INCLUDES = -Iinclude

SOURCES = src/uart_config.c \
          src/uart_tx.c \
          src/uart_channel.c \
          src/uart_rx.c

all: simulator

simulator: $(SOURCES) src/main.c
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

test: $(SOURCES) tests/test_uart.c
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o test_uart
	./test_uart

clean:
	rm -f simulator test_uart

.PHONY: all test clean