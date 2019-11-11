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
//#define Compass_address 0x60
#define Sensor_address 0x41
#define Motor_address 0x40



#define status 0x01
#define Direction 0x02
#define Distance 0x03


int get_data( uint8_t opcode, uint8_t address);
int get_data_bytes( uint8_t opcode, uint8_t bytes, uint8_t address);







#endif /* MASTER_H_ */