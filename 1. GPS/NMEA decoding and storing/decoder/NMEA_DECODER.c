/*
 * NMEA_DECODER.c
 *
 * Created: 31-10-2019 21:07:00
 *  Author: Jacob
 */ 

#include "NMEA_DECODER.h"
#include <stdio.h>
#include <string.h>

void init(struct DATA *GPS_Data)
{
	GPS_Data->HIGH_LAT = 0;
	GPS_Data->LOW_LAT  = 0;
	GPS_Data->HIGH_LON = 0;
	GPS_Data->LOW_LON = 0;
	GPS_Data->ageOfCorrection = 0;
	GPS_Data->quality=0;
	GPS_Data->Speed=0;
	GPS_Data->TrueDir=0;
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

int GPS_Decode(char* msg, struct DATA *GPS_Data)
{
	///////////////////Checksum////////////////////////
	if(checksum(msg))
	{
		uint8_t type = MessageType(msg);
		init(GPS_Data);
		
	switch(type)
	{
			case GPGGA:
			{
				uint8_t i=6;	//First comma after type
				uint8_t CommaCounter=0;	//Comma counter
				uint8_t DotCounter=0;
				int High_Lat_divider = 1000;	//Digit number
				int High_Lon_divider = 10000;
				int Low_Lat_divider = 10000;
				int Low_Lon_divider = 10000;
				uint8_t age = 10;
				
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
								if(DotCounter==0)
								{
									GPS_Data->HIGH_LAT += (msg[i] - 48) * High_Lat_divider;
									High_Lat_divider /= 10;
								}
								if(DotCounter==1)
								{
									GPS_Data->LOW_LAT += (msg[i]-48) * (uint32_t)Low_Lat_divider;
									Low_Lat_divider /= 10;		
								}
							}
							
							if(msg[i]=='.')
							{
								DotCounter++;
							}
							break;
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
								if(DotCounter==1)								
								{
									GPS_Data->HIGH_LON += (msg[i] - 48.0) * High_Lon_divider;
									High_Lon_divider /= 10;
								}
								if(DotCounter==2)
								{
									GPS_Data->LOW_LON += (msg[i] - 48) * (uint32_t)Low_Lon_divider;
									Low_Lon_divider /= 10;
								}
							}
							
							if(msg[i]=='.')
							{
								DotCounter++;
							}
							break;
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
						case 13:
						{
							GPS_Data->ageOfCorrection += (msg[i]-48) * age;
							age /= 10;
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
		return 1;
	}
	else
	{
		return 0;
	}
}