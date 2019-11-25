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
#include "MPU_9250.h"


void GPS_init(void)
{
	DDRD &= ~(1 << DDD2);	             // PD2 set as input
	PORTD |= (1 << PORTD2);				 // turn OFF the Pull-up
	EIMSK |= (1<<INT0);
	EICRA |= (1 << ISC00)| (1 << ISC01); // set INT0 to trigger on falling edge logic change								 // turn on interrupts
	Gps_counter_to_zero();
	status=Nofix;
		
}

void increase_counters(void)
{
	Gps_counter.ms++;
	
	if (Gps_counter.ms>1000)
	{
		Gps_counter.sec++;
		Gps_counter.ms=0;
	}
	
if ((Gps_counter.sec==5)&&(status==Running))
{
	status=Gps_failure;
}
}


void Gps_counter_to_zero(void)
{
	Gps_counter.sec=0;
	Gps_counter.ms=0;
}

void Compass_counter_to_zero(void)
{
	Compass_counter.sec=0;
	Compass_counter.ms=0;
}


int update_gps_data (void)
{	
	Gps_data New_data;
	
		New_data.direction = get_data_int(Direction, GPS_address);
		
		if (New_data.direction!=-1)
		{
			Gps.direction=New_data.direction;
			New_data.distnace=get_data_long(Distance, GPS_address);
		}
		else
		{
			printf("GPS controller comm failure\n");	return -1;
		}
			
			if (New_data.distnace!=-1)
			{
				Gps.distnace=New_data.distnace;	//printf("GPS controller Update\n");	
				return 1;
			}
			else
			{
				printf("GPS controller comm failure\n");	return -1;
			}	
			
	
}


void update_compass_data (void)
 {
	 Magnometer_out();

	printf("Compass Update\n"); 
 }
 

void Calc_obs_heading(void)
{
	
	printf("Received direction %d \n",Gps.direction);
	ideal_heading = ((float)Gps.direction/32767)*360.0;
	
	motor.error=ideal_heading - Heading;
	
	if (motor.error<=0)
	{
		motor.error=motor.error+360;
	}
	
	if (motor.error>=180)
	{
		motor.error=motor.error-360;
	}
	
	
}

void update_motor_data (void)
{



	
}
	







ISR(INT0_vect)
{
	status=Gps_newdata;
}