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
 int data=0;
 int info=-100;
 int data_received =0;
 uint8_t byte=1;
 int main(void)
 {
	 DDRD = 0xFF; // I/O board PD4..7 as outputs, for LEDs
	 PORTD = 0xFF; // Enable internal pull at PC0...3 inputs
	 
	 
	 i2c_init();
	 uart_init();
	 io_redirect();
	 
	 i2c_sync();
		
	 
	
	 while (1)
	 {
		 
		
		
		printf("input a number\n");
		scanf("%d",&data);
		printf("Thanks\n");
		info = i2c_start(0x40<<1 | I2C_WRITE);		//starts i2c comm here in writing mode
		printf("value %d\n ", info);
		i2c_write(data);		//send pressed key char
		//printf("Data transmitted \n");
		i2c_stop();				//stop i2c here
		//printf("stopping i2c \n ");
		i2c_start(0x40<<1 | I2C_READ);		//here we start i2c in read mode where we request a byte
		data_received=i2c_read_ack();	//read the byte
		i2c_read_nack();				// read the neg ack
		//printf("Transmission completed \n ");
		printf("Received data = %d \n", data_received);

	 }
	 
 }




/*
		if(data>=256)
		{
			
		byte=2;
		uint8_t data_8bit[0];
		
		data_8bit[0]=(uint8_t)data;		// 8 LSB	
		data_8bit[1]=data >> 8;			// 8 MSB
		printf("Data first 8 bits %d is, data last 8 bits %d \n",data_8bit[0] , data_8bit[1]);
		
		}
	 */