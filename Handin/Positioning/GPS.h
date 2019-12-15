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


#endif /* GPS_H_ */