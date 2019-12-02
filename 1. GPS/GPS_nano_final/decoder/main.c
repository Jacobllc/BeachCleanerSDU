
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
	WP[1].LAT_int = 911963;
	WP[1].LON_int = 780645;
	
	WP[2].LAT_int = 911838;
	WP[2].LON_int = 780816;
	
	WP[3].LAT_int = 911701;
	WP[3].LON_int = 780981;
	
	WP[4].LAT_int = 911290;
	WP[4].LON_int = 780456;
	
	int WP_NUM=1;   //Current WP number 
	char msg[85];  //GPGAA message from module
	DATA NMEA1;    //struct containing relevant data; LAT LON etc.
	
	init(&NMEA1); //INIT GPS_Data struct  
	
	while(1)
	{
		usart_init(); 
		
		init_GPSDATA(&NMEA1);							//to expose NMEA1 to GPS_send.h
		
		while(!get_gps_message(msg));
		
		PORTC &= ~(1<<PORTC0);							//Set data_ready_flag LOW When bearing and distance is being recieved and caluculated.
		
		if(GPS_Decode(msg, &NMEA1))						//Take message as char array and reference to data struct. Returns true if checksum is okay. AND if quality <=4
		{
			dist_to_wp(&NMEA1, WP[WP_NUM]);				//Calculating dist from pos and WP
			bearing_to_wp(&NMEA1, WP[WP_NUM]);			//Calculating bearing from pos and WP
			Transmit_dist_bearing_i2C(&NMEA1);			//Transmitting via I2C
			
			PORTC |= (1<<PORTC0);						//Set data_ready_flag HIGH When bearing and distance has been send.
		}
		
		if(NMEA1.dist_wp<1000 && NMEA1.dist_wp>10 && WP_NUM<4)
		WP_NUM++;
		
	}
	
}