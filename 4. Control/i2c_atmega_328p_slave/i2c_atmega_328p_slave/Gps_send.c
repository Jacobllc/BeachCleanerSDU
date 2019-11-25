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


char status =255;
int dir = 10;
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
	char data;
	
	if (return_checksum==1)
	{
		char checksum;
		
		checksum = cal_checksum(dir, 16);
		set_data(checksum);
		return_checksum=0;
	}
	else
	{
		data= dir>> 8*bytes;
		set_data(data);	
		bytes++;
		if (bytes==2)
		bytes=0;
	
		
	}
}

void Gps_send_Distance(void)
{
	char data;
	
	if (return_checksum==1)
	{
		char checksum;
		
		checksum = cal_checksum(dist, 32);
		set_data(checksum);
		return_checksum=0;
	}
	else
	{
		data= dist>> 8*bytes;
		set_data(data);
		bytes++;
		if (bytes==4)
		bytes=0;
		
	
	}
}