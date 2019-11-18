/*
 * gps_func.c
 *
 * Created: 07-10-2019 21:48:02
 *  Author: Magnus
 */ 
#include "gps_func.h"
#include "NMEA_DECODER.h"
#include <stdio.h>


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
	float m_pr_deg_lat = 111.1329*1000;
	float m_pr_deg_lon = ((111.41288*cos( deg_to_rad(WP.LAT) ) ) - (0.09350*cos( deg_to_rad(3*WP.LAT) ) ) + (0.00012*cos( deg_to_rad(5*WP.LAT) ) )  )*1000;
	
	float c = a * m_pr_deg_lat;
	float d = b * m_pr_deg_lon;
	
	//finding dist between pos and wp
	float dist = (sqrt(pow(c,2) + pow(d,2)))/1000000 ;
	
	GPS_Data->dist_wp = dist; 
}

void bearing_to_wp(struct DATA *GPS_Data, coor_t WP){
	
	int a=  (WP.LAT_int - ( GPS_Data->LAT_FINAL ));
	int b=  (WP.LON_int - ( GPS_Data->LON_FINAL ));
	
	//converting a b to dist in meters using formula for 1deg in m:
	float m_pr_deg_lat = 111.1329*1000;
	float m_pr_deg_lon = ((111.41288*cos( deg_to_rad(WP.LAT) ) ) - (0.09350*cos( deg_to_rad(3*WP.LAT) ) ) + (0.00012*cos( deg_to_rad(5*WP.LAT) ) )  )*1000;
	
	printf("  m pr deg_lon:  %f \n",m_pr_deg_lon);
	
	float c = a * m_pr_deg_lat;
	float d = b * m_pr_deg_lon;
	
	if(c==0){ c=0.000001;}; //To avoid divide by 0 error.
	if(d==0){ d=0.000001;};
	
	float angle = atan2(d, c);
	
	if(angle<0){
		angle = angle - (PI/2);
	}
	
	GPS_Data->bearing_wp = rad_to_deg(angle);
}

