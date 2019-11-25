/*
 * i2c_atmega_328p_master.c
 *
 * Created: 16.9.2019 23:52:22
 *  Author: Hörður Hermannsson
 */ 

#define F_CPU 16000000UL
#define F_SCL 100000UL // SCL frequency
#define Prescaler 1
#define TWBR_val ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)

#include <util/delay.h>
#include <avr/io.h>
#include <util/twi.h>
#include "i2c_atmega_328p_master.h"
#include <stdio.h>
#include <avr/interrupt.h>
volatile int counter=0;
volatile int flag=0;


void i2c_init(void)
{
	TWBR = (uint8_t)TWBR_val;
}

int i2c_start(uint8_t address)
{

	TWCR = 0;										
	TCNT0 = 0, counter = 0, flag = 0;																			// reset TWI control register
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);									// transmit START condition
	while( !(TWCR & (1<<TWINT)) )
	{
			if (flag==1)
			{
				flag = 0;
				return -1;
			}
	}												// wait for end of transmission
	
	if((TWSR & 0xF8) != TW_START)
	{ return 1; }																// check if the start condition was successfully transmitted

	TWDR = address;																// load slave address into data register
	TWCR = (1<<TWINT) | (1<<TWEN);												// start transmission of address
	while( !(TWCR & (1<<TWINT)) );												// wait for end of transmission
	uint8_t twst = TW_STATUS & 0xF8;
	
	if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) 
	return 1;
	
	return 0;																	// check if the device has acknowledged the READ / WRITE mode
}

int i2c_write(uint8_t data)
{

	TWDR = data;																// load data into data register
	TWCR = (1<<TWINT) | (1<<TWEN);												// start transmission of data
																				// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) )
	{
		if (flag==1)
		{
			flag = 0;
			return -1;
		}
	}
	
	if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
	{ return 1; }
	
	return 0;
}

int i2c_read_ack(void)
{	
	TCNT0 = 0, counter = 0, flag = 0;
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);			// start TWI module and acknowledge data after reception
	while(!(TWCR & (1<<TWINT)))
	{
		if (flag==1)
		{
			flag = 0;
			return -1;
		}
	}
														// wait for end of transmission
	
	//PORTD^=(1<<PORTD2);
	return (int)TWDR;								// return received data from TWDR
	
	
}

int i2c_read_nack(void)
{
	
	TWCR = (1<<TWINT) | (1<<TWEN);// start receiving without acknowledging reception
	while(!(TWCR & (1<<TWINT)))
	{
		if (flag==1)
		{
			flag = 0;
			return -1;
		}
	}
	// wait for end of transmission
	
	//PORTD^=(1<<PORTD2);
	return (int)TWDR;								// return received data from TWDR
	

}

void i2c_stop(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);			// transmit STOP condition
}

void i2c_transmit_bytes(int data, uint8_t address)
{
	
	if(data>=256)
	{
		uint8_t data_8bit[0];
		data_8bit[0]=(uint8_t)data;				// 8 LSB
		data_8bit[1]=data >> 8;					// 8 MSB
		
		i2c_start(address<<1 | I2C_WRITE);		//starts i2c comm here in writing mode
	    i2c_write(data_8bit[1]);
		i2c_write(data_8bit[0]);				
		i2c_stop();								//stop i2c here	
	}
	
	else
	{
		i2c_start(address<<1 | I2C_WRITE);		//starts i2c comm here in writing mode
		i2c_write(data);						//send pressed key char
		i2c_stop();								//stop i2c here
	}
}

void scan_i2c(void)
{
	int addresses_min = 0x00;
	int addresses_max = 0xF7;
	uint8_t logic;
	
	for (int i=addresses_min; i<=addresses_max; i++)
	{	
		if(!(logic=i2c_start(i<<1 | I2C_WRITE)))
		{
			printf("%X is on the bus \n",i);
		}
	}
}

int get_data_8bit( uint8_t opcode, uint8_t address)
{
	char New_data;
	char info;
	char checksum_reveived;
	char checksum_cal;
	
	
	info = i2c_start(address<<1 | I2C_WRITE);		//starts i2c comm here in writing mode
	
	if (info !=0)
	{
		printf("The receiver is unresponsive \n");   i2c_stop();    return -1;
	}
	
	else
	{
		info = i2c_write(opcode);		//send pressed key char
		
		if (info!=0)
		{
			printf("The receiver did not ack the data \n");   i2c_stop();   return -1;
		}
		
	}
	
	info = i2c_start(address<<1 | I2C_READ);		//starts i2c comm here in writing mode
	
	if (info == -1)
	{
		printf("The receiver sends no data \n");  i2c_stop();   return -1;
	}
	
	else
	{
		New_data=i2c_read_ack();	//read the byte
		
		if (New_data== -1)
		{
			printf("The receiver did not send the data \n");   i2c_stop();   return -1;
		}
		else
		{
			checksum_reveived=i2c_read_nack();
			
			i2c_stop();
			
			checksum_cal=cal_checksum(New_data, 8);
			
			if (checksum_cal==checksum_reveived)
			{
				/*printf("Result=%d\n",New_data);*/	return New_data;
			}
			
			else
			{			
				printf("Checksum failure\n"); 	return -1;
			}
		}
	}
	
	
	
	
	
	
	
}

int get_data_int( uint8_t opcode, uint8_t address)
{
	
	char info, bytes =2;
	int result=0;
	uint8_t New_data[bytes];
	char checksum_reveived;
	char checksum_cal;
	
	info = i2c_start(address<<1 | I2C_WRITE);		//starts i2c comm here in writing mode
	
	if (info !=0)
	{
		printf("The receiver is unresponsive\n");    i2c_stop();	return -1;
	}
	
	else
	{
		info = i2c_write(opcode);		//send pressed key char
		
		if (info!=0)
		{
			printf("The receiver did not ack the data \n");	   i2c_stop();  	return -1;
		}
	}
	
	info = i2c_start(address<<1 | I2C_READ);		//starts i2c comm here in writing mode
	
	if (info == -1)
	{
		printf("The receiver sends no data \n");   i2c_stop();	 return -1;
	}
	else
	{
		
		for (int i=0; i<bytes; i++)
		{
			New_data[i]=i2c_read_ack();
		//	printf("data %d \n",New_data[i]);
		
			if (New_data[i]== -1)
			{
				printf("The receiver did not send the data \n");    return -1;
			}
		}
		
		checksum_reveived=i2c_read_nack();	//read the byte
		//printf("Checksum received %d \n",checksum_reveived);
		
		if (checksum_reveived== -1)
		{
			printf("The receiver did not send the data \n");		return -1;
		}
		
		for (int i=0; i<bytes; i++)
		{
			result=result+(New_data[i] << 8*i);
		}
		
		i2c_stop();
		
		checksum_cal=cal_checksum(result, 16);
		//printf("Checksum calculated %d \n",checksum_cal);
		if (checksum_cal==checksum_reveived)
		{
			/*printf("Result=%d\n",result);*/	return result;
		}
		else
		{
			printf("Checksum failure\n"); 	return -1;
		}
	}
}

long get_data_long( uint8_t opcode, uint8_t address)
{
	
	int info, bytes =4;
	long result=0;
	long New_data[bytes];
	char checksum_reveived;
	char checksum_cal;
	
	info = i2c_start(address<<1 | I2C_WRITE);		//starts i2c comm here in writing mode
	
	if (info !=0)
	{
		printf("The receiver is unresponsive return value is %d \n",info);    i2c_stop();	return -1;
	}
	
	else
	{
		info = i2c_write(opcode);		//send pressed key char
		
		if (info!=0)
		{
			printf("The receiver did not ack the data \n");	   i2c_stop();  	return -1;
		}
	}
	
	info = i2c_start(address<<1 | I2C_READ);		//starts i2c comm here in writing mode
	
	if (info == -1)
	{
		printf("The receiver sends no data \n");   i2c_stop();	 return -1;
	}
	else
	{
		
		for (int i=0; i<bytes; i++)
		{
			New_data[i]=i2c_read_ack();
			//printf("data %li \n",New_data[i]);
			
			if (New_data[i]== -1)
			{
				printf("The receiver did not send the data \n");    return -1;
			}
		}
		
		checksum_reveived=i2c_read_nack();	//read the byte
		//printf("Checksum received %d \n",checksum_reveived);
		
		if (checksum_reveived== -1)
		{
			printf("The receiver did not send the data \n");		return -1;
		}
		
		for (int i=0; i<bytes; i++)
		{
			result=result+(New_data[i] << 8*i);
		}
		
		i2c_stop();
		
		checksum_cal=cal_checksum(result, 32);
		//printf("Checksum calculated %d \n",checksum_cal);
		if (checksum_cal==checksum_reveived)
		{
			/*printf("Result=%li\n",result);*/	return result;
		}
		else
		{
			printf("Checksum failure\n"); 	return -1;
		}
	}
	
}

int send_data_8bit( uint8_t opcode, uint8_t address, uint8_t data)
{
	char info;
	char send_data[3];
    send_data[0] = opcode;
	send_data[1] = data;
	send_data[2] = cal_checksum(data, 8);
	
	
	info = i2c_start(address<<1 | I2C_WRITE);		//starts i2c comm here in writing mode
	
	if (info !=0)
	{
		printf("The receiver is unresponsive \n");   i2c_stop();    return -1;
	}
	
	else
	{
		for (int i=0; i<3; i++)
		{
			
			info = i2c_write(send_data[i]);		//send pressed key char
		
			if (info!=0)
			{
				printf("The receiver did not ack the data \n");   i2c_stop();   return -1;
			}
		
		}
	
				printf("Data has been sent \n"); return 1;	
	}	
}

int send_data_int( uint8_t opcode, uint8_t address, int data)
{
	
	char info;
	char send_data[4];
	send_data[0] = opcode;
	send_data[1] = data;
	send_data[2] = data >> 8;
	send_data[3] = cal_checksum(data, 16);
	
	
	info = i2c_start(address<<1 | I2C_WRITE);		//starts i2c comm here in writing mode
	
	if (info !=0)
	{
		printf("The receiver is unresponsive \n");   i2c_stop();    return -1;
	}
	
	else
	{
		for (int i=0; i<4; i++)
		{
			
			info = i2c_write(send_data[i]);		//send pressed key char
			
			if (info!=0)
			{
				printf("The receiver did not ack the data \n");   i2c_stop();   return -1;
			}
		}
		
		
		printf("Data has been sent \n"); return 1;
	}
}

int send_data_long( uint8_t opcode, uint8_t address, long data)
{
	
	char info;
	char send_data[6];
	send_data[0] = opcode;
	send_data[1] = data;
	send_data[2] = data >> 8;
	send_data[3] = data >> 16;
	send_data[4] = data >> 24;
	send_data[5] = cal_checksum(data, 32);
	
	
	info = i2c_start(address<<1 | I2C_WRITE);		//starts i2c comm here in writing mode
	
	if (info !=0)
	{
		printf("The receiver is unresponsive \n");   i2c_stop();    return -1;
	}
	
	else
	{
		for (int i=0; i<6; i++)
		{
			
			info = i2c_write(send_data[i]);		//send pressed key char
			
			if (info!=0)
			{
				printf("The receiver did not ack the data \n");   i2c_stop();   return -1;
			}
		}
	}	
}

int cal_checksum(int value, char length)
{
	char array[length];
	char Checksum=0;
	for (int i=0; i<length; i++)
	{   array[i] = 0;
		array[i]= (value>>((length-1)-i)) & 1;
		Checksum^=array[i];
	}
	return Checksum;
}

void i2c_timer0_init(void)
{
	TCCR0A |= (1 << WGM01);
	// Set the Timer Mode to CTC
	OCR0A = 0xF9;
	TCNT0 = 0;
	// Set the value that you want to count to 256
	TIMSK0 |= (1 << OCIE0A);
	//Set the ISR COMPA vect
	TCCR0B |= (1 << CS01) | (1 << CS00);
	// set prescaler to 64 and start the timer
	sei(); // turn on interrupts
}


ISR (TIMER0_COMPA_vect) // timer0 overflow interrupt
{	
	counter++;
	
	if (counter==30)
	{
		flag=1;
		counter=0;
		
	}
	
	increase_counters();	
}