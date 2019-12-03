/*
 * master.h
 *
 * Created: 11/11/2019 3:27:02 PM
 *
 *  Author: H�r�ur Hermannsson
 */ 

#ifndef MASTER_H_
#define MASTER_H_

 #define Nofix 0
 #define Running 1
 #define Gps_newdata 2
 #define Gps_failure 3
 #define Compass_failure 4


/////////////////// Device addresses/////////////////////////////////
#define GPS_address 0x40
#define Motor_address 0x41
#define Dist_adress 0x42

/////////////////// GPS Commands/////////////////////////////////
#define Direction 0x01
#define Distance 0x02

/////////////////// MOTOR Commands/////////////////////////////////
#define Motor_status 0x00
#define Motor_error 0x01
#define Motor_zone 0x02
///////////////////Distance commands///////////////////////////////
#define Get_Zone 0x05
#define Get_Sensor1 0x01
#define Get_Sensor2 0x02
#define Get_Sensor3 0x03
#define Get_Sensor4 0x04


 char Gps_update;
 char status;
 float ideal_heading;
 char motor_status;
 char sensor_zone;		


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
	uint8_t mode;
	int error;	
}Motor_data;


typedef struct Dist_data
{
	uint8_t Zone;	
	uint16_t dist[4];
}Dist_data;


Gps_data Gps;
counter Gps_counter;
counter Compass_counter;

Motor_data motor;
Dist_data Dist;


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