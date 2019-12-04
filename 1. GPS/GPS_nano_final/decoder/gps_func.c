/*
 * gps_func.c
 *
 * Created: 07-10-2019 21:48:02
 *  Author: Magnus Nielsen-Man
 */ 
#include "gps_func.h"
#include "NMEA_DECODER.h"
#include <stdio.h>
#include <avr/io.h> 

//define my var 
int first_dist=0;
int first_bearing=0;


float rad_to_deg(float rad){
	float deg;
	deg = ((rad * 180.0)/PI);
	return deg;
}

float deg_to_rad(float deg){
	float rad;
	rad = ((deg * PI)/180.0);
	return rad;
}

void dist_to_wp(struct DATA *GPS_Data, coor_t WP){

	int a=  (WP.LAT_int - ( GPS_Data->LAT_FINAL ));
	int b=  (WP.LON_int - ( GPS_Data->LON_FINAL )); 
	
	//converting a b to dist in meters using formula for 1deg in m:
	if(first_dist==0){
	m_pr_deg_lon = ((111.41288*cos( deg_to_rad(WP.LAT) ) ) - (0.09350*cos( deg_to_rad(3*WP.LAT) ) ) + (0.00012*cos( deg_to_rad(5*WP.LAT) ) )  )*1000;
	first_dist++;
	}
	
	float c = a * m_pr_deg_lat;
	float d = b * m_pr_deg_lon;
	
	//finding dist between pos and wp
	float dist = (sqrt(pow(c,2) + pow(d,2)))/1000 ;
	
	GPS_Data->dist_wp = dist; 
}

void bearing_to_wp(struct DATA *GPS_Data, coor_t WP){
	
	int a=  (WP.LAT_int - ( GPS_Data->LAT_FINAL ));
	int b=  (WP.LON_int - ( GPS_Data->LON_FINAL ));
	
	//converting a b to dist in meters using formula for 1deg in m:
	if(first_bearing==0){
	m_pr_deg_lon = ((111.41288*cos(deg_to_rad(WP.LAT) ) ) - (0.09350*cos( deg_to_rad(3*WP.LAT) ) ) + (0.00012*cos( deg_to_rad(5*WP.LAT) ) )  )*1000;
	first_bearing++;
	}
	
	float c = a * m_pr_deg_lat;
	float d = b * m_pr_deg_lon;
	
	if(c==0){ c=0.000001;}; //To avoid divide by 0 error.
	if(d==0){ d=0.000001;};
	
	float angle;
	if(d>0 && c>0){ //1. quatrant
		angle = atan2(d, c);
	}
	if(d<0 && c>0){ //2. quatrant
		angle = atan2(d, c);
		angle = (angle) +(2*PI);
	}
	if(d<0 && c<0){ //3. quatrant
		angle = atan2(d, c);
		angle = (angle) + (2*PI);
	}
	if(d>0 && c<0){ //4. quatrant
		angle = atan2(d, c);
	}
	
	GPS_Data->bearing_wp = rad_to_deg(angle);
}

void Transmit_dist_bearing_i2C(struct DATA *GPS_Data)
{
		//Convert dist and bearing  
		//Sending dist to DATA struct as long int 
		long dist_send;
		dist_send = (long)((GPS_Data->dist_wp));
		GPS_Data->dist_sendI2C = dist_send; 
		
		// Sending bearing to DATA struct as int 
		int bearing_send;
		bearing_send = (int)( (GPS_Data->bearing_wp/360)*32767 );
		GPS_Data->bearing_sendI2C = bearing_send; 
}