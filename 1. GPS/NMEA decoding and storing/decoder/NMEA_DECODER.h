#ifndef NMEA_DECODER_H_
#define NMEA_DECODER_H_

#include <stdio.h>
#include <string.h>

#define GPGGA 1
#define GPVTG 2

typedef struct DATA
{	
	//From GGA		0		1			2		3		4	  5  6	7	  8	  9	 10	  11 12	13	14   15 
	// 			   $--GGA, hhmmss.ss, llll.lll, a, yyyyy.yyy, a, x, uu, v.v, w.w, M, x.x, M, , zzzz* hh<CR><LF> 
	uint8_t LAT_Degree;					  //, llll.lll, 
	uint8_t LAT_Min;
	uint32_t LAT;
	float LAT_Float;
	uint32_t LAT_FINAL;
	char LATdir;				  //		  , a, 
	
	uint8_t LON_Degree;					  //			 , yyyyy.yyy, 
	uint8_t LON_Min;
	uint32_t LON;
	float LON_Float;
	uint32_t LON_FINAL;
	char LONdir;				  //						, a,
	 
	uint8_t quality;			  //						   , x, 
	uint8_t ageOfCorrection;	  //											   , x.x, 
	
/*
	GPS Quality indicator :
	0 : Fix not valid
	1 : GPS fix
	2 : Differential GPS fix, OmniSTAR VBS
	4 : Real - Time Kinematic, fixed integers
	5 : Real - Time Kinematic, float integers, OmniSTAR XP / HP or Location RTK
*/
	
	//From VTG
	//				$--VTG,x.x,T,y.y,M,u.u,N,v.v,K,m*hh<CR><LF>
	float TrueDir;	//	  ,x.x, 
	float Speed;	//						,v.v,
	float dist_wp;
	float bearing_wp;
	
}DATA;

void init(struct DATA *GPS_Data);
int GPS_Decode(char* msg, struct DATA *GPS_Data);
uint8_t MessageType(char* msg);

#endif /* NMEA_DECODER_H_ */