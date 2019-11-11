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
 int status = 100;
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
		 printf("Thanks\n");
		 status=i2c_start(0x10<<1 | I2C_WRITE);		//starts i2c comm here in writing mode
		 printf("start i2c %d\n", status);
		 status = 100;
		 status=i2c_write(data);						//send pressed key char
		  printf("write i2c %d\n", status);
		 i2c_stop();							//stop i2c here
			
		 i2c_start(0x10<<1 | I2C_READ);			//here we start i2c in read mode where we request a byte
		 data_received=i2c_read_ack();			//read the byte
		 i2c_read_nack();						// read the neg ack
		 i2c_stop();
		
		printf("Received %d \n", data_received);

	 }
 }


		/*
		
		printf("input an number\n");
		scanf("%d",&data);
		
	
		if(data>=256)
		{
			
		byte=2;
		uint8_t data_8bit[0];
		
		data_8bit[0]=(uint8_t)data;		// 8 LSB	
		data_8bit[1]=data >> 8;			// 8 MSB
		printf("Data first 8 bits %d is, data last 8 bits %d \n",data_8bit[0] , data_8bit[1]);
		
		}
	 }
	 
 }*/
