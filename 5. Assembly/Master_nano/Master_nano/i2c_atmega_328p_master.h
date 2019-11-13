/*
 * i2c_atmega_328p_master.h
 *
 * Created: 16.9.2019 23:51:59
 *  Author: Hörğur Hermannsson
 */ 


#ifndef I2C_ATMEGA_328P_MASTER_H_
#define I2C_ATMEGA_328P_MASTER_H_


#define I2C_READ 0x01
#define I2C_WRITE 0x00

// Functions prototypes 

void i2c_init(void);
int i2c_start(uint8_t address);
uint8_t i2c_write(uint8_t data);
int i2c_read_ack(void);
uint8_t i2c_read_nack(void);
uint8_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length);
uint8_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length);
uint8_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
uint8_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
void i2c_stop(void);
void i2c_transmit_2bytes(int data, uint8_t address);
void scan_i2c(void);
void i2c_timer0_init(void);
int get_data_8bit( uint8_t opcode, uint8_t address);
int get_data_int( uint8_t opcode, uint8_t address);
long get_data_long( uint8_t opcode, uint8_t address);



#endif /* I2C_ATMEGA_328P_MASTER_H_ */