/*
 * master.h
 *
 * Created: 11/11/2019 3:27:02 PM
 *
 *  Author: Hörður Hermannsson
 */ 

#ifndef MASTER_H_
#define MASTER_H_
#define GPS_address 0x40
#define Sensor_address 0x41
#define Motor_address 0x40


/////////////////// GPS Commands/////////////////////////////////
#define data_check 0x00
#define Device_status 0x01
#define Direction 0x02
#define Distance 0x03

/////////////////// GPS Commands/////////////////////////////////


/////////////////////////////////////////////////////////////////





int cal_checksum(int value, char length);


char update_gps_data (void);
void update_sensor_data (void);
void update_battery_data (void);
void update_motor_data (void);


void print_gps_data (void);
void print_sensor_data (void);		
void print_battery_data (void);
void print_motor_data (void);
		
			
		






#endif /* MASTER_H_ */