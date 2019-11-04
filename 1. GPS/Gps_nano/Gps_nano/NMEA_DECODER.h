/*
 * NMEA_DECODER.h
 *
 * Created: 11/4/2019 9:50:19 AM
 *  Author: Jacob
 */ 


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
	float LAT;					  //, llll.lll, 
	char LATdir;				  //		  , a, 
	float LON;					  //			 , yyyyy.yyy, 
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
	
}DATA;



void init(struct DATA *GPS_Data);
int GPS_Decode(char* msg, struct DATA *GPS_Data);
uint8_t MessageType(char* msg);



#endif /* NMEA_DECODER_H_ */