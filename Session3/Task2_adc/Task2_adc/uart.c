#define F_CPU 3333333UL
#define BAUD_9600 ((4UL*F_CPU)/9600)

#include "uart.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define TXEN   6
#define TXCIF  6
#define TXPIN  0
#define TXPORT PORTB

#define RXEN   7
#define RXCIE  7
#define RXCIF  7
#define RXPIN  1
#define RXPORT PORTB

#define NBIT   0x03
#define CHSIZE 0
#define DREIF  5

void uart_init()
{
    //Set TX pin as output
	TXPORT.OUTSET |= (1 << TXPIN); 
 	//Set the TX pin high
	TXPORT.DIRSET |= (1 << TXPIN);
	//Fill in the baud rate in the 2 BAUD registers. (High and Low, you will need to do some bit shifting here)
	USART3.BAUDL = (0x00ff & BAUD_9600) >> 0; 
	USART3.BAUDH = (0xff00 & BAUD_9600) >> 8; 
	//We are going to use "async" mode, 1 stop bit and 8 bit character size. everything is by default correct...
	USART3.CTRLC |= (NBIT << CHSIZE);
	//Enable RX and TX
	USART3.CTRLB |= (1 << TXEN); 
	USART3.CTRLB |= (1 << RXEN);
	
	//Enable interrupt on incoming data
	USART3.CTRLA |= (1 << RXCIE);
}

// Function for transmitting UART data
void uart_transmit(char cData)
{
    //First we should check that there isn't already data being sent
	//	-if there is, we should probably wait for it to finish first
	while (!(USART3.STATUS & (1 << DREIF)));
	
	
	//Put our new data into the DATA register
	USART3.TXDATAL = cData; 
}

void uart_print(char* data)
{
	while (*data != '\0')
	{
		if (*data == '\n')
			uart_transmit('\r');
		uart_transmit(*data); 
		data++; 
	}
}

//Interrupt service routine for the receiver.
ISR(USART3_RXC_vect){
	
	//Read out the received data to a variable
	while (!(USART3.STATUS) & (1 << RXCIF)); 

	uint8_t data = USART3.RXDATAL; 
	USART3.STATUS &= ~(1 << RXCIF);
	//Do things with data. Perhaps send something back? Maybe not the same as recieved?

	uart_transmit(data);
}