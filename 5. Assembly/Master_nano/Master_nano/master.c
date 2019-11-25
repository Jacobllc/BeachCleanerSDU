/*
 * master.c
 *
 * Created: 11/11/2019 3:26:38 PM
 *  Author: hordur Hermannsson
 */ 

#include <avr/io.h>
#include <util/twi.h>
#include "i2c_atmega_328p_master.h"
#include <stdio.h>
#include <avr/interrupt.h>
#include "master.h"




typedef struct Gps_data
{						  
	int  status;
	int direction;
	int distnace;
	char checksum;
}Gps_data;


typedef struct Compass_data
{
	char status;
	int direction;
	int distnace;
	
}Compass_data;

typedef struct Motor_data
{
	char status;
	int direction;
	int distnace;
	
}Motor_data;



Gps_data Gps;


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



char update_gps_data (void)
{	
	Gps_data New_data;
	char checksum_cal;
	
	New_data.status = get_data_8bit(Device_status, GPS_address);
	New_data.checksum = get_data_8bit(data_check, GPS_address);
	checksum_cal=cal_checksum(New_data.status, 8);
	
	

	
	if (((New_data.status==1))&&(checksum_cal==New_data.checksum))
	{

		Gps.status=New_data.status;
		printf("Status messgae was ok \n");
	    New_data.direction = get_data_int(Direction, GPS_address);
		New_data.checksum = get_data_8bit(data_check, GPS_address);
		checksum_cal=cal_checksum(New_data.direction, 16);
		
	
		if ((!(New_data.direction==-1))&&(checksum_cal==New_data.checksum))
		{
			
			Gps.direction=New_data.direction;
			printf("direction  messgae was ok \n");
			return 1;
			
		//	New_data.distnace = get_data_int(Distance, GPS_address);
		//	New_data.checksum = get_data_int(data_check, GPS_address);
		//	checksum_cal=cal_checksum(New_data.distnace, 16);
			
		//	if ((!(New_data.distnace==-1))&&(checksum_cal==New_data.checksum))
		//	{
		//		printf("distance  messgae was ok \n");
		//		Gps.distnace=New_data.distnace;
		//		return 1;
		//	}
		}
			
	}

return 0;	
}
	
void update_sensor_data (void)
{
	
}
void update_battery_data (void)
{
	
}
void update_motor_data (void)
{
	
}
	
	
	
		
void print_gps_data (void)
	{
		
		
		
	}
void print_sensor_data (void)
	{
		
	}
void print_battery_data (void)
	{
		
	}
void print_motor_data (void)
	{
		
	}

