
#include "NMEA_DECODER.h"
#include "gps_func.h"
#include "GPS.h"
#include "Gps_send.h"
#include "i2c_atmega_328p_slave.h"


//char msg1[80] = "$GPGGA,133800.000,5454.7212,N,00946.8262,E,2,06,1.58,28.1,M,44.6,M,0000,0000*52";
//char msg1[85]   = "$GNGGA,144204.00,5454.71942,N,00946.83221,E,1,12,0.94,21.1,M,44.1,M,,*70";
 //   = "$GNGGA,144204.00,5454.28070,N,00947.13640,E,1,12,0.94,21.1,M,44.1,M,,*70";  //(dist 81.72m      angle: 99.31)

#define address 0x40



int main(void)
{	
	DDRC |=(1<<PORTC0); //Setting port C0 as an output 
	i2c_init(address);  //init i2c transmiission 
	GPS_init();         //init GPS decoder
	
//while(1){	
	//Defining waypoint and NMEA, message 
	coor_t WP  = {54.90, 904558, 9.78, 786864};
	
	char msg[85];  //GPGAA message from module 
	DATA NMEA1;    //struct containing relevant data; LAT LON etc. 
	
while(1){	
			init_GPSDATA(&NMEA1); //to expose NMEA1 to GPS_send.h 
		
			//Getting GPGAA from complete data pakage  
			while(!get_gps_message(msg)); 
			//printing_data(); //Printng message 
	
			//Decoding 
			if(GPS_Decode(msg, &NMEA1))	//Take message as char array and reference to data struct. Returns true if checksum is okay.
			{
				dist_to_wp(&NMEA1, WP);  //Calculating dist from pos and WP 
				bearing_to_wp(&NMEA1, WP); //Calculating bearing from pos and WP 
				Transmit_dist_bearing_i2C(&NMEA1); //Transmitting via I2C 
			}
		
		/*
		//converting back to float 
		float Bearing_retrieve; 
		Bearing_retrieve = ((float)bearing_send/32767)*360.0;
		printf(" BEARING RETRIEVE: %f", Bearing_retrieve); 
		*/
		
	}	
}
