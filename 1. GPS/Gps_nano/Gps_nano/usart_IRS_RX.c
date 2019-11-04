/*
 * usart_IRS_RX.c
 *
 * Created: 10/10/2019 7:43:12 PM
 *  Author: hordur Hermannsson
 */ 

#include "usart_IRS_RX.h"
#include "GPS.h"

unsigned char usart_receive(void){
	while(!(UCSR0A & (1<<RXC0))); //wait for new data
	return UDR0; //received data
}

void usart_send( unsigned char data){
	while(!(UCSR0A & (1<<UDRE0))); //wait for transmit buffer
	UDR0 = data; //data to be sent
}

void usart_init(void)
{
	UBRR0H = (uint8_t)(BAUD_PRESCALER>>8);
	UBRR0L = (uint8_t)(BAUD_PRESCALER);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)| (1<<RXCIE0);
	UCSR0C = ((1<<UCSZ00)|(1<<UCSZ01));
}


ISR(USART_RX_vect)
{		
	check_gps_data();
}