/*
 * Gps_send.c
 *
 * Created: 11.11.2019 22:07:40
 *  Author: User
 */ 


#include <stdio.h>
#include "i2c_atmega_328p_slave.h"
#include "Gps_send.h"

uint8_t opcode; 

void set_opcode(uint8_t value)
{
	opcode = value;
}


void i2c_service(void)
{
	switch(opcode)
{	
	case 0: 
	{
		Gps_send_status();
		break;	
	}	
	
	case 1:
	{
		Gps_send_Direction();
		break;
	}
	
	case 2:
	 {
		 Gps_send_Distance();
		 break;
	 }
	}
}

void Gps_send_status(void)
{
	set_data(10);
}
void Gps_send_Direction(void)
{
	set_data(20);
}
void Gps_send_Distance(void)
{
	set_data(30);
}