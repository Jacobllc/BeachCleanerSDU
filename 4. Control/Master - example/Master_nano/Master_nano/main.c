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
	 i2c_timer0_init();
	 i2c_init();
	 uart_init();
	 io_redirect();
		
		
		scan_i2c();
	   //send_data_int(1, Motor_address, 1000);
	
		 while (1)
		 {	
			  data = get_data_8bit(Motor_status, Motor_address);
			  printf(" Received status %d \n",data);
			  
			  printf(" Insert the zone to be sent\n");
			  scanf("%d",&motor.mode);
			  send_data_8bit(Motor_zone, Motor_address, motor.mode);
			  
			    printf(" Insert the error to be sent\n");
			    scanf("%d",&motor.error);
			    send_data_int(Motor_error, Motor_address, motor.error);
			  
			  _delay_ms(50);
	
			// data = get_data_8bit(Motor_status, Motor_address);
		    // printf(" Received status %d \n",data);
		   // send_data_8bit(Motor_error, Motor_address, 1);
			
			
			  
			  
			 
			  
			  
		
			
		 }
	 
	 }

