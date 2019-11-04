/*
 * gps_func.c
 *
 * Created: 07-10-2019 21:48:02
 *  Author: Magnus
 */ 
#include "gps_func.h"
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

float dist_to_wp(coor_t pos, coor_t wp){

	float a=  (wp.LAT_int - pos.LAT_int);
	float b=  (wp.LON_int - pos.LON_int);
	
	//converting a b to dist in meters using formula for 1deg in m:
	float m_pr_deg_lat = 111.1329*1000;
	float m_pr_deg_lon = ((111.41288*cos( deg_to_rad(pos.LAT) ) ) - (0.09350*cos( deg_to_rad(3*pos.LAT) ) ) + (0.00012*cos( deg_to_rad(5*pos.LAT) ) )  )*1000;
	
	a = a * m_pr_deg_lat;
	b = b * m_pr_deg_lon;
	
	//finding dist between pos and wp
	float dist = (sqrt(pow(a,2) + pow(b,2)))/100000000 ;
	
	return dist;
}


float angle_to_wp(coor_t pos, coor_t wp){
	
	float a=  (wp.LAT_int - pos.LAT_int);
	float b=  (wp.LON_int - pos.LON_int);
	printf("HELLO a: %f",a);
	printf("  b:  %f",b);
	
	//converting a b to dist in meters using formula for 1deg in m:
	float m_pr_deg_lat = 111.1329*1000;
	float m_pr_deg_lon = ((111.41288*cos( deg_to_rad(pos.LAT) ) ) - (0.09350*cos( deg_to_rad(3*pos.LAT) ) ) + (0.00012*cos( deg_to_rad(5*pos.LAT) ) )  )*1000;
	
	a = a * m_pr_deg_lat;
	b = b * m_pr_deg_lon;
	
	if(a==0){ a=0.000001;}; //To avoid divide by 0 error.
	if(b==0){ b=0.000001;};
	
	float angle = atan2(b, a);
	
	if(angle<0){
		angle = angle - (PI/2);
	}
	
	return angle;
}
