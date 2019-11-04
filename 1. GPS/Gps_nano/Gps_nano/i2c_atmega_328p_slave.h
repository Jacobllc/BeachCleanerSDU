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



// Function prototypes

void i2c_init(uint8_t address);					// Enable I2C.
void i2c_stop(void);							// Disable I2C.	
void i2c_transmit_data(int data);			// Write data into buffer.
void I2C_setCallbacks(void (*reciece_call)(uint8_t), void (*request_call)());  // setting uo callbacks

#endif /* I2C_ATMEGA_328P_SLAVE_H_ */