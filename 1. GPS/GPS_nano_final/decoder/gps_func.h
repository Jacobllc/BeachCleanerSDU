/*
 * gps_func.h
 *
 * Created: 07-10-2019 21:47:10
 *  Author: Magnus
 */ 

#ifndef GPS_FUNC_H_
#define GPS_FUNC_H_
#include <math.h>
#include "NMEA_DECODER.h"

//Own definitions
#define PI 3.14159265358979323846
#define m_pr_deg_lat 1111329.0;


//Structures definition
typedef struct coor_t{
	float LAT;
	uint32_t LAT_int;
	float LON;
	uint32_t LON_int;
}coor_t;

//variables definition 
float m_pr_deg_lon; 


//Function declarations
void dist_to_wp(struct DATA *GPS_Data, coor_t wp);
void bearing_to_wp(struct DATA *GPS_Data, coor_t WP);
float rad_to_deg(float rad);
float deg_to_rad(float deg);
void Transmit_dist_bearing_i2C(struct DATA *GPS_Data); 

#endif /* GPS_FUNC_H_ */