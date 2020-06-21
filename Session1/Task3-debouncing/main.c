/*
 * Task3.c
 *
 * Created: 11.02.2017 23:45:00
 * Author : Petter
 * 
 * Updated: 05.03.2019
 * Author: AVRurd
 *
 */ 

// F_CPU
/* Define F_CPU here */
#define F_CPU 3333333UL //3.33... MHz

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

//LED
/* Define the pins for the LED here */
#define LED0 5 //On port F

//Button
/* Define the pins for the button here */
#define SW0 6 //On port F

// Pullup enable 
#define PULLUPEN 3 

int main(void)
{
	/*
	 * PORTx.DIR: set direction - 1 is output, 0 is input
	 * PORTx.OUT: set value of pins
	 * PORTx.IN: read value of pins
	 * LED: 1 LED is off, 0 LED is on
	 * SW: 1 Button is open, 0 button is pressed
	 * Set to 1: REG |= ( 1 << BIT_POS )
	 * Set to 0: REG &= ~( 1 << BIT_POS )
	 * This is called "read-modify-write". 
	 *
	 * The ATmega4809 also has special port registers that can do some of this for you.
	 * Read what PORTx.DIRSET, .DIRCLR and .DIRTGL do to the PORTx.DIR register, 
	 * And similarly what PORTx.OUTSET, .OUTCLR and .OUTTGL do to PORTx.OUT 
	 * (HINT: see chapter 15.5 of the datasheet)
	*/


	/*
	* Do the following:
	* Set LED and button correctly, and add a pull-up to the button
	*/

	PORTF.DIR      |=  (1 << LED0); 
	PORTF.DIR      &= ~(1 <<  SW0); 

	PORTF.PIN6CTRL |=  (1 << PULLUPEN);
	
	PORTF.OUT      &= ~(1 << LED0); 

    while (1) 
    {
		/* 
		* Do the following:
		* Check if button is pressed, but this time you want to toggle the light instead of turning it on/off (hint: OUTTGL or XOR)
		* Add a button-pressed-state so that you don't have to hold the button to turn on the light, but so that 
		* you instead toggle between light on/off when the button is pressed (like a light switch):
		* When the button is not pressed the light should hold it's current state.
		*/
		if ( !(PORTF.IN & (1 << SW0)) )
		{
			// PORTF.OUT ^= (1 << LED0); 
			PORTF.OUTTGL = (1 << LED0); 
			_delay_ms(100);
		}

    }
}
//Are things acting a bit unexpectedly? Google debouncing...

