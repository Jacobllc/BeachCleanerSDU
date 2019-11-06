#include <atmel_start.h>
#include "NMEA_DECODER.h"

//char msg1[80] = "$GPGGA,133800.000,5454.7212,N,00946.8262,E,2,06,1.58,28.1,M,44.6,M,0000,0000*52";
char msg1[85]   = "$GNGGA,144204.00,5454.71942,N,00946.83221,E,1,12,0.94,21.1,M,44.1,M,,*70";


int main(void)
{
	atmel_start_init();
	struct DATA NMEA1;	//Create new instance of Data.

	if(GPS_Decode(msg1, &NMEA1))	//Take message as char array and reference to data struct. Returns true if checksum is okay.
	{
		printf("Lat_Degree:\t %d \t ", NMEA1.LAT_Degree);
		printf("Lat_Min:\t %d \t", NMEA1.LAT_Min);
		printf("Lat_Dec:\t %lu \t", NMEA1.LAT);
		printf("%c\t\n", NMEA1.LATdir);
		
		printf("Lon_Degree:\t %d \t ", NMEA1.LON_Degree);
		printf("Lon_Min:\t %d \t", NMEA1.LON_Min);
		printf("Lon_Dec:\t %lu \t", NMEA1.LON);
		printf("%c\n", NMEA1.LONdir);
		
		printf("Lat: %lf\t Lon: %lf\n", NMEA1.LAT_Float, NMEA1.LON_Float);
		printf("LON_Final: %lu\n", NMEA1.LON_FINAL);
		//printf("LAT_Final: %lu\n", NMEA1.LAT_FINAL);
		
		
		printf("Quality: %d\n", NMEA1.quality);
		printf("Age: %d\n", NMEA1.ageOfCorrection);
		
		
	}
	else
	{
		printf("NoGo!");
	}
}
