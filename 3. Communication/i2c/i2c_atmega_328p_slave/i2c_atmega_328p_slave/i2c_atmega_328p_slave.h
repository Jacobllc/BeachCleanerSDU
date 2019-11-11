/*
 * i2c_atmega_328p_slave.h
 *
 * Created: 16.9.2019 20:30:26
 *  Author: Hörður Hermannsson
 */ 


#ifndef I2C_ATMEGA_328P_SLAVE_H_
#define I2C_ATMEGA_328P_SLAVE_H_

#include<avr/interrupt.h>
#include <stdint.h>

volatile uint8_t data;
volatile uint8_t data2;

// Function prototypes

void i2c_init(uint8_t address);					// Enable I2C.
void i2c_disable(void);							// Disable I2C.	
void i2c_transmit_data(int data);			// Write data into buffer.



#endif /* I2C_ATMEGA_328P_SLAVE_H_ */