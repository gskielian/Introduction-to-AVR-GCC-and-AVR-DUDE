## ATTINY45V

This particular ATTINY can go all the way down to 1.8V, but to do so it requires a slower clock speed (0 -> 4MHz)

To accomplish this without sacrificing pins, we use the internal 128kHz oscillator.

Makefile with fuse config for achieving this included, overview of commands below (see makefile for more in depth descriptions).

## Main Commands

- `make fuse` -- really only need to do this once, sets the fuses (in this case to utilize the 128kHz internal oscillator)
- `make all` -- compiles stuff and makes the hex file
- `make flash` uploads firmware to the device

## Modding

* changing the Device from attiny45 to something else 
* changing the device clock speed from 128kHz to something else
* decreasing the "Slowness" of the upload (right now it's very slow, 2048, else it can't program it with this slow clock speed). Omit this or decrease the number to speed upload, up.
* changing the fuses -- for this see either the datasheet of your respective chip, or use this nifty site that many of us love: http://www.engbedded.com/fusecalc/ 

## There are other commands in the Makefile too...

There are other commands, as well (my favorite being the assembly dump), I added descriptions of these in the Makefile comments.
