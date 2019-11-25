/*
 * Motor_i2c.h
 *
 * Created: 11/24/2019 4:04:53 PM
 *  Author: Red
 */ 


#ifndef MOTOR_I2C_H_
#define MOTOR_I2C_H_

#define I2C_ADDR 0x41	

char bytes;
uint8_t opcode;

char status;
char zone;
int error;

// Function prototypes



void i2c_service(void);
int cal_checksum(int value, char length);
void Motor_Send_Status(void);
void Motor_Send_error(void);
void Motor_Send_zone(void);

#endif /* MOTOR_I2C_H_ */