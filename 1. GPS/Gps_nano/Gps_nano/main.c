/*
 * Usart_IRS_RX.c
 *
 * Created: 10/10/2019 7:16:51 PM
 * Author : Hörður Hermannsson
 */ 


#include <avr/io.h>
#include <stdio.h>
#include "usart_IRS_RX.h"
#include "GPS.h"
#include "i2c_atmega_328p_slave.h"
#include <util/delay.h>

int main(void)
{
	DDRD = 0x00; // I/O PD0-PD7 set as input
	DDRC = 0xF0; // I/O board PC0..3 as inputs, for buttons
	PORTD = 0x00; // Enable internal pull at PC0...3 inputs
	PORTC = 0x30; // Enable internal pull at PC0...3 3 inputs
	I2C_slave_init();
	usart_init();
	GPS_init();
	

	while(1)
	{		
		printing_data();
	}
}
