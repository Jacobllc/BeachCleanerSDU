/*
 * i2c_atmega_328p_slave.c
 *
 * Created: 16.9.2019 20:30:50
 *  Author: H�r�ur Hermannsson 
 */

#include <util/twi.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "i2c_atmega_328p_slave.h"


static void (*I2C_recieve)(uint8_t);		
static void (*I2C_data_request)();

void I2C_setCallbacks(void (*reciece_call)(uint8_t), void (*request_call)())
{
	I2C_recieve = reciece_call;
	I2C_data_request = request_call;
}

void i2c_init(uint8_t address)
{
	
		cli();						
		TWAR = address << 1;										// load address into TWI address register
		TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWEN);		// set the TWCR to enable address matching and enable TWI, clear TWINT, enable TWI interrupt
		sei();														//enable TWI interrupt
}


void i2c_stop(void)
{
		
		cli();
		TWCR = 0;			// clear acknowledge and enable bits
		TWAR = 0;
		sei();
}


void i2c_transmit_data(int data)
{	
	
	TWDR = data;
}






// TWI Interrupt!! 


ISR(TWI_vect)
{
	switch(TW_STATUS)
	{
		case TW_SR_DATA_ACK:
		// received data from master, call the receive callback
		I2C_recieve(TWDR);
		
		TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		break;
		
		case TW_ST_SLA_ACK:
		// master is requesting data, call the request callback
		I2C_data_request();
		TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		break;
		
		case TW_ST_DATA_ACK:
		// master is requesting data, call the request callback
	
		TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		
		break;
		
		case TW_BUS_ERROR:
		// some sort of erroneous state, prepare TWI to be readdressed
		TWCR = 0;
		TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		break;
		
		default:
		TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		break;
	}
}



	
	
	