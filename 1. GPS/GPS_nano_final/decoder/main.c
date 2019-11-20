
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
	usart_init();

	//	coor_t WP[5]  = {54.91, 911290, 9.78, 780456};
	
	coor_t WP[5];
	WP[1].LAT = 54.91;
	WP[1].LON = 9.78;
	WP[1].LAT_int = 911290;
	WP[1].LON_int = 780456;
	
	WP[2].LAT_int = 911250;
	WP[2].LON_int = 780456;
	
	WP[3].LAT_int = 911290;
	WP[3].LON_int = 780456;
	
	WP[4].LAT_int = 911290;
	WP[4].LON_int = 780456;

	int WP_NUM=1;
	char msg[85];  //GPGAA message from module
	DATA NMEA1;    //struct containing relevant data; LAT LON etc.
	
	while(1)
	{
		init_GPSDATA(&NMEA1);							//to expose NMEA1 to GPS_send.h
		
		while(!get_gps_message(msg));
		
		PORTC &= ~(1<<PORTC0);							//Set data_ready_flag LOW When bearing and distance had been send.
		
		if(GPS_Decode(msg, &NMEA1))						//Take message as char array and reference to data struct. Returns true if checksum is okay. AND if quality <=4
		{
			dist_to_wp(&NMEA1, WP[WP_NUM]);				//Calculating dist from pos and WP
			bearing_to_wp(&NMEA1, WP[WP_NUM]);			//Calculating bearing from pos and WP
			Transmit_dist_bearing_i2C(&NMEA1);			//Transmitting via I2C
			
			PORTC |= (1<<PORTC0);						//PORT C0 high
		}
		
		//if(NMEA1.dist_wp<100)
		//WP_NUM++;
	}
}