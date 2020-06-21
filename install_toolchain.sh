#!/bin/bash

# Symlinks will confuse this script. 
# If you use then, I can't save you.

# Get path to where this script is
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

TOOLCHAIN="avr8-gnu-toolchain-3.6.2.1759-linux.any.x86_64.tar.gz"
DFP="Atmel.ATmega_DFP.1.3.300.atpack"

# Check if device is mounted, and gently remind if it isn't

# Download AVR-toolchain from OV
if [ ! -d "$SCRIPT_DIR/toolchain" ]; then
	mkdir "$SCRIPT_DIR/toolchain"
fi
wget -P "$SCRIPT_DIR/toolchain/" "omegav.no/files/avrkurs/2019/$TOOLCHAIN"

# Download DFP from OV
if [ ! -d "$SCRIPT_DIR/DFP" ]; then 
	mkdir "$SCRIPT_DIR/DFP"
fi
wget -P "$SCRIPT_DIR/DFP/" "omegav.no/files/avrkurs/2019/$DFP"

# Check for AVR-toolchain and extract
if [ -f "$SCRIPT_DIR/toolchain/$TOOLCHAIN" ]; then
	# Extract toolchain
	tar -xf "$SCRIPT_DIR/toolchain/$TOOLCHAIN" -C "$SCRIPT_DIR/toolchain/"
else
	echo "Toolchain not found, make sure the name is right!"
	exit 1
fi

# Check for DFP and unzip
if [ -f "$SCRIPT_DIR/DFP/$DFP" ]; then
	# Extract DFP
	# I don't know what .zip utility YOU use, so I'll just test some
	if hash unzip 2>/dev/null; then
		unzip -d "$SCRIPT_DIR/DFP/" "$SCRIPT_DIR/DFP/$DFP" 
	elif hash 7z 2>/dev/null; then
		7z x "-o$SCRIPT_DIR/DFP/" "$SCRIPT_DIR/DFP/$DFP" 
	else
		echo "Could not find an unzip tool. I recommend 7z"
	fi
else
	echo "DFP not found, make sure the name is right!"
	exit 1
fi

# Check for Makefile
if [ ! -f "$SCRIPT_DIR/Makefile" ]; then 
	echo "No Makefile found, something is off!"
	exit 1
fi

echo "$SCRIPT_DIR"
# Automagically fix paths in Makefile
sed -i "s#^HOME_DIR\ =#HOME_DIR\ =\ $SCRIPT_DIR#" "$SCRIPT_DIR/Makefile"
sed -i "s#^DFP_DIR\ =#DFP_DIR\ =\ $SCRIPT_DIR/DFP/#" "$SCRIPT_DIR/Makefile"
sed -i "s#^AVR-GCC\ =#AVR-GCC\ =\ $SCRIPT_DIR/toolchain/avr8-gnu-toolchain-linux_x86_64/bin/avr-gcc#" "$SCRIPT_DIR/Makefile"
sed -i "s#^AVR-OBJCOPY\ =#AVR-OBJCOPY\ =\ $SCRIPT_DIR/toolchain/avr8-gnu-toolchain-linux_x86_64/bin/avr-objcopy#" "$SCRIPT_DIR/Makefile"

echo "Toolchain successfully installed!"
exit 0
