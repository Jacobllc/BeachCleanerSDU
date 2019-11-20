/*
 * master.h
 *
 * Created: 11/11/2019 3:27:02 PM
 *
 *  Author: Hörður Hermannsson
 */ 

#ifndef MASTER_H_
#define MASTER_H_

 #define Nofix 0
 #define Running 1
 #define Gps_newdata 2
 #define Gps_failure 3
 #define Compass_failure 4



#define GPS_address 0x40
#define Sensor_address 0x41



/////////////////// GPS Commands/////////////////////////////////
#define Direction 0x01
#define Distance 0x02

/////////////////// GPS Commands/////////////////////////////////


/////////////////////////////////////////////////////////////////

 char Gps_update;
 char status;
 float ideal_heading;		


typedef struct counter
{	
	int sec;
	int ms;
}counter;


typedef struct Gps_data
{
	int direction;
	long distnace;
	char checksum;
}Gps_data;


typedef struct Motor_data
{
	char mode;
	int error;	
}Motor_data;

Gps_data Gps;
counter Gps_counter;
counter Compass_counter;

Motor_data motor;



void Gps_init(void);
void Gps_counter_to_zero(void);
void Compass_counter_to_zero(void);
void increase_counters(void);
int update_gps_data (void);
void update_compass_data (void);
void update_sensor_data (void);
void Calc_obs_heading(void);
void update_motor_data (void);


void print_gps_data (void);
void print_sensor_data (void);		
void print_battery_data (void);
void print_motor_data (void);
		
			
		






#endif /* MASTER_H_ */