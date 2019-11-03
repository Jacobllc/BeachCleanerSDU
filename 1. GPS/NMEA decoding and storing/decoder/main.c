#include <atmel_start.h>
#include "NMEA_DECODER.h"

char msg1[80] = "$GPGGA,133800.000,5454.7212,N,00946.8262,E,2,06,1.58,28.1,M,44.6,M,0000,0000*52";


int main(void)
{
	atmel_start_init();
	
	struct DATA NMEA1;	//Create new instance of Data.

	if(GPS_Decode(msg1, &NMEA1))	//Take message as char array and reference to data struct. Returns true if checksum is okay.
	{
		printf("Lat:\t%f ", NMEA1.LAT);
		printf("%c\n", NMEA1.LATdir);
		printf("Lon:\t%f ", NMEA1.LON);
		printf("%c\n", NMEA1.LONdir);
		printf("Quality: %d\n", NMEA1.quality);
		printf("Age: %d\n", NMEA1.ageOfCorrection);
	}
	else
	{
		printf("NoGo!");
	}
}
