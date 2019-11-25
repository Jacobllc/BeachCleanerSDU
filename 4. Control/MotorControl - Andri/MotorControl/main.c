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
#include "i2c_atmega_328p_slave.h"
#include "Motor_i2c.h"
//						Global Variables
char status = 10;

int main(void)
{
	
	uart_init();   // open the communication to the microcontroller
	io_redirect(); // redirect input and output to the uart	
	//IO_init();	   //
	TimersInit();
	//Enable_ADC();
	//i2c_init(I2C_ADDR);	
	//sei();
	DDRD |= (1 << DDD2);
	PORTD &= ~(1<< PORTD2);
	
	
	sei();
		
    while(1) 
    {	
		
		
	//	Toggle(pd2);
		
		_delay_us(100);
	//	while(status == 10){
			
			//printf("Error %d and zone %d\n",error,zone);
			//CalculatePwm(error, zone);	
			//StartDrive();
			//Sorting(sortState);
			

			//adc_result = adc_read(ADC_Channel);
			
			
			// printf("Safe to run!  \n");	
			/*if(adc_result > Max_Curren)
			{
			// printf("Shit should stop!\n");
			//mode = 0;		
			}
			*/


											

			/*			
				adc_result = 0.19 * adc_read(ADC_Channel) - 25; // Untested !!!!!!!!!!!!!!!!!!!!!
			*/

			
		//}
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 							
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 

	//	while(status == 20){
			// printf("Not Safe to run!  \n");	
		//	StopDrive();
			
			
				
	//	}
		

		
	}
}

