
#define F_CPU 20000000UL


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
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

#define LED1 4 // port D, connected to WO4
#define LED2 5 // port D, connected to WO5

#define TCA0EN 0 // enable TCA0
#define SPLITM 0 // enable split mode

#define WO4 5 // WO4 enable in split mode
#define WO5 6 

#define PORTMUXPORTD 0x3 // set portmux to portD

/*
    In this exercise, you will use PWM to control the brightness of LEDs.
    Once we have PWM set up, controling the brightness is super easy!
*/

int main(void)
{
	//Set up the leds and buttons. You might want to copy this from previous exercises.
	PORTD.DIR |= (1 << LED1); 
	PORTD.DIR |= (1 << LED2); 
	LED3PORT.DIR |= (1 << LED3PIN); 

	// Button init
	BUTTON1PORT.DIR &= ~(1 << BUTTON1PIN); 
	BUTTON2PORT.DIR &= ~(1 << BUTTON2PIN); 
	BUTTON3PORT.DIR &= ~(1 << BUTTON3PIN); 
	// Button pullup
	BUTTON1PORT.BUTTON1CTRL |= (1 << PULLUPEN);
	BUTTON2PORT.BUTTON2CTRL |= (1 << PULLUPEN);
	BUTTON3PORT.BUTTON3CTRL |= (1 << PULLUPEN);

	// PORTD.OUT |= (1 << LED1); 
	// PORTD.OUT |= (1 << LED2);
	
	/*We will be using timer TCA0 in Split (not Single) mode. We use Split mode to output 
          waveforms on WO4 and WO5, see Figure 19-13.
	  It is highly recommended that you read chapter 19.3.3.4 and 19.3.3.6 in the megaAVR® 0-series. 
	  There you will find a sub-chapter on the single-slope PWM we will be using.
	*/
	
	//First, enable the timer
	TCA0.SPLIT.CTRLA |= (1 << TCA0EN); 

	//Set the mode of the timer to split slope PWM 
	TCA0.SPLIT.CTRLD |= (1 << SPLITM);
	
	//We have to override the normal pin operation so the PWM is pushed directly to the pin
	//Hint: WO4 and WO5 are connected to leds. We need to override them to get the PWM out.
	//See Datasheet to ATmega4809 for pins.
	PORTMUX.TCAROUTEA = PORTMUXPORTD;

	TCA0.SPLIT.CTRLB |= (1 << WO4);
	TCA0.SPLIT.CTRLB |= (1 << WO5);
		
	/*Timer A is a 16 bit timer.
	When we use split mode, this will be split into two 8 bit timers. 
	By lowering the period, (PER) we get higher frequency at the cost of lower resolution. 
	(Since in split mode, we must use LPER(for WO0-WO2) and HPER (for WO3-WO5).
	*/
	
	//Set the period to 0xff bit. (What frequency does this give?)
	// TCA0.SPLIT.LPER = 0xff; 
	TCA0.SPLIT.HPER = 0xff; 
	// 3333333 / (0xff + 1) = 13020.83203125
	
	//We can now control the PWM duty cycle by simply writing values to the CMP0 and CMP1 registers.
	// TCA0.SPLIT.HCMP1 = 0xff; //Max brightness (Leds are inverted)
	// TCA0.SPLIT.HCMP2 = 0xff; //Min brightness (Leds are inverted)
	
	//Set Duty cycle of WO4 to 0x7f to see it twinkle.
	// TCA0.SPLIT.HCMP1 = 0x7f; 
	
	uint8_t i = 0; 
	uint8_t ledSelect = 1; 

	uint8_t led1Brightness = 0xff; 
	uint8_t led2Brightness = 0xff; 

	TCA0.SPLIT.HCMP1 = led1Brightness;
	TCA0.SPLIT.HCMP2 = led2Brightness;
	
    while(1){
		
		/*Have some fun with the leds. Examples:
		  Have them fade between max and min
		  Have them fade in a pattern (Heartbeat?) 
		  Change the brightness based on buttons

		*/
		if (!(BUTTON2PORT.IN & (1 << BUTTON2PIN)))
		{
			switch (ledSelect)
			{
			case 1:
				ledSelect = 2; 
				break;
			case 2: 
			default:
				ledSelect = 1; 
				break;
			}

			_delay_ms(10); 
		}

		if (!(BUTTON1PORT.IN & (1 << BUTTON1PIN)))
		{
			switch (ledSelect)
			{
			case 1:
				led1Brightness = (led1Brightness + 0xf) % (0x100); 
				break;
			case 2: 
				led2Brightness = (led2Brightness + 0xf) % (0x100); 
				break;
			default:
				break;
			}
			TCA0.SPLIT.HCMP1 = led1Brightness;
			TCA0.SPLIT.HCMP2 = led2Brightness;
			_delay_ms(10);
		}

		if (!(BUTTON3PORT.IN & (1 << BUTTON3PIN)))
		{
			switch (ledSelect)
			{
			case 1:
				led1Brightness = (led1Brightness - 0xf) % (0x100); 
				break;
			case 2: 
				led2Brightness = (led2Brightness - 0xf) % (0x100); 
			default:
				break;
			}
			TCA0.SPLIT.HCMP1 = led1Brightness;
			TCA0.SPLIT.HCMP2 = led2Brightness;
			_delay_ms(10);
		}

		_delay_ms(1);

		if (ledSelect == 1) 
		{
			LED3PORT.OUT |= (1 << LED3PIN); 
		}
		else if (ledSelect == 2)
		{
			LED3PORT.OUT &= ~(1 << LED3PIN); 
		}
		// TCA0.SPLIT.HCMP1 = i++ % (0x100); 
		// TCA0.SPLIT.HCMP2 = i % (0x100); 
    }
}

