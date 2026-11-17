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

## Sample Output

Example execution with 9600 baud rate, 8 data bits, no parity, and 0% noise:

```text
=== VIRTUAL UART SIMULATOR ===

Enter data: A

Enter baud rate: 9600

Select data bits:
1. 5 bits
2. 6 bits
3. 7 bits
4. 8 bits
5. 9 bits
Choice: 4

Select parity:
1. None
2. Even
3. Odd
Choice: 1

Enter noise probability (0-100%): 0

--- TRANSMISSION ---

UART FRAME:
START: 0
DATA[0]: 1
DATA[1]: 0
DATA[2]: 0
DATA[3]: 0
DATA[4]: 0
DATA[5]: 0
DATA[6]: 1
DATA[7]: 0
STOP: 1

--- TRANSMISSION RESULT ---
Baud rate:    9600
Data bits:    8
Parity:       None
Stop bits:    1
Noise:        0%
Transmitted:  A
Received:     A
Status:       SUCCESS
```


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