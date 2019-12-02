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


int main(void)
{
	new_data = 0;
	status = 0;
	zone = 1;	
		
	uart_init();   // open the communication to the microcontroller
	io_redirect(); // redirect input and output to the uart	
	IO_init();	   //
	TimersInit();
	PWM_init();
	//Enable_ADC();
	i2c_init(I2C_ADDR);	
	sei();
	//DDRD |= (1 << DDD2);
	//PORTD &= ~(1<< PORTD2);
	//sei();
		
    while(1) 
	
	
	
    {	printf("The error is %d   and new data = %d \n",error, new_data);
		
		
		if (new_data==1)
		{
			motor_handler();
			
			new_data = 0;	
		}
		
		//Call the ADC function 	

	    
	}
	
	
	CalculatePwm(error);  
	
	printf("The error is %d   and new data = %d \n",error, new_data);
	
}
	
