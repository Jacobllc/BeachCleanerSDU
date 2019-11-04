/*
 * PWM_TestRig.cpp
 * Created: 9/20/2019 8:13:06 PM
 * Author : Red
 */ 
 #define F_CPU 16000000UL
 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "PWM.h"
#include "MACROS.h"
#include "usart.h"
#include "ADC_Setup.h"

volatile int Besafe = 1;

int main(void)
{

	uart_init(); // open the communication to the microcontroller
	io_redirect(); // redirect input and output to the uart
	uart_init();
	io_redirect();
	IO_init();	
	//T0_init();
	T1_init();
	//T2_init();
	
	M_Direc = 0b0000;
	M1_DutyCycle = 0;
	M2_DutyCycle = 0;
	SetDrive(M1_DutyCycle, M2_DutyCycle , M_Direc);
	Enable_ADC();

	
	sei(); // Enable interrupts
		
    while(1) 
    {	
		if(adc_result > Max_Curren)
		{
			printf("Shit should stop!\n");
		}
		
		printf("TIMER VALUE %d \n",TCNT1);

		adc_result = adc_read(ADC_Channel);
		printf("ADC value %d \n",adc_result);
		printf("Channel %x \n",ADMUX);
		_delay_ms(1000);
		
	}
}

ISR(ADC_vect){
	switch(ADMUX){
			case 0x40:
			//printf("ADC CHANNEL 0\n");
			Max_Curren = 31;
			ADC_Channel = 1;
			break;
			
			case 0x41:
			//printf("ADC CHANNEL 1\n");
			Max_Curren = 32;
			ADC_Channel = 2;
			break;
			
			case 0x42:
			//printf("ADC CHANNEL 2\n");
			Max_Curren = 33;
			ADC_Channel = 3;
			break;
			
			case 0x43:
			//printf("ADC CHANNEL 3\n");
			Max_Curren = 34;
			ADC_Channel = 0;
			break;
	default:
		printf("Broken!\n");
		break;
	}

}
	
ISR(TIMER0_OVF_vect){}
	
ISR(TIMER1_OVF_vect){}
		
ISR(TIMER2_OVF_vect){}
