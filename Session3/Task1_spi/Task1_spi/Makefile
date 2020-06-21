#	This is a Makefile for AVR KURS,
#	attempting to provide support for compiling and flashing AtMega4809 from Linux (2019-03-01)
#	Author: richard.bman@gmail.com
#	Special thanks: magne.hov@gmail.com
#	
#	Guide for programming AVR AtMega4809 in Linux  
#		To compile for AVR AtMega4809 we need some utilities for AVR, install these:
#		The ones in your repos may or may not be up to date, let's save ourselves
#		the trouble and go straight to the source. 
#		1) Run 'make toolchain', which will execute install_toolchain.sh. It is always wise to 
#		   read the contents of scripts before running them. 
#		2) The chip acts as a USB storage device! Mount it to somewhere sensible 
#		     sudo mount /dev/sdx /mnt
#		   If you didn't use /mnt/, write it down below in CHIP_DIR
#		5) Done! You can now cp the Makefile to wherever the main.c file you're working on is,
#		   and run 'make'. Note that uploading to the chip requires sudo priviledges, so you
#		   you will be asked for your password when uploading


# ###
# Dependency directories and binaries
CHIP_DIR = /mnt/

DFP_DIR = /home/martin/dev/avrkurs/DFP/
AVR-GCC = /home/martin/dev/avrkurs/toolchain/avr8-gnu-toolchain-linux_x86_64/bin/avr-gcc
AVR-OBJCOPY = /home/martin/dev/avrkurs/toolchain/avr8-gnu-toolchain-linux_x86_64/bin/avr-objcopy

# ####
# Project files and flags

#Source files, add more files to SRC if needed: main.c uart.c ...
SRC = main.c graphics.c oled.c spi.c uart.c
OBJ = $(SRC:.c=.o)

#Target name
TARGET = out

#Compiler and Linker flags
MCU = atmega4809
CFLAGS = -B $(DFP_DIR)gcc/dev/atmega4809 -I $(DFP_DIR)include -mmcu=$(MCU) -Os 
LDFLAGS = -B $(DFP_DIR)gcc/dev/atmega4809 -I $(DFP_DIR)include -mmcu=$(MCU) #-Wl,-Map=$(TARGET).map

# ####
# Make rules
all: compile flash clean

compile: $(TARGET).hex

flash: compile
	sudo cp $(TARGET).hex $(CHIP_DIR) && sync $(CHIP_DIR)$(TARGET).hex

clean:
	rm -f $(OBJ) $(TARGET).{elf,hex}

toolchain:
	./install_toolchain.sh

# ####
# Compiler rules
%.hex: %.elf
	$(AVR-OBJCOPY) -O ihex -R .eeprom -R .fuse -R .lock -R .signature $< $@

%.elf: $(OBJ)
	$(AVR-GCC) $^ $(LDFLAGS) -o $@

%.o : %.c
	$(AVR-GCC) $(CFLAGS) -o $@ -c $<
