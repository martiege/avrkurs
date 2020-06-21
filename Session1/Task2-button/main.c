/*
 * Task2.c
 *
 * Created: 11.02.2017 23:39:47
 * Author : Petter
 *
 * Updated: 05.03.2019
 * Author: AVRurd
 */ 

#define F_CPU 3333333UL //3.33... MHz

/*
* System headers bellow
*/

#include <avr/io.h>
#include <util/delay.h>

/*
* Check out the ATmega4809 datasheet to find the correct ports and pins 
*/

// LED
#define LED0 5 //On port F

// Button
#define SW0 6 //On port F

// Pullup enable 
#define PULLUPEN 3 

int main(void)
{
	/*
	 * We want to send signals to the LEDs, in order to turn it off and on.
	 * We also want to be able to read the switches.
	 * This is done by setting bits in the PORTx.DIR register (in this case PORTF.DIR and PORTF.DIR)
	 * PORTx.DIR: 1 is output, 0 is input
	 * LED: 1 LED is off, 0 LED is on
	 * Button: 1 Button is open, 0 button is pressed
	 * Bit set logic:
	 * Set to 1: REG |= ( 1 << BIT_POS )
	 * Set to 0: REG &= ~( 1 << BIT_POS )
	 */

	/**
	 * In order to read from the switches, we need to give it a ground reference, via a pull-up resistor.
	 * If we don't, the switch will have a floating ground, and hence its value will be undefined.
	 * On the ATmega4809, we enable pull-up by setting the "PORT_PULLUPEN" bit in "PORTx.PINnCTRL" high.
	 * See datasheet section 15 (I/O-ports).
	 */
    
	/* 
	 * It's your time to do some stuff! Do the following:
	 * 1 - Set LED0 as output
	 * 2 - Set SW0 as input
	 * 3 - Enable pull-up on button SW0
	 */

	PORTF.DIR |= (1 << LED0); 
	PORTF.DIR &= ~(1 << SW0); 
	PORTF.PIN6CTRL |= (1 << PULLUPEN);
	
    while (1) 
    {
    	/*
		 * Here, you want to check if a button is pressed, and if yes, turn on LED0.
		 * If no, then do the opposite.
		 * Similar to setting pins with PORTx.OUT, we can read pins with PORTx.IN
		 * In order to check a pin value, mask out that particular bit. (use bitwise AND)
		 * Bit masking is done like this:
		 * (REGISTER & (1 << BIT_POS)), which selects bit BIT_POS from register.
		 * If that bit is 0, the result will be 0. If it is 1, the result will be greater than  0 (depending on bit pos).
		 */
		
		
		/* 
		* Do the following:
		* 1 - check if button SW0 is pressed
		* 2 - if so, turn LED0 on
		* 3 - if not, turn LED0 off
		*/
		if (PORTF.IN & (1 << SW0))
		{
			PORTF.OUT |= (1 << LED0); 
		}
		else 
		{
			PORTF.OUT &= ~(1 << LED0); 
		}
		
    }
}
