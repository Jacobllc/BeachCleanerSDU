/*
 * usart_IRS_RX.h
 *
 * Created: 10/10/2019 7:43:35 PM
 *  Author: hordu
 */ 


#ifndef USART_IRS_RX_H_
#define USART_IRS_RX_H_

#define BAUDRATE 19200
#define BAUD_PRESCALER (((F_CPU / (BAUDRATE * 16UL))) - 1)
#define F_CPU 16000000UL


#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>


void usart_init(void);
unsigned char usart_receive(void);
void usart_send(unsigned char data);



#endif
