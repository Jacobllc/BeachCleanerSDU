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
uint8_t return_checksum=0;
uint8_t byte=0;

char status =1;
int dir = 257;
long dist = 30000;

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


void set_opcode(uint8_t value)
{	
	if (value == 0)
	{
		return_checksum = 1;
	}
	else
	{
	opcode = value;
	}
}


void i2c_service(void)
{
	switch(opcode)
{	
	case 1: 
	{
		Gps_send_status();
		break;	
	}	
	
	case 2:
	{
		Gps_send_Direction();
		break;
	}
	
	case 3:
	 {
		 Gps_send_Distance();
		 break;
	 }
	}
}


void Gps_send_status(void)
{
	if (return_checksum==1)
	{
		int checksum;
		
	    checksum = cal_checksum(status, 8);
		set_data(checksum);		
		return_checksum=0;
	}
	else
	{	
		set_data(status);
	}
}

void Gps_send_Direction(void)
{
	if (return_checksum==1)
	{
		int checksum;
		
		checksum = cal_checksum((dir>>(8*byte)), 16);
		set_data(checksum);
		return_checksum=0;
	}
	else
	{
		set_data(dir>>(8*byte));	
		printf("byte value %d \n",bytes);
		printf("byte value %d \n",dir>>(8*byte));
	}
}

void Gps_send_Distance(void)
{
	if (return_checksum==1)
	{
		int checksum;
		
		checksum = cal_checksum(257, 16);
		set_data(checksum);
		return_checksum=0;
	}
	else
	{
		set_data(1);
	}
}