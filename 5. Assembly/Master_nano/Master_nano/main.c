/*
 * i2c_atmega_328p_master.c
 *
 * Created: 16.9.2019 23:48:35
 * Author : Hörður Hermannsson
 */ 
 #define F_CPU 16000000UL  //to simulate in proteus I ahve used lower crystal freq
 #include <avr/io.h>
 #include <stdio.h>
 #include <util/delay.h>
 #include "i2c_atmega_328p_master.h"  
 #include "usart.h"
 #include "master.h"
 unsigned int data=0;
 uint8_t byte=1;
 int main(void)
 {
	 DDRD = 0xFF; // I/O board PD4..7 as outputs, for LEDs
	 PORTD = 0xFF; // Enable internal pull at PC0...3 inputs
	 
	 i2c_init();
	 i2c_timer0_init();
	 uart_init();
	 io_redirect();			
	 

		
	
	
	 while (1)
	 {	
		
			
		printf("input a number\n");
		scanf("%d",&data);
		
		data=get_data_long(data, GPS_address);
	
	
	 }
	 
 }

