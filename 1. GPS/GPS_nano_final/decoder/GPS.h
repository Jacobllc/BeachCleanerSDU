/*
 * GPS.h
 *
 * Created: 10/28/2019 11:14:52 AM
 *  Author: Hörður Hermannsson
 */ 


#ifndef GPS_H_
#define GPS_H_
#define Nr_msg 2      //GPGGA and GPGSA messages 
#define I2C_ADD 0x10

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usart_IRS_RX.h"

// uint8_t command;

//Global var 
volatile uint8_t print_flag; 


void GPS_init(void);
void read_gps_data(void);
void stop_gps_sample(void);
int get_gps_message (char* msg_main);


void printing_data(void);




void I2C_received(uint8_t received_data);
void I2C_requested();	
void I2C_slave_init();
void send_latitdue(void);
void send_logtitude(void);
void send_age_of_data(void);
void send_quality(void);
void send_direction(void);
void send_velocity(void);



#endif /* GPS_H_ */