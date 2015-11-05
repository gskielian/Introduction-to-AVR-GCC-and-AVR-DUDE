#purpose of slower clock is to use the 1.8V setting of these attiny45V series mcu's
#I have been using this successfully with the "avr pocket programmer"
#Caveat: if at first uploading fails, try try again... (as is in the way of mcu's)

DEVICE     = atmega328p
CLOCK      = 1000000
PROGRAMMER = -F -c usbtiny
OBJECTS    = main.o
# FUSES      = -U lfuse:w:0x62:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m
# FUSES      = -U lfuse:w:0x7f:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m
FUSES        = -U lfuse:w:0x7d:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m

#basically need more slowness for slower clocks, if it it cannot recogn device, probably needs to be slower...
SLOWNESS = -B 1024 


## adding slowness in order to program for slower clocks 
AVRDUDE = avrdude $(SLOWNESS) $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) 



##### NEEDED FOR MAKE ALL (or default make)

all:	main.hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(COMPILE) -S $< -o $@
 
main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex


##### FLASH -- uploading firmware
flash:	all
	$(AVRDUDE) -U flash:w:main.hex:i


##### FUSE SETTINGS
fuse:
	$(AVRDUDE) $(FUSES)


##### COMBINED FUSE FLASH
install: fuse flash


##### CLEAN
clean:
	rm -f main.hex main.elf $(OBJECTS)


##### dumps to assembly and c++
disasm:	main.elf
	avr-objdump -d main.elf

cpp:
	$(COMPILE) -E main.c
