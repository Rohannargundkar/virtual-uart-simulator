# Virtual UART Simulator

A software-based UART communication simulator developed using Embedded C (C11).

The project demonstrates how UART serial communication works by simulating data transmission, a virtual communication channel, and data reception without requiring physical hardware.

## Features

- Configurable UART parameters.
- UART frame generation with start, data, parity, and stop bits.
- Data transmission using LSB-first bit ordering.
- Virtual communication channel.
- UART frame reception.
- Parity and framing error detection.
- Automated tests.

## Requirements

- Ubuntu / WSL2
- GCC
- Make

## Build

Compile the project:

```bash
make
```

## Run

Execute the simulator:

```bash
./simulator
```

Enter a data string and baud rate when prompted.

## Testing

Compile and run the automated tests:

```bash
make test
```

Expected output:

```text
All UART tests passed!
```

## Clean

Remove generated executables:

```bash
make clean
```

## Project Structure

```text
virtual-uart-simulator/
├── include/
├── src/
├── tests/
├── Makefile
├── README.md
└── .gitignore
```

## Limitations

- This is a software simulation, not a physical UART implementation.
- No hardware communication is performed.
- The simulator uses a simplified virtual communication channel.

## Language and Standard

- Language: C
- Standard: C11
- Compiler: GCC