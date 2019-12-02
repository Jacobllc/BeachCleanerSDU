/*
 * Motor_i2c.c
 *
 * Created: 11/24/2019 4:04:32 PM
 *  Author: Red
 */ 

#include <stdio.h>
#include "i2c_atmega_328p_slave.h"
#include "Motor_i2c.h"
#include "PWM.h"


uint8_t return_checksum=0;


int new_error=0;
char new_zone=0;
int cal_checksum(int value, char length)
{
	char array[length];
	char Checksum=0;
	for (int i=0; i<length; i++)
	{   array[i] = 0;
		array[i]= (value>>((length-1)-i)) & 1;
		Checksum^=array[i];
	}
	return Checksum;
}


void i2c_service(void)
{
	switch(opcode)
	{
		case 0:
		{
			Motor_Send_Status();
			break;
		}
		
		case 1:
		{
			Motor_Send_error();
			break;
		}
		
		case 2:
		{
			Motor_Send_zone();
			break;
		}
	}
}



void Motor_Send_Status(void)
{
	if (bytes==2)
	{
		int checksum;
		
		checksum = cal_checksum(status, 8);
		set_data(checksum);
		bytes=0;
	}
	else
	{
		set_data(status);
		bytes++;
	}
}

void Motor_Send_error(void)
{
	
	char received_checksum;
	if (bytes==3)
	{
		received_checksum = data;
		int checksum = cal_checksum(new_error, 16);
		
		if (checksum==received_checksum)
		{
			error = new_error;
			new_data=1;
		}

		new_error=0;
		bytes=0;
		
	}
	else
	{
		new_error= new_error + (data << (8*(bytes-1)));
		bytes++;
	}
}

void Motor_Send_zone(void)
{
	
		char received_checksum;
		if (bytes==2)
		{
			received_checksum = data;
			int checksum = cal_checksum(new_zone, 8);
			
			if (checksum==received_checksum)
			{
				zone = new_zone;
				new_zone=0;
				
			}

			bytes=0;
			
		}
		else
		{
			new_zone = data;
			bytes++;
		}
	
}