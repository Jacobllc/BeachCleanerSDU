/*
 * NMEA_DECODER.c
 *
 * Created: 31-10-2019 21:07:00
 *  Author: Jacob Caspers
 */ 

#ifndef NMEA_DECODER_H_
#define NMEA_DECODER_H_

#include <stdio.h>
#include <string.h>

#define GPGGA 1
#define GPVTG 2

typedef struct DATA
{	
	
	uint8_t LAT_Degree;					
	uint8_t LAT_Min;
	uint32_t LAT;
	float LAT_Float;
	uint32_t LAT_FINAL;
	char LATdir;				 
	
	uint8_t LON_Degree;				
	uint8_t LON_Min;
	uint32_t LON;
	float LON_Float;
	uint32_t LON_FINAL;
	char LONdir;				  
	 
	uint8_t quality;			
	uint8_t ageOfCorrection;	
	
	float bearing_true;	
	float Speed;		
	float dist_wp;
	float bearing_wp;
	long dist_sendI2C; 
	int bearing_sendI2C; 
	
}DATA;

void init(struct DATA *GPS_Data);
int GPS_Decode(char* msg, struct DATA *GPS_Data);
uint8_t MessageType(char* msg);

#endif /* NMEA_DECODER_H_ */