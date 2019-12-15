/*
 * NMEA_DECODER.c
 *
 * Created: 31-10-2019 21:07:00
 *  Author: Jacob Caspers
 */ 

#include "NMEA_DECODER.h"
#include <stdio.h>
#include <string.h>

void init(struct DATA *GPS_Data)
{
	GPS_Data->LAT_Float=0.0;
	GPS_Data->LAT=0;
	GPS_Data->LAT_Min=0;
	GPS_Data->LAT_Degree=0;
	GPS_Data->LON_Float=0.0;
	GPS_Data->LON=0;
	GPS_Data->LON_Min=0;
	GPS_Data->LON_Degree=0;
	GPS_Data->ageOfCorrection = 0;
	GPS_Data->quality=0;
	GPS_Data->Speed=0;
	GPS_Data->bearing_true=0;
	GPS_Data->bearing_sendI2C=0; 
	GPS_Data->dist_wp=0;
	GPS_Data->dist_sendI2C=0;
	GPS_Data->bearing_wp=0;
}

uint8_t checksum(char* msg)
{
	int i = 0;
	int checksum = 0;
	int nmea_sum = 0;
	
	if(msg[0] == '$')
	{
		i++;
		while(msg[i] != '*')
		{
			checksum ^= (msg[i]-48);
			i++;
		}
		
		if(msg[i] == '*')
		{
			////////////MSB
			i++;
			nmea_sum = 16*(msg[i]-48);
				
			////////////LSB
			i++;
			
			if((msg[i]>='0') && (msg[i]<='9'))
			{
				nmea_sum += 1*(msg[i]-48);
			}
			
			if((msg[i]>='A') && (msg[i]<='F'))
			{
				nmea_sum += 1*(msg[i]-55);
			}
		}
		
		if(checksum==(nmea_sum-(2*48)))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		
	}
return 0; 
}

uint8_t MessageType(char* msg){
	if(msg[0]=='$')
	{
		char msg_type[5];
		for(int k = 0; k<5; k++)
		{
			if(msg[k+1]>='A' && msg[k+1]<='Z')	//Make sure range
			{
				msg_type[k]	= msg[k+1];
				//printf("%c", msg_type[k]);		//Print message to therminal
			}
			else
			{
				//printf("Failed message type\n");
			}
		}
		char msg_gpgga[5] = "GPGGA";
		char msg_gpvtg[5] = "GPVTG";
		char msg_gngga[5] = "GNGGA";
		
		if(strncmp(msg_type, msg_gpgga, 5) == 0)
		{
			return GPGGA;
		}
		if(strncmp(msg_type, msg_gpvtg, 5) == 0)
		{
			return GPVTG;
		}
		if(strncmp(msg_type, msg_gngga, 5) == 0)
		{
			return GPGGA;
		}
	}
	return 0; 
}

void convert(struct DATA *GPS_Data)
{
	GPS_Data->LON_Float = GPS_Data->LON_Min + (GPS_Data->LON/100000.0);
	GPS_Data->LON_FINAL = (GPS_Data->LON_Float*100000000)/60;
	
	GPS_Data->LAT_Float = GPS_Data->LAT_Min + (GPS_Data->LAT/100000.0);
	GPS_Data->LAT_FINAL = (GPS_Data->LAT_Float*100000000)/60;
}

int GPS_Decode(char* msg, struct DATA *GPS_Data)
{
	///////////////////Checksum////////////////////////
	if(checksum(msg))  //! to disable during testing 
	{
		uint8_t type = MessageType(msg);
		init(GPS_Data);
		
	switch(type)
	{
			case GPGGA:
			{
				uint8_t i=6;	//First comma after type
				uint8_t CommaCounter=0;	//Comma counter
				uint8_t age = 10;
				
				uint8_t LatCount=0;
				uint8_t LatDegree = 10;
				uint8_t LatHour = 10;
				uint32_t LatMin = 10000;
				
				uint8_t LonCount=0;
				uint8_t LonDegree = 100;
				uint8_t LonHour = 10;
				uint32_t LonMin = 10000;
								
				while(msg[i] != '*')
				{
					if(msg[i] == ',')
					{
						CommaCounter++;
						i++;
					}
					
					///////////COMMA SWITCH START!////////////////////////
					switch(CommaCounter)
					{
						case 2:		//Latitude
						{
							if((msg[i] != '.') && (msg[i] != ','))
							{
								if(LatCount<2)
								{
									GPS_Data->LAT_Degree += (msg[i]-48) * LatDegree;
									LatDegree /= 10;
								}
								if((LatCount>=2) && (LatCount<4))
								{
									GPS_Data->LAT_Min += (msg[i]-48) * LatHour;
									LatHour /= 10;
								}
								if((LatCount>=4))
								{
									GPS_Data->LAT += (msg[i]-48) * LatMin;
									LatMin /= 10;
								}
								LatCount++;
							}

						}
						//////////////////////////////////////////////////
						case 3:		//Lat sign
						{
							if(msg[i]>='A' && msg[i]<='Z')
							{
								GPS_Data->LATdir = msg[i];
							}
							break;
						}
						///////////////////////////////////////////////////
						case 4:		//Longitude
						{
							if((msg[i] != '.') && (msg[i] != ','))
							{
								if(LonCount<3)
								{
									GPS_Data->LON_Degree += (msg[i]-48) * LonDegree;
									LonDegree /= 10;
								}
								if((LonCount>=3) && (LonCount<5))
								{
									GPS_Data->LON_Min += (msg[i]-48) * LonHour;
									LonHour /= 10;
								}
								if((LonCount>=5))
								{
									GPS_Data->LON += (msg[i]-48) * LonMin;
									LonMin /= 10;
								}
								LonCount++;	
							}
						}
						//////////////////////////////////////////////////
						case 5: //Lon dir
						{
							if(msg[i]>='A' && msg[i]<='Z')
							{
								GPS_Data->LONdir = msg[i];
							}
							break;
						}
						//////////////////////////////////////////////////
						case 6: //Quality
						{
							if((msg[i]<= '5') && (msg[i] >= '0') && (msg[i]!=','))
							{
								GPS_Data->quality = msg[i] - 48;
							}
							
							break;
						}
						//////////////////////////////////////////////////
						case 13: //AGE
						{
							if((msg[i] != '.') && (msg[i] != ','))
							{
							GPS_Data->ageOfCorrection += (msg[i]-48) * age;
							age /= 10;
							}
							break;
						}
					}
					///////////COMMA SWITCH END!////////////////////////
					i++;
				}	
			}
			
			///////////////////////////END GGA////////////////////////////////
			case GPVTG:
			{
				
			}	
		}			//End switch type
		////////////////////////////////////////////////////////
		convert(GPS_Data);
		
		if(GPS_Data->quality >= 4) //if fix return 1
		return 1;
		else
		return 0;
		
		//return 1;
	}
	else
	{	//if chechsum false return 0
		return 0;
	}
}