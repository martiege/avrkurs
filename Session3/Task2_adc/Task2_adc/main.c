

#define F_CPU 3333333UL
#define BAUD_9600 ((4UL*F_CPU)/9600)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "adc.h"
#include "graphics.h"
#include "oled.h"
#include "uart.h"
#include "spi.h"



/* In this exercise you will be writing an ADC driver. 
	You will use this to read the OV-POT KLAKK connected to the MicroBUS slot 1 on the Curiosity Nano Adapter board.
	We will display the results on the OLED screen from them previous task.
*/

int main(void)
{
		
	//Initialize everything we need here
	spi_init(); 
	oled_init();
	uart_init(); 
	adc_init(); 

	_delay_ms(5000);
	uart_print("Initialised\n");
	graphics_printf(5,"Initialised\n");
	
	while (1)
	{
		_delay_ms(1000);
		//continuously read the ADC each loop
		uint16_t volt = adc_read(1);
		char buffer[33];
		itoa(volt, buffer, 16);
		uart_print(buffer);
		uart_print("\n");
		/*
			About vfprintf: Handles formatting of your print to terminal. This includes special characters, values of variables and more.
			It takes one string and any variables you want to print.
			Some handy special characters: \n = newline (enter)(some terminals need \r also), \t = tab
			'%' marks a variable to be inserted in the string. %d = decimal, %x = hexadecimal, %f = floating point number (There are many more)
			Variables to be inserted have to be provided separated by commas, after the string in order of appearance in string.
			
			A handy thing to know with vfprintf and variables is that for example %u will print a unsigned integer, "no matter how long it is"*, while
			%4u will print a integer which is always "four" long disregarding preceding zeros, and %04u will print a 4 character long unsigned integer with preceding zeros.
			
			Make sure to read the "graphics.h" file to find out what neat functions we have laid out for you!
		*/
		
		
	}
}
