/*
 * i2c_atmega_328p_master.c
 *
 * Created: 16.9.2019 23:52:22
 *  Author: Hörður Hermannsson
 */ 


#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>

#include "i2c_atmega_328p_master.h"
#define F_CPU 16000000UL
#define F_SCL 100000UL // SCL frequency
#define Prescaler 1
#define TWBR_val ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)

#define INT_ms 2500

volatile uint8_t int_counter = 0; 
volatile uint8_t flag  = 0 ; 

void setup_timer(void)
{
// TIMER 0 for interrupt frequency 1000 Hz:
cli(); // stop interrupts
TCCR0A = 0; // set entire TCCR0A register to 0
TCCR0B = 0; // same for TCCR0B
TCNT0  = 0; // initialize counter value to 0
// set compare match register for 1000 Hz increments
OCR0A = 249; // = 16000000 / (64 * 1000) - 1 (must be <256)
// turn on CTC mode
TCCR0B |= (1 << WGM01);
// Set CS02, CS01 and CS00 bits for 64 prescaler
TCCR0B |= (0 << CS02) | (1 << CS01) | (1 << CS00);
// enable timer compare interrupt
TIMSK0 |= (1 << OCIE0A);
sei(); // allow interrupts

}



void i2c_init(void)
{
	setup_timer();
	TWBR = (uint8_t)TWBR_val;
}

uint8_t i2c_start(uint8_t address)
{
	flag = 0;
	TCNT0 = 0;
	TIMSK0 |= (1 << OCIE0A);
	
	TWCR = 0;																	// reset TWI control register
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);									// transmit START condition
	while( !(TWCR & (1<<TWINT)) )						// wait for end of transmission
		{
			if(flag==1)
			{
			TIMSK0 &= ~(1 << OCIE0A);
			return 0;
			}
		}
	
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

	flag = 0;
	TCNT0 = 0;
	TIMSK0 |= (1 << OCIE0A);

	TWCR = 0;

	TWDR = data;																// load data into data register
	TWCR = (1<<TWINT) | (1<<TWEN);												// start transmission of data
	while( !(TWCR & (1<<TWINT)) )												// wait for end of transmission
			{
				if(flag==1)
				{
					TIMSK0 &= ~(1 << OCIE0A);
					return 0;
				}
			}
			
	if( (TWSR & 0xF8) != TW_MT_DATA_ACK )
	{ return 1; }
	
	return 0;
}

uint8_t i2c_read_ack(void)
{
	flag = 0;
	TCNT0 = 0; 
	TIMSK0 |= (1 << OCIE0A);
	
	
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);			// start TWI module and acknowledge data after reception
	
	while( !(TWCR & (1<<TWINT)) )						// wait for end of transmission
	{
		if(flag==1)
		{
			TIMSK0 &= ~(1 << OCIE0A);
			return 0;
		}
	}						
	
	return TWDR;										// return received data from TWDR

}

uint8_t i2c_read_nack(void)
{
	
	TWCR = (1<<TWINT) | (1<<TWEN);// start receiving without acknowledging reception
	while( !(TWCR & (1<<TWINT)) );	// wait for end of transmission

	return TWDR;					// return received data from TWDR

}

uint8_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length)
{
	if (i2c_start(address<<1 | I2C_WRITE)) return 1;
	
	for (uint16_t i = 0; i < length; i++)
	{
		if (i2c_write(data[i])) return 1;
	}
	
	i2c_stop();
	
	return 0;
}

uint8_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length)
{
	if (i2c_start(address<<1 | I2C_READ)) return 1;
	
	for (uint16_t i = 0; i < (length-1); i++)
	{
		data[i] = i2c_read_ack();
	}
	data[(length-1)] = i2c_read_nack();
	
	i2c_stop();
	
	return 0;
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

ISR(TIMER0_COMPA_vect)
{
	if(int_counter==INT_ms)
	{
	flag = 1; 
	//printf("%d\n\n", INT_ms);
	int_counter = 0;
	}
	else
	{
	int_counter ++;	
	}
}
