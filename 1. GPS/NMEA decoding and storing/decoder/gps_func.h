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

//Structures definition
typedef struct{
	float LAT;
	uint32_t LAT_int;
	float LON;
	uint32_t LON_int;
}coor_t;

//Function declarations
void dist_to_wp(struct DATA *GPS_Data, coor_t wp);
float angle_to_wp(coor_t pos, coor_t wp);
float rad_to_deg(float rad);
float deg_to_rad(float deg);

#endif /* GPS_FUNC_H_ */