# Virtual UART Simulator

A software-based UART communication simulator developed using Embedded C (C11).

The project demonstrates how UART serial communication works by simulating data transmission, a virtual communication channel, and data reception without requiring physical hardware.

## Features

- Configurable baud rate.
- Configurable data width (5–9 bits).
- Configurable parity (None, Even, Odd).
- Support for one or two stop bits.
- UART frame generation with start, data, parity, and stop bits.
- Data transmission using LSB-first bit ordering.
- Virtual communication channel.
- Configurable virtual-channel noise injection.
- UART frame reception.
- Start-bit, parity, and framing error detection.
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

The project includes automated tests covering the following functionality:

- **UART configuration validation**
  - Valid and invalid baud rates.
  - Supported and unsupported data widths.
  - Valid and invalid parity settings.
  - Valid and invalid stop-bit settings.

- **Data transmission and reception**
  - All supported data widths (5–9 bits).
  - Successful transmission and reception.
  - One and two stop-bit configurations.
  - All parity modes (None, Even, Odd).

- **Error detection**
  - Parity errors.
  - Framing errors.
  - Invalid start bits.
  - Invalid bit values in received frames.

- **Virtual communication channel**
  - Frame transmission.
  - Manual bit corruption.
  - Noise injection at 0% and 100%.
  - Rejection of invalid noise probability.

### Run Tests

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
- The command-line interface currently uses one stop bit by default.

## Language and Standard

- Language: C
- Standard: C11
- Compiler: GCC