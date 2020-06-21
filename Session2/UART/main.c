

#define F_CPU 3333333UL
#define BAUD_9600 ((4UL*F_CPU)/9600)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*
In this exercise we will set up and use USART communication.
The embedded debugger has a virtual com port that we will use to communicate with the computer.

*/

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

void usart_init(unsigned long baud){
	
	//In this function, we want to initialize the USART.
	//Chapter 22.3 in datasheet tells us how this is done:
	//You can see on the datasheet for Curiosity Nano that USART3 connects to the usb.
	
	//Set TX pin as output
	TXPORT.OUTSET |= (1 << TXPIN); 
 	//Set the TX pin high
	TXPORT.DIRSET |= (1 << TXPIN);
	//Fill in the baud rate in the 2 BAUD registers. (High and Low, you will need to do some bit shifting here)
	USART3.BAUDL = (0x00ff & baud) >> 0; 
	USART3.BAUDH = (0xff00 & baud) >> 8; 
	//We are going to use "async" mode, 1 stop bit and 8 bit character size. everything is by default correct...
	USART3.CTRLC |= (NBIT << CHSIZE);
	//Enable RX and TX
	USART3.CTRLB |= (1 << TXEN); 
	USART3.CTRLB |= (1 << RXEN);
	
	//Enable interrupt on incoming data
	USART3.CTRLA |= (1 << RXCIE);
}

// function to transmit data
void usart_transmit(char data){
	//In this function we will send data.
	
	//First we should check that there isn't already data being sent
	//	-if there is, we should probably wait for it to finish first
	while (!(USART3.STATUS & (1 << DREIF)));
	
	
	//Put our new data into the DATA register
	USART3.TXDATAL = data; 
}

void usart_print(char* data)
{
	while (*data != '\0')
	{
		if (*data == '\n')
			usart_transmit('\r');
		usart_transmit(*data); 
		data++; 
	}
}


int main(void)
{
	//Initialize the USART with our function. 
	//We will be using a baudrate of 9600 (defined as BAUD_9600 at the top of the file)
	usart_init(BAUD_9600);
	
	sei(); //Enable global interrupt, this is important for anything here to work
	
    while (1) 
    {
		// usart_transmit('a');
		usart_print("Hello World!\n");
		_delay_ms(100); 
		//We don't really need to do anything here.
		//If you want, you can continously send something over usart. It will be a good idea to include a small delay.
		//the ISR will handle receiving. 
    }
}


//Interrupt service routine for the receiver.
ISR(USART3_RXC_vect){
	
	//Read out the received data to a variable
	while (!(USART3.STATUS) & (1 << RXCIF)); 

	uint8_t data = USART3.RXDATAL; 
	USART3.STATUS &= ~(1 << RXCIF);
	//Do things with data. Perhaps send something back? Maybe not the same as recieved?

	usart_transmit(data);
}