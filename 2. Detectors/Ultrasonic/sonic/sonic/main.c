/*
 * sonic.c
 *
 * Created: 06/11/2019 12.42.54
 * Author : chalo
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>

#include "usart.h"
#include "set_up.h"


int main(void)
{
    uart_init(); //open comms to microcontroller (Realterm)
    io_redirect();
	
	init_timers();
	deadswitch(); // the switches will be implemented with an extension of the same trigger pin
	
	int din;
	
    while (1) 
    {
		int zone; 
		zone = distance();
		
		printf(" ZONE: %d \n",zone);
		
		if (TCNT1 == 5900) // toggle pin every time you read the four sensors. XOR the pin to see it
		{
			PORTD ^=(1<<PORTD2);
		}
	}
}

