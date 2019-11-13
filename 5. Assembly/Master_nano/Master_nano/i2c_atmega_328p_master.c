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

uint8_t i2c_write(uint8_t data)
{

	TWDR = data;																// load data into data register
	TWCR = (1<<TWINT) | (1<<TWEN);												// start transmission of data
	while( !(TWCR & (1<<TWINT)) );												// wait for end of transmission
	
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
	
	PORTD^=(1<<PORTD2);
	return (int)TWDR;								// return received data from TWDR
	
	
}

uint8_t i2c_read_nack(void)
{
	
	TWCR = (1<<TWINT) | (1<<TWEN);// start receiving without acknowledging reception
	while( !(TWCR & (1<<TWINT)) );	// wait for end of transmission

	return TWDR;					// return received data from TWDR

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
	
	if (counter==20)
	{
		flag=1;
		counter=0;
		
	}
	
	if (flag==0)
	{PORTD=(1<<PORTD3);
	}
	
	else
	{
		
		PORTD=(0<<PORTD3);
	}
}