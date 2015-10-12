## Atmega 328p

Notes:
- dividing clock by 8, so `F_CPU` is 1MHz.
- fully tested

## Main Commands

- `make fuse` -- really only need to do this once, sets the fuses (in this case to utilize the 128kHz internal oscillator)
- `make all` -- compiles stuff and makes the hex file
- `make flash` uploads firmware to the device
