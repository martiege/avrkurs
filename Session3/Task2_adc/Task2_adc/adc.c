/*
 * adc.c
 *
 * Created: 13.02.2017 02:04:10
 *  Author: Petter
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define ADC_RESSEL 2
#define ADC_ENABLE 0

#define ADC_REFSEL_BIT  4
#define ADC_REFSEL_MASK 0x1

#define ADC_MUXPOS_BIT  0
#define ADC_MUXPOS_MASK 0x1

#define ADC_STCONV_BIT 0
#define ADC_RESRDY_BIT 0

void adc_init(){

	//This function sets up the required registers to initialize the ADC

	/*
		Not as much help this time around.
		We want our ADC to run in 10 bit mode using the supply voltage (VDD) as reference.
		The rest is up to you to find out.
	*/

	// 1.  Configure the resolution by writing to the Resolution Selection bit (RESSEL) in the Control A register(ADCn.CTRLA).
	ADC0.CTRLA |= (1 << ADC_RESSEL);
	// 2.  Optional: Enable the Free-Running mode by writing a ‘1’ to the Free-Running bit (FREERUN) inADCn.CTRLA.
	// 3.  Optional: Configure the number of samples to be accumulated per conversion by writing the SampleAccumulation Number Select bits (SAMPNUM) in the Control B register (ADCn.CTRLB).
	// 4.  Configure a voltage reference by writing to the Reference Selection bit (REFSEL) in the Control C register(ADCn.CTRLC). The default is the internal voltage reference of the device (VREF, as configured there).
	ADC0.CTRLC |= (ADC_REFSEL_MASK << ADC_REFSEL_BIT);
	// 5.  Configure the CLK_ADC by writing to the Prescaler bit field (PRESC) in the Control C register (ADCn.CTRLC).
	// 6.  Configure an input by writing to the MUXPOS bit field in the MUXPOS register (ADCn.MUXPOS).
	PORTD.DIR &= ~(1 << 0);
	PORTD.PIN0CTRL |= (1 << 3);
	ADC0.MUXPOS |= (ADC_MUXPOS_MASK << ADC_MUXPOS_BIT);
	// 7.  Optional: Enable Start Event input by writing a ‘1’ to the Start Event Input bit (STARTEI) in the Event Controlregister (ADCn.EVCTRL). Configure the Event System accordingly.
	// 8.  Enable the ADC by writing a ‘1’ to the ENABLE bit in ADCn.CTRLA
	ADC0.CTRLA |= (1 << ADC_ENABLE);
	
}


uint16_t adc_read(uint8_t channel){
	
	//This function takes in a channel and returns the result of the ADC operation on that channel
	ADC0.MUXPOS |= (channel << ADC_MUXPOS_BIT);
	_delay_ms(10);

	//Keep in mind an ADC operation takes a little time
	ADC0.COMMAND |= (1 << ADC_STCONV_BIT);
	_delay_ms(10);

	while (!(ADC0.INTFLAGS & (1 << ADC_RESRDY_BIT)));
	_delay_ms(10);

	uint16_t result = (ADC0.RESL << 0) | (ADC0.RESH << 8);
	return result; 
}
