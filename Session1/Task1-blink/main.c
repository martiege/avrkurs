
/*
 * Task1.c
 *
 * Created: 11.02.2017 23:37:53
 * Author : Petter
 *
 * Updated: 05.03.2017
 * Author AVRurd
*/ 


/**
 * F_CPU tells the timer what the CPU's clock frequency is, such that the timer will count correctly.
 * Note that this DOES NOT set the clock speed, it just informs the compiler. Here it affects the _delay_ms() function.
 * If this is set wrong, the chip will work as normal, but software delays will be too long (if set too low) or too short (if set too high).
 * Example: set F_CPU to 2 MHz => "#define F_CPU 2000000UL". UL = unsigned long
 * F_CPU must be defined before including headers.
 */

#define F_CPU 3333333UL //The ATmega4809 operates at 20MHz with a default scaling factor of 6: 20/6 = 3.333333MHz

/**
 * System headers bellow
 */

#include <avr/io.h>
#include <util/delay.h>

/**
 * Define helpers for pin bit positions.
 * The LED0 on the ATmega4809 Curiosity Nano is connected to pin 5 on port F.
 * You can also check the datasheet or the silk screen to find out which pins on which ports the different LEDs and buttons are connected to. For example PF5 means PORTF, pin 5.
 */

#define LED0	5	// LED 0 is connected to pin 5 on PORTF



int main(void){
	/**
	 * We want to send signals to the LED, in order to turn it on and off.
	 * In the AVR world we have the following:
	 * PORTx.DIR: 1 is output, 0 is input
 	 * LED: 1 LED is off, 0 LED is on, this is called active-low
	 * Button: 1 button is open, 0 button is pressed, this is called active-low
	 *
	 * Remember bit set logic:
	 * Set to 1:	REGISTER |= ( 1 << BIT_POS ) - using 'or' ('|') so we only change the one we want and leave the others untouched
	 * Set to 0:	REGISTER &= ~( 1 << BIT_POS ) - same thing here but using 'and' ('&') and bitwise 'not' ('~'), find paper and a logic-table, and try it out if you want to know how it works.
	 * Toogle bit:	REGISTER ^= ( 1 << BIT_POS ) - using bitwise 'xor' ('^'), toogles the bit at BIT_POS
	 */

	PORTF.DIR |= (1 << LED0); // Set LED0 as output - Using "F" in PORTx.DIR since the LED is connected to port F on the microcontroller
	
	/*
	* The usual way to run microcontrollers is using a simple infinite loop
	*/

    while (1) 
    {
		PORTF.OUT ^= (1 << LED0); // Changes the state of LED0 by XOR-ing the last state. Check the XOR-table to find out how this works. 
		//Non-compressed: PORTF.OUT = PORTF.OUT ^ (1 << LED0);
		//Can also refer to toogle register: PORTF.OUTTGL = (1 << LED0). IMPORTANT: only use equal sign here (=)
		_delay_ms(500);
    }
}
