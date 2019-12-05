/*
 * i2c_atmega_328p_slave.c
 *
 * Created: 16.9.2019 20:30:50
 *  Author: Hörður Hermannsson 
 */
#include <util/twi.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "set_up.h"
#include "US_send.h"

#include "i2c_atmega_328p_slave.h"


volatile uint8_t data;


void I2C_recieve(uint8_t received_data)							//isr on receiving a byte on i2c
 {
	set_opcode(received_data);
	data=received_data;							
 }		
 
 
void I2C_data_ACK_request(void)												//if master request data from slave
{
	i2c_service();
	i2c_transmit_data(data);
	
	
}

 
 void I2C_data_NACK_request(void)												//if master request data from slave
 {
	 
	 i2c_service();
	 i2c_transmit_data(data);
	
	 
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

void i2c_transmit_data(uint8_t data)
{		
	TWDR = data;
}

void set_data(uint8_t value)
{
	data = value;
}


 
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
		// master is requesting data using NACK,master expects only one additional byte. call the request callback
		I2C_data_NACK_request();
		TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		break;
		
		case TW_ST_DATA_ACK:
		// master is requesting data using ACK, master expects multiple bytes. call the request callback
		I2C_data_ACK_request();
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



	
	
	