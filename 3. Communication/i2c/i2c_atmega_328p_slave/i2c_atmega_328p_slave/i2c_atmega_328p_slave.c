/*
 * i2c_atmega_328p_slave.c
 *
 * Created: 16.9.2019 20:30:50
 *  Author: Hörğur Hermannsson 
 */

#include <util/twi.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "i2c_atmega_328p_slave.h"

void I2C_recieve(uint8_t received_data)							//isr on receiving a byte on i2c
 {
	 data = received_data;
	 data2=data+2;													//received data
	 printf("From master: %d\n",data);											
 }		
 
void I2C_data_request()												//if master request data from slave
{
	i2c_transmit_data(data2);
}

void i2c_init(uint8_t address)
{
		cli();						
		TWAR = address << 1;										// load address into TWI address register
		TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWEN);		// set the TWCR to enable address matching and enable TWI, clear TWINT, enable TWI interrupt
		sei();														//enable TWI interrupt
}

void i2c_disable(void)
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
 
ISR(TWI_vect)
{
	switch(TW_STATUS)
	{
		case TW_SR_DATA_ACK:
		printf("TW_SR_DATA_ACK\n");
		// received data from master, call the receive callback
		I2C_recieve(TWDR);
		
		TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		break;
		
		case TW_ST_SLA_ACK:
		// master is requesting data, call the request callback
		printf("TW_ST_SLA_ACK\n");
		I2C_data_request();
		TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		break;
		
		case TW_ST_DATA_ACK:
		// master is requesting data, call the request callback
		printf("TW_ST_DATA_ACK\n");
		I2C_data_request();
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



	
	
	