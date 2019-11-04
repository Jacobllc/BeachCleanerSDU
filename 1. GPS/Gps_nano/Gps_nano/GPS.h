/*
 * GPS.h
 *
 * Created: 10/28/2019 11:14:52 AM
 *  Author: Hörður Hermannsson
 */ 


#ifndef GPS_H_
#define GPS_H_
#define Nr_msg 2
#define I2C_ADD 0x10

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usart_IRS_RX.h"

void GPS_init(void);
void check_gps_data(void);
void stop_gps_sample(void);
void printing_data(void);
void I2C_received(uint8_t received_data);
void I2C_requested();	
void I2C_slave_init();




#endif /* GPS_H_ */