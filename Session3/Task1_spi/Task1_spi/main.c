#define F_CPU 3333333UL


#include <avr/io.h>
#include <avr/delay.h>

#include "oled.h"
#include "graphics.h"
#include "spi.h"
#include "uart.h"

/*
	In this exercise you will write a driver for the SPI module. You will connect the OLED1 Xplained Pro screen to the Xplained Pro Extension header.
	and use your SPI driver to write bitmaps and text to the screen.
	A finished driver for the screen is provided (graphics.c), as well as a font for it. These build on the SPI driver.
	You can read graphics.h to see what functions you can use with the screen.
	No help beyond the function headers is provided. To start, it's recommend you: 

	a) glance over the chapter on SPI in the ATmega4809 datasheet
	b) find out what pins of the ATmega4809 the screen is connected to 
*/


int main(void)
{
	spi_init();
	oled_init();
	uart_init();

	_delay_ms(1000);
	//Here we have implemented our own multi-font vfprintf, which uses a lot of the standard printf family functionality.  If you want to know the difference, ask an assistant or go here: https://www.nongnu.org/avr-libc/user-manual/group__avr__stdio.html.
	//Look into the oled.h to see how we connect it to vfprintf.
	graphics_printf(5,"Hello Screen \n");
		
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
		
		
		
		
	//Code here

	uint64_t i = 0; 
    while (1) 
	{
		//Code also here?	 
		uart_print("main alive\n");
		// graphics_printf(5,"O\n");
		_delay_ms(1000);
	}
}
