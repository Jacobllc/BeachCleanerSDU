/*
 * Created: 8/01/2018 
 * Author : Magnus Nielsen-Man
 */ 

 #define F_CPU 16000000UL
 #include <stdio.h>
 #include <avr/io.h>
 #include <util/delay.h>
 #include "usart.h"   // To use Real term
 #include <math.h>
 
 #include "gps_func.h" //own lib

 int main(void) {
		uart_init(); // open comms to microcontroller (Makes real term work)
		io_redirect(); // redirect input and output to the uart (Makes real term work)
	
	//Test coorbeachdata (dist 17.4m      angle: )
	//coor_t pos = {54.90, 461800, 9.78, 632883};
	//coor_t wp  = {54.90, 461783, 9.78, 633150};
	
	//Test coor1 (dist 81.72m      angle: 99.31)
	coor_t pos = {54.90, 467800, 9.78, 560700};
	coor_t wp  = {54.90, 455800, 9.78, 686400};
	
	//Test coor2 (dist 51.0m      angle: 25.4)
	//coor_t pos = {54.90, 470700, 9.78, 538400};
	//coor_t wp  = {54.90, 512200, 9.78, 572600};
	
	//Test coor3 (dist 34.4m      angle: 225.13)
	//coor_t pos = {54.90, 496900, 9.78, 617300};
	//coor_t wp  = {54.90, 475100, 9.78, 579200};
		
	while(1)
	{
		
	//Printing your pos and WP:
		printf("\n POS: Lat: %lf  Long: %lf \n",pos.LAT, pos.LON);
		printf(" WP : Lat: %lf  Long: %lf \n ",wp.LAT, wp.LON );
	
	//Printing angle to WP
		printf("\n Angle to WP is:");
		float angle = angle_to_wp(pos,wp);
		printf("\t %lf rad   %lf deg \n",angle, rad_to_deg(angle) );
	
	//Printing dist to WP
		printf(" Dist to WP in m is:");
		float dist = dist_to_wp(pos, wp);
		printf("\t %lf m",dist);
		
		
		int i; scanf("%d",&i);
	}
}
 