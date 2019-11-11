/*
 * i2c_atmega_328p_master.h
 *
 * Created: 16.9.2019 23:51:59
 *  Author: Hörður Hermannsson
 */ 


#ifndef I2C_ATMEGA_328P_MASTER_H_
#define I2C_ATMEGA_328P_MASTER_H_


#define I2C_READ 0x01
#define I2C_WRITE 0x00
#define slave_address 0x40

// Functions prototypes 

void i2c_init(void);
uint8_t i2c_start(uint8_t address);
uint8_t i2c_write(uint8_t data);
uint8_t i2c_read_ack(void);
uint8_t i2c_read_nack(void);
uint8_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length);
uint8_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length);
uint8_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
uint8_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
void i2c_stop(void);
void i2c_transmit_2bytes(int data, uint8_t address);
void scan_i2c(void);
void i2c_sync(void);


#endif /* I2C_ATMEGA_328P_MASTER_H_ */