

#define F_CPU 3333333UL


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED1 4 // port D
#define LED2 5 // port D

#define DIV256 0x6
#define TCA0EN 0

#define OVF 0
#define CLKSEL 1

int main(void)
{
	/*	In this exercise we will get LEDs to blink at even intervals using interrupts
		First set up the LEDs like in the previous exercise. 
		You can either copy paste from the previous exercise or start fresh.
	*/
	PORTD.DIR |= (1 << LED1); 
	PORTD.DIR |= (1 << LED2); 

	// PORTD.OUT |= (1 << LED1); 
	// PORTD.OUT |= (1 << LED2);

	// PORTD.OUT |=  (1 << LED1); 
	// PORTD.OUT &= ~(1 << LED2);

	PORTD.OUT &= ~(1 << LED1); 
	PORTD.OUT |=  (1 << LED2);
	
	/*We will be using timer A (TCA0) that will trigger an overflow interupt.
	  This is a 16 bit timer that can run in 2 modes
		-single mode as one 16-bit timer
		-dual/split mode as two 8-bit timers
	  We will be using single mode in this exercise.
	  
	  Hint because the register names can be hard to understand:
	  TCA0.SINGLE.CTRLA addresses the control A register for timer A
	  
	  First we set the prescaler to clk=clk/256 and enable the timer. 
	  This is done by setting the correct bits in the control A register.
	*/

	TCA0.SINGLE.CTRLA |= (DIV256 << CLKSEL); 
	TCA0.SINGLE.CTRLA |= (1 << TCA0EN); 

	//Next we Enable timer interrupt for overflow on TCA0. 
	TCA0.SINGLE.INTCTRL |= (1 << OVF);
	
	//Finally we have to set the max value of the timer, the top. 
	//This defines the period of the interrupt (which hints at the register's name.)
	//Note that this is a 16 bit value!
	TCA0.SINGLE.PER = 4096; 
	
	
	//To be able to react to the interrupts from the module we have to enable interrupts globally.
	//This is done in the function sei(), which is located in the already included header file <avr/interrupt.h>
	sei();
	
    while(1){
		//Do other things?
		
		//Remember to fill in the ISR at the bottom of the file, else nothing will happen!
    }
}

ISR(TCA0_OVF_vect){

	//Do something with the led(s), like toggle.
	PORTD.OUT ^= (1 << LED1); 
	PORTD.OUT ^= (1 << LED2);
	
	//Clear the interrupt flag.
	//If we do not clear the flag, we will instantly jump back into the ISR again
	TCA0.SINGLE.INTFLAGS |= (1 << OVF);
}
