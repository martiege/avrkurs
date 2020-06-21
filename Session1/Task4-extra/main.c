/*
 * Task4.c
 *
 * Created: 11.02.2017 23:56:53
 * Author : Petter
 */ 

/*
* This time you'll have to do all the setup and coding yourself. 
* You are going connect the "OLED1 Xplained Pro" extension card to the ATtiny4809 kit, 
* and make the LEDs and buttons work on the extension card.
*/

/*
* Connect the OLED1 extension board to EXT1 on the ATmega board.
* Set the proper ports and pins for the LEDs and the buttons on the OLED1, don't enable the LED0 and SW0 on the ATmega
* Checkout the datasheet for the OLED1 extension card to see which pins the different LEDs/buttons are connected to
* Checkout the datasheet for the ATmega to see which ports and pins on the microcontroller that corresponds to those pins from EXT1
* Remember: The ports on the ATmega can be different for the LEDs/buttons located on the same extension card (EXT1).
*/

// F_CPU
/* Define F_CPU here */
#define F_CPU 3333333UL //3.33... MHz

// System headers
/* Define system headers here */
#include <avr/io.h>
#include <util/delay.h>
#include "OLEDPINS.h"

// Enable defines
#define PULLUPEN  3
#define COUNTEREN 0

// Timer frequency divisor select
#define DIV1	0x0
#define DIV2	0x1
#define DIV4	0x2
#define DIV8	0x3
#define DIV16	0x4
#define DIV64	0x5
#define DIV256	0x6
#define DIV1024	0x7

// LEDs - OLED1 Xplained Pro
/* Define LED pins here */
#define LED1PIN  OLEDPIN7PIN
#define LED2PIN  OLEDPIN8PIN
#define LED3PIN  OLEDPIN6PIN
#define LED1PORT OLEDPIN7PORT
#define LED2PORT OLEDPIN8PORT
#define LED3PORT OLEDPIN6PORT
#define LED1CTRL OLEDPIN7CTRL
#define LED2CTRL OLEDPIN8CTRL
#define LED3CTRL OLEDPIN6CTRL

// Buttons - OLED1 Xplained Pro
/* Define button pins here */
#define BUTTON1PIN  OLEDPIN9PIN
#define BUTTON2PIN  OLEDPIN3PIN
#define BUTTON3PIN  OLEDPIN4PIN
#define BUTTON1PORT OLEDPIN9PORT
#define BUTTON2PORT OLEDPIN3PORT
#define BUTTON3PORT OLEDPIN4PORT
#define BUTTON1CTRL OLEDPIN9CTRL
#define BUTTON2CTRL OLEDPIN3CTRL
#define BUTTON3CTRL OLEDPIN4CTRL

int main(void){
	
    /* 
	* Do the following:
	* Set the LEDs as output
	* Set buttons as input
	* Enable pull-ups on the buttons 
	*/

	// LED init
	LED1PORT.DIR |= (1 << LED1PIN); 
	LED2PORT.DIR |= (1 << LED2PIN); 
	LED3PORT.DIR |= (1 << LED3PIN); 

	// Button init
	BUTTON1PORT.DIR &= ~(1 << BUTTON1PIN); 
	BUTTON2PORT.DIR &= ~(1 << BUTTON2PIN); 
	BUTTON3PORT.DIR &= ~(1 << BUTTON3PIN); 
	// Button pullup
	BUTTON1PORT.BUTTON1CTRL |= (1 << PULLUPEN);
	BUTTON2PORT.BUTTON2CTRL |= (1 << PULLUPEN);
	BUTTON3PORT.BUTTON3CTRL |= (1 << PULLUPEN);

	// TCA
	TCA0.PER = TOP; 
	TCA0.CTRLA |= (1 << COUNTEREN); 

	
    while (1){
		/*
		* Check if the different buttons are pressed, and turn on the corresponding LED if it is pressed
		*/

		// button and led 1
		if (BUTTON1PORT.IN & (1 << BUTTON1PIN)) 
		{
			LED1PORT.OUT |= (1 << LED1PIN); 
		}
		else 
		{
			LED1PORT.OUT &= ~(1 << LED1PIN); 
		}

		// button and led 2 
		if (BUTTON2PORT.IN & (1 << BUTTON2PIN)) 
		{
			LED2PORT.OUT |= (1 << LED2PIN); 
		}
		else 
		{
			LED2PORT.OUT &= ~(1 << LED2PIN); 
		}

		// button and led 3 
		if (BUTTON3PORT.IN & (1 << BUTTON3PIN)) 
		{
			LED3PORT.OUT |= (1 << LED3PIN); 
		}
		else 
		{
			LED3PORT.OUT &= ~(1 << LED3PIN); 
		}

    }
}

