/*
 * master.c
 *
 * Created: 11/11/2019 3:26:38 PM
 *  Author: hordur Hermannsson
 */ 

#include <avr/io.h>
#include <util/twi.h>
#include "i2c_atmega_328p_master.h"
#include <stdio.h>
#include <avr/interrupt.h>
#include "master.h"



int get_data_8bit( uint8_t opcode, uint8_t address)
 {
	int info;
	int data_received;
	
	 
	 info = i2c_start(address<<1 | I2C_WRITE);		//starts i2c comm here in writing mode
	
	 if (info !=0)
	 {
		 printf("The receiver is unresponsive return value is %d \n",info);
		 i2c_stop();
		 return -1;
	 }
	
	 else
	 {
		 info = i2c_write(opcode);		//send pressed key char
		
		 if (info!=0)
		 {
			 printf("The receiver did not ack the data \n");
			 i2c_stop();
			 return -1;
		 }
		
		 else
		 {
			 printf("The receiver did ack the data \n");
		 }
	}
	 
	i2c_stop();				//stop i2c here
	 
	info = i2c_start(address<<1 | I2C_READ);		//starts i2c comm here in writing mode
	
	if (info == -1)
	 {
		 printf("The receiver sends no data \n");
		 i2c_stop();
		 return -1;
	 }
	 else
	 {
		 data_received=i2c_read_nack();	//read the byte
		 
		 if (data_received== -1)
		 {
			 printf("The receiver did not send the data \n");
			 i2c_stop();
			 return -1;
		 }
		 else
		 {
			 printf("The receiver data %d\n",data_received);
			 i2c_stop();
			 return data_received; 
		 }
	 }
	 
	
	 
	 
	 
	 
	 
 }

int get_data_int( uint8_t opcode, uint8_t address)
{
	
	char info, bytes =2;
    int result=0;
	uint8_t data_received[bytes];
	
	info = i2c_start(address<<1 | I2C_WRITE);		//starts i2c comm here in writing mode
	
	if (info !=0)
	{
		printf("The receiver is unresponsive return value is %d \n",info);
		return -1;
	}
	
	else
	{
		info = i2c_write(opcode);		//send pressed key char
		
		if (info!=0)
		{
			printf("The receiver did not ack the data \n");
			return -1;
		}
		
		else
		{
			printf("The receiver did ack the data \n");
		}
	}
	
	i2c_stop();				//stop i2c here
	
	info = i2c_start(address<<1 | I2C_READ);		//starts i2c comm here in writing mode
	
	if (info == -1)
	{
		printf("The receiver sends no data \n");
		return -1;
	}
	else
	{
		
		for (int i=0; i<(bytes-1); i++)
		{
			data_received[i]=i2c_read_ack();
			printf("data %d \n",data_received[i]);
			if (data_received[i]== -1)
			{
				printf("The receiver did not send the data \n");
				return -1;
			}
		}
		
		data_received[bytes-1]=i2c_read_nack();	//read the byte
		printf("data %d \n",data_received[bytes-1]);
		if (data_received[bytes-1]== -1)
		{
			printf("The receiver did not send the data \n");
			return -1;
		}
		;
		for (int i=0; i<bytes; i++)
		{
			result=result+(data_received[i] << 8*i);	
		}
		
		i2c_stop();		
		printf("stopping i2c \n ");
		printf("Result=%d\n",result);
		return result;
			
	}
}

long get_data_long( uint8_t opcode, uint8_t address)
{
	
	char info, bytes =4;
	long result=0;
	long data_received[bytes];
	
	info = i2c_start(address<<1 | I2C_WRITE);		//starts i2c comm here in writing mode
	
	if (info !=0)
	{
		printf("The receiver is unresponsive return value is %d \n",info);
		return -1;
	}
	
	else
	{
		info = i2c_write(opcode);		//send pressed key char
		
		if (info!=0)
		{
			printf("The receiver did not ack the data \n");
			return -1;
		}
		
		else
		{
			printf("The receiver did ack the data \n");
		}
	}
	
	i2c_stop();				//stop i2c here
	
	info = i2c_start(address<<1 | I2C_READ);		//starts i2c comm here in writing mode
	
	if (info == -1)
	{
		printf("The receiver sends no data \n");
		return -1;
	}
	else
	{
		
		for (int i=0; i<(bytes-1); i++)
		{
			data_received[i]=i2c_read_ack();
			printf("data %ld \n",data_received[i]);
			if (data_received[i]== -1)
			{
				printf("The receiver did not send the data \n");
				return -1;
			}
		}
		
		data_received[bytes-1]=i2c_read_nack();	//read the byte
		printf("data %ld \n",data_received[bytes-1]);
		if (data_received[bytes-1]== -1)
		{
			printf("The receiver did not send the data \n");
			return -1;
		}
		
		
	
		
		for (int i=0; i<bytes; i++)
		{
			result=result+(data_received[i] << 8*i);
		}
		
		i2c_stop();
		printf("stopping i2c \n ");
		printf("Result=%ld \n",result);
		return result;
		
	}
	
}






void update_gps_data (void)
{
	
	
		
}
void update_sensor_data (void)
{
	
}
void update_battery_data (void)
{
	
}
void update_motor_data (void)
{
	
}
	
	
	
		
void print_gps_data (void)
	{
		
		
		
	}
void print_sensor_data (void)
	{
		
	}
void print_battery_data (void)
	{
		
	}
void print_motor_data (void)
	{
		
	}

