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

//						Global Variables
volatile int tick = 0;
char mode = 1;

int main(void)
{

	uart_init();   // open the communication to the microcontroller
	io_redirect(); // redirect input and output to the uart	
	IO_init();	   //
	TimersInit();
	Enable_ADC();	
	sei(); // Enable interrupts
		
    while(1) 
    {	
		
		while(mode == 1){
			// printf("Safe to run!  \n");	
			if(adc_result > Max_Curren)
			{
			// printf("Shit should stop!\n");
			//mode = 0;		
			}

			
			StartDrive();
			Sorting(sortState);

											

						
				adc_result = 0.19 * adc_read(ADC_Channel) - 25; // Untested !!!!!!!!!!!!!!!!!!!!!
				_delay_ms(1000);
			
			
		}
		
		while(mode == 0){
			// printf("Not Safe to run!  \n");	
			
			StopDrive();
			
			
				
		}
		

		
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
		
ISR(TIMER2_OVF_vect){
	tick++;						// 80  micro
	if(tick >= 2);				// 160 micro seconds
	tick = 0;
	TimerCounter++;
	
}
