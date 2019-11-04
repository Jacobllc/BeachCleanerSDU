/*
 * gps_func.h
 *
 * Created: 07-10-2019 21:47:10
 *  Author: Magnus
 */ 

#ifndef GPS_FUNC_H_
#define GPS_FUNC_H_
#include <math.h>

//Own definitions
#define PI 3.14159265358979323846

//Structures definition
typedef struct{
	float LAT;
	int LAT_int;
	float LON;
	int LON_int;
}coor_t;

//Function declarations
float dist_to_wp(coor_t pos, coor_t wp);
float angle_to_wp(coor_t pos, coor_t wp);
float rad_to_deg(float rad);
float deg_to_rad(float deg);

#endif /* GPS_FUNC_H_ */