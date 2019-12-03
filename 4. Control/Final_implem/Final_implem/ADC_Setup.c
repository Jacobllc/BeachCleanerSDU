/*/*
 * ADC_Setup.c
 *
 * Created: 10/24/2019 4:47:34 PM
 *  Author: Red
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "ADC_Setup.h"

void Enable_ADC(void)
{	
	ADMUX = (1<<REFS0); // Select Vref = AVcc
	ADCSRA = (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);	
}

uint16_t adc_read(uint8_t adc_channel){
	//printf("Reset ADC\n");
	ADMUX &= 0xf0; // clear any prev used channael but keep internal reference
	//printf("Set Channel\n");
	ADMUX |= adc_channel; // set the desired channel
	//printf("Start Conversion\n");
	ADCSRA |= (1<<ADSC);
	// now wait for the convresion
	
	ADC_Channel++;       //go trough the channels
	if(ADC_Channel >3)
	ADC_Channel = 0;   // start over everytime is called

	
	while( (ADCSRA & (1<<ADSC)));	
	// now we have result so return it to the calling function
	return ADC;
}

void Calculate_ADC(void)
{
		adc_result = adc_read(ADC_Channel);
		
		if (adc_result==0)
		{
			adcc1=0;
		}
		else
		{
			adcv1= (adc_result/1023)*5000;
			adcc1 = ((adcv1-2500)/100);
			mes [ADC_Channel] = adcc1;
		}
		
		printf("Channel: %d \t ADC value: %.1f \t Result:  %d \n",ADMUX, adc_result, mes[ADC_Channel]);
}