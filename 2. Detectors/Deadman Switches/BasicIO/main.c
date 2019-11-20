/* Deadswitch.c
 * Created: 18/11/2019 
 * Author : Sophie
 */ 
 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>		// Delays
#include <avr/interrupt.h>	// Interrupts
#include <stdbool.h>
#include "i2cmaster.h"


#define BAUDRATE 19200										// Define baud rate to be 19200
#define BAUD_PRESCALER (((F_CPU / (BAUDRATE * 16UL))) - 1)	// Function prototypes
#define ADC_PIN 0											// ADC channel used: A0(PC0)

 
void init_interrupt (void);
void init_adc(void);
uint16_t adc_read(uint8_t adc_channel);

volatile int  deadswitch=0; 

int main(void)
{
	DDRD &= ~(1<<DDD2);		// PD2 as input (Deadswitch-pin)
	PORTD |= (1 << PORTD2);	// Enable internal pull at pin

	i2c_init();				// i2C
	init_adc();				// ADC 
	init_interrupt();		// interrupt initialization
	
	while(1)				
	{}
	
	return 0;
}	

ISR (TIMER2_COMPA_vect)
{
	return deadswitch;
}

void init_interrupt (void)
{
	TCCR2A |= (1 << WGM21);					// Set the Timer Mode to CTC
	OCR2A = 0x7D;							// Value you wanna count to (125 cycles per ms) -> 0.5ms
	TIMSK2 |= (1 << OCIE2A);				// Set the ISR COMPA vect
	sei();									// Enable interrupt
	TCCR2B |= (1 << CS22);					// Prescaler 64 (-> 250.000 times/s)
	PORTC |= (1 << PORTC1);					// Turn on the Pull-upy
	PCICR |= (1 << PCIE1);					// Set INT1 to trigger on ANY logic change
	PCMSK1 |= (1 << PCINT18);				// Turns on interrupt for PCINT18 (Deadswitch pin)
}

ISR(PCINT1_vect)
{
	if((PINC & (1 << PIND2)) == 1)			// Check for rising edge on deadswitch pin 
	{
		deadswitch=1;						// Set variable high
	}
}

void init_adc(void)
{
	// Select Vref = AVcc
	ADMUX = (1<<REFS0);
	// Set prescaler to 128 and turn on the ADC module
	ADCSRA = (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}

uint16_t adc_read(uint8_t adc_channel)
{
	ADMUX &= 0xf0;							// Clear any previously used channel, but keep internal reference
	ADMUX |= adc_channel;					// Set the desired channel
	ADCSRA |= (1<<ADSC);					// Start a conversion
	while ( (ADCSRA & (1<<ADSC)) );			// now wait for the conversion to complete
	return ADC;								// received result -> return it to function as uint (16bit)
}





