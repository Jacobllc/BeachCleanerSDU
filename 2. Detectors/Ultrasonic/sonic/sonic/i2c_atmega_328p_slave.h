/*
 * i2c_atmega_328p_slave.h
 *
 * Created: 16.9.2019 20:30:26
 *  Author: Hörður Hermannsson
 */ 


#ifndef I2C_ATMEGA_328P_SLAVE_H_
#define I2C_ATMEGA_328P_SLAVE_H_
#define I2C_ADDR 0x40												
#include <stdint.h>

// Function prototypes

void i2c_init(uint8_t address);					// Enable I2C.
void i2c_disable(void);							// Disable I2C.	
void i2c_transmit_data(uint8_t data);			// Write data into buffer.
void I2C_recieve(uint8_t received_data);
void I2C_data_ACK_request(void);		
void I2C_data_NACK_request(void);		
void set_data(uint8_t value);										

#endif /* I2C_ATMEGA_328P_SLAVE_H_ */