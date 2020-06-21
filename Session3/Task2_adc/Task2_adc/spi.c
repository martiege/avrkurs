#include <avr/io.h>

#include "spi.h"

#define MOSI_bm (1 << 4)
#define SCK_bm (1 << 6)
#define SPI_PORT PORTA 

#define CS_bm (1 << 6)
#define CS_PORT PORTC 

#define SPI_IF_ENABLE_bp 0

void spi_init()
{
	SPI_PORT.DIRSET = (MOSI_bm) | (SCK_bm);
	CS_PORT.DIRSET = (CS_bm);

	CS_PORT.OUTSET = (CS_bm);
	SPI0.CTRLA |= (SPI_ENABLE_bm) | (SPI_MASTER_bm); 
	SPI0.CTRLB |= (SPI_SSD_bm);
	SPI0.INTCTRL |= (1 << SPI_IF_ENABLE_bp);
}

void spi_transmit(char cData)
{
	CS_PORT.OUTCLR = (CS_bm);
	SPI0.DATA = cData; 
	while (!(SPI0.INTFLAGS & (SPI_IF_bm)));
	SPI0.DATA; 

	CS_PORT.OUTSET = CS_bm; 
}