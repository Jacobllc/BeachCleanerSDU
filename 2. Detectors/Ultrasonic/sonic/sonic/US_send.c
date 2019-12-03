/*
 * Gps_send.c
 *
 * Created: 11.11.2019 22:07:40
 *  Author: User
 */ 

#include <stdio.h>
#include "i2c_atmega_328p_slave.h"
#include "US_send.h"
#include "set_up.h"

uint8_t opcode;


char status =1;
int dir = 0;
long dist = 30000000;


//void init_GPSDATA(struct DATA *GPS_Data_NMEA1) {NMEA1 = GPS_Data_NMEA1;};  //To acces NMEA1 from main 


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
	opcode = value;
}


void i2c_service(void)
{
	switch(opcode)
	{	
		case 5:
		{
			US_send_zone();
			break;
		}
		case 1:
		{
			US_send_dist(1);
			break;
		}
		case 2:
		{
			US_send_dist(2);
			break;
		}
		case 3:
		{
			US_send_dist(3);
			break;
		}
		case 4:
		{
			US_send_dist(4);
			break;
		}
		
	}
}


void US_send_zone(void)
{
	//char data;
	
	if (bytes==1)
	{
		char checksum;
		
		checksum = cal_checksum(zone, 8);
		set_data(checksum);
		bytes=0;
	}
	else
	{
		set_data(zone);
		bytes++;
	}
	
}

void US_send_dist(int nr)
{
	char data;
	
	if (bytes==2)
	{
		char checksum;
		
		checksum = cal_checksum(av_distance_array[nr], 16);
		set_data(checksum);
		bytes=0;
	}
	else
	{
		data= av_distance_array[nr]>> 8*bytes;
		set_data(data);
		bytes++;
	}
}



/*
void Gps_send_status(void)
{
	if (bytes==1)
	{
		char checksum;
		
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

 
void Gps_send_Distance(void)
{
	char data;
	
	if (bytes==4)
	{
		char checksum;
		checksum = cal_checksum(NMEA1->dist_sendI2C, 32);
		set_data(checksum);
		bytes=0;
	}
	else
	{
		data= NMEA1->dist_sendI2C>> 8*bytes;
		set_data(data);
		bytes++;	
	}
	
}
*/
