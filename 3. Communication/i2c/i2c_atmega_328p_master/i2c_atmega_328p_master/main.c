/*
 * i2c_atmega_328p_master.c
 *
 * Created: 16.9.2019 23:48:35
 * Author : Hörğur Hermannsson
 */ 


 #include <avr/io.h>
 #include <stdio.h>
 #include "i2c_atmega_328p_master.h"  
 #include "usart.h"
 int data=0;
 int data_received =0;
 uint8_t byte=1;
 int main(void)
 {
	 i2c_init();
	 uart_init();
	 io_redirect();
	 
	 
	
	 while (1)
	 {
		printf("input a number\n");
		scanf("%d",&data);
		
		i2c_start(0x40<<1 | I2C_WRITE);			//starts i2c comm here in writing mode
		i2c_write(data);						//send pressed key char
		i2c_stop();								//stop i2c here
		
		i2c_start(0x40<<1 | I2C_READ);			//here we start i2c in read mode where we request a byte
		data_received=i2c_read_ack();			//read the byte
		printf("Received: %d\n", data_received);
		i2c_read_nack();						// read the neg ack
		
		i2c_stop();
		
	 }
	 
 }




/*

		*/