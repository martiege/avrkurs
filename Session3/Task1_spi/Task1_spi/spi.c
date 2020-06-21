/*
//
// spi.c
//


// System headers
#include <avr/io.h>
#include <stdlib.h>

// Project headers
#include "spi.h"
#include "uart.h"
#include "OLEDPINS.h"


#define SPI_SS_A_PIN  OLEDPIN15PIN
#define SPI_SS_A_PORT OLEDPIN15PORT
#define SPI_SS_A_CTRL OLEDPIN15CTRL

#define SPI_MOSI_PIN  OLEDPIN16PIN
#define SPI_MOSI_PORT OLEDPIN16PORT
#define SPI_MOSI_CTRL OLEDPIN16CTRL

#define SPI_SCK_PIN   OLEDPIN18PIN
#define SPI_SCK_PORT  OLEDPIN18PORT
#define SPI_SCK_CTRL  OLEDPIN18CTRL

#define SPI_ENABLE_BIT 0
#define SPI_MASTER_MODE_BIT 5 

#define SPI_PRESC_BIT 1
#define SPI_PRESC_MASK 0x0 

#define SPI_IF_BIT 7
#define SPI_IE_BIT 0
#define SPI_SSD_BIT 2

void spi_init()
{

	//You should probably write code here
	// 1.  Configure the SS pin in the port peripheral. 
	SPI_SS_A_PORT.DIR |= (1 << SPI_SS_A_PIN); 
	// Off, active low
	SPI_SS_A_PORT.OUT |= (1 << SPI_SS_A_PIN);
	// Configure SCK and MOSI
	SPI_MOSI_PORT.DIR |= (1 << SPI_MOSI_PIN); 
	SPI_SCK_PORT.DIR  |= (1 << SPI_SCK_PIN); 
	// 2.  Select SPI Master/Slave operation by writing the Master/Slave Select bit (MASTER) in the Control A register(SPIn.CTRLA).
	SPI0.CTRLA |= (1 << SPI_MASTER_MODE_BIT);
	// 3.  In Master mode, select the clock speed by writing the Prescaler bits (PRESC) and the Clock Double bit(CLK2X) in SPIn.CTRLA.
	SPI0.CTRLA |= (SPI_PRESC_MASK << SPI_PRESC_BIT);
	// 4.  Optional: Select the Data Transfer mode by writing to the MODE bits in the Control B register (SPIn.CTRLB).
	// 5.  Optional: Write the Data Order bit (DORD) in SPIn.CTRLA.
	// 6.  Optional: Setup Buffer mode by writing BUFEN and BUFWR bits in the Control B register (SPIn.CTRLB).
	// 7.  Optional: To disable the multi-master support in Master mode, write ‘1’ to the Slave Select Disable bit (SSD) inSPIn.CTRLB.
	SPI0.CTRLB |= (1 << SPI_SSD_BIT); 
	// 8.  Enable the SPI by writing a ‘1’ to the ENABLE bit in SPIn.CTRLA.
	SPI0.CTRLA |= (1 << SPI_ENABLE_BIT);

	SPI0.INTCTRL |= (1 << SPI_IE_BIT);
}


void spi_transmit(char cData)
{
	
	//You should probably write code here
	SPI0.DATA = cData; 

	SPI_SS_A_PORT.OUT &= ~(1 << SPI_SS_A_PIN);

	while (! (SPI0.INTFLAGS & (1 << SPI_IF_BIT)) );
	
	// char buffer[33];
	// itoa(SPI0.INTFLAGS, buffer, 2);
	// uart_print(buffer);
	// uart_print("\n");

	SPI0.DATA; 
	// itoa(SPI0.INTFLAGS, buffer, 2);
	// uart_print(buffer);
	// uart_print("\n");
	SPI_SS_A_PORT.OUT |=  (1 << SPI_SS_A_PIN);

}
*/

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