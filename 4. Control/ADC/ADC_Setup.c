/*
 * ADC_Setup.c
 *
 * Created: 10/24/2019 4:47:34 PM
 *  Author: Red
 */ 

#include <avr/io.h>


void Enable_ADC(void){
	
	ADMUX = (1<<REFS0); // Select Vref = AVcc
	ADCSRA = (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADIE)|(1<<ADEN);
	
}

uint16_t adc_read(uint8_t adc_channel){
	ADMUX &= 0xf0; // clear any prev used channael but keep internal reference
	ADMUX |= adc_channel; // set the desired channel
	ADCSRA |= (1<<ADSC);
	// now wait for the convresion
	//while( (ADCSRA & (1<<ADSC) ) );
	
	// now we have result so return it to the calling function
	return ADC;
}

/*
ADC0 MUX 0000	
ADC1 MUX 0001
ADC2 MUX 0010
ADC3 MUX 0011
ADC4 MUX 0100
ADC5 MUX 0101
ADC6 MUX 0110
ADC7 MUX 0111

	
	//EIMSK |= (1<<INT0);
	//EICRA |= (0 << ISC00)| (1 << ISC01); // set INT0 to trigger on falling edge logic change

*/