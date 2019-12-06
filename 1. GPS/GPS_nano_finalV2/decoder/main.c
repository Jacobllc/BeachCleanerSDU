
#include "NMEA_DECODER.h"
#include "gps_func.h"
#include "GPS.h"
#include "Gps_send.h"
#include "i2c_atmega_328p_slave.h"
#define address 0x40

int main(void)
{
	DDRC |=(1<<PORTC0); //Setting port C0 as an output
	i2c_init(address);  //init i2c transmiission
	GPS_init();         //init GPS decoder
	usart_init();       //INT USART to recieve data from c94-MP8 

	coor_t WP[5];  //Struct defined in gps_func.h 

	// Waypoint definitions
	WP[1].LAT = 54.91;
	WP[1].LON = 9.78;
	//NOTRTH
	//WP[1].LAT_int = 91221900;
	//WP[1].LON_int = 78042000;
	//SOUTH
	//WP[1].LAT_int = 91197600;
	//WP[1].LON_int = 78044600;
	//EAST
	//WP[1].LAT_int = 91211500;
	//WP[1].LON_int = 78066100;
	//WEST
	WP[1].LAT_int = 91210900;
	WP[1].LON_int = 78022600;
	
	
	int WP_NUM=1;   //Current WP number 
	char msg[85];  //GPGAA message from module
	DATA NMEA1;    //struct containing relevant data; LAT LON etc.
	
	init(&NMEA1); //INIT GPS_Data struct  
	
	while(1)
	{
		usart_init(); 
		
		init_GPSDATA(&NMEA1);							//to expose NMEA1 to GPS_send.h
		
		while(!get_gps_message(msg));
		
		//PORTC &= ~(1<<PORTC0);						//Set data_ready_flag LOW When bearing and distance is being recieved and caluculated.
		
		if(GPS_Decode(msg, &NMEA1))						//Take message as char array and reference to data struct. Returns true if checksum is okay. AND if quality <=4
		{
			dist_to_wp(&NMEA1, WP[WP_NUM]);				//Calculating dist from pos and WP
			bearing_to_wp(&NMEA1, WP[WP_NUM]);			//Calculating bearing from pos and WP
			Transmit_dist_bearing_i2C(&NMEA1);		//Transmitting via I2C
				
			atmel_start_init();
			
			printf("\ni2c - Dist: %ld \t Heading: %d       \n", NMEA1.dist_sendI2C, NMEA1.bearing_sendI2C);
			printf("Dist: %f \t Heading: %f     \n", NMEA1.dist_wp, NMEA1.bearing_wp);
			//printf("Age: %d        \n", NMEA1.ageOfCorrection);
			/*
			printf("Lat:%ld\t Lon:%ld       \n", NMEA1.LAT, NMEA1.LON);
			printf("Float: Lat:%f\t Lon:%f       \n", NMEA1.LAT_Float, NMEA1.LON_Float);
			printf("Final: Lat: %ld\t Lon: %ld        \n", NMEA1.LAT_FINAL, NMEA1.LON_FINAL);
			
			int32_t a=  (WP[1].LAT_int - ( NMEA1.LAT_FINAL ));
			int32_t b=  (WP[1].LON_int - ( NMEA1.LON_FINAL ));
			float c = a * 111132.9;
			float d = b * 64153.18;
			
			printf("DIF LAT:  %ld\t LON: %ld       \n", a,b);
			printf("DIF c:  %f\t d: %f       \n", c,d);
				
				*/		
			//PORTC |= (1<<PORTC0);						//Set data_ready_flag HIGH When bearing and distance has been send.
		}
	}	
}