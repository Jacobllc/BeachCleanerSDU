/*
 * i2c_atmeGPS a_328p_master.c
 *
 * Created: 16.9.2019 23:48:35
 * Author : Hörður Hermannsson
 */ 
 #define F_CPU 16000000UL  

 #include <avr/io.h>
 #include <stdio.h>
 #include <util/delay.h>
 #include "i2c_atmega_328p_master.h"  
 #include "usart.h"
 #include "master.h"
 unsigned int data=0;
 
 
 int main(void)
 {
	 DDRD = 0xFF; // I/O board PD4..7 as outputs, for LEDs
	 PORTD = 0xFF; // Enable internal pull at PC0...3 inputs
	 
	 i2c_init();
	 i2c_timer0_init();
	 GPS_init();
	 uart_init();
	 io_redirect();
	 MPU9250_init();
	 AK8963_init();			
	
	
	

		 while (1)
		 {	
			 
			 switch(status)
			 {
				 
				  case Nofix:
				  {
					   printf("Waiting for Gps fix \n");
					  
					  break;
				  }
				 
				 
				 case Running:
				 {
					 update_compass_data();
					 
					 Calc_obs_heading();
					 
					 printf("Direction %.1f Distance  %li \n", ideal_heading, Gps.distnace);
					 print_heading();
					 printf("Error %d \n",motor.error);
					 
					 break;
				 }
				 
				 case Gps_newdata:
				 {
					 
					 int update=0;
					 update = update_gps_data();
					 
					 if (update==1)
					 {
						 printf("GPS controller Update\n");	
						 Gps_counter_to_zero();
					 }
										   
					status=Running;
				    break; 
			 	 }
				 
				 case Gps_failure:
			 	 {
					 printf("Gps failure! \n");	
					break;
			 	 }
				  
			     case Compass_failure:
				 {
					 printf("Compass failure! \n");	
					break;
				 }
				 
			 }
			 
		
		_delay_ms(300);
		 }
	 
	 }

