/*
 * sonic.c
 *
 * Created: 06/11/2019 12.42.54
 * Author : chalo
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include "usart.h"
int obs;
void init_io(){
	//Sensor1
	DDRB |= (1<<DDB3); //PB3 is an output (TRIG1)
	DDRB &= ~(1<<DDB4); //PB4 is an INPUT (Echo1)
	//Sensor2
	DDRB |= (1<<DDB2); //PB2 is an output (TRIG2)
	DDRB &= ~(1<<DDB1); //PB1 is an INPUT (Echo2)
	//Sensor3
	DDRB |= (1<<DDB0); //PB0 is an output (TRIG3)
	DDRD &= ~(1<<DDD7); //PD7 is an INPUT (Echo3)
}
float getdist1(void){
//PB3 TRIGGER PB4 ECHO

float dis;
//sENDING THE TRIGGER

PORTB |= (1<<PORTB3);
TCNT1 = 0;
while (TCNT1 < 10);
//RECIVE ECCHO

PORTB &= ~(1<<PORTB3);
TCNT1 = 0;
while (!(PINB & (1<<PORTB4)));
TCNT1 = 0;
while ((PINB & (1<<PORTB4)) && TCNT1 < 5900); //stay here until data form echo is returned (count the time)

dis = ( (float)TCNT1/2)/58;
return dis;
}
float getdist2(void){
	//PB2 TRIGGER PB1 ECHO

	float dis;
	//sENDING THE TRIGGER

	PORTB |= (1<<PORTB2);
	TCNT1 = 0;
	while (TCNT1 < 10);
	//RECIVE ECCHO

	PORTB &= ~(1<<PORTB2);
	TCNT1 = 0;
	while (!(PINB & (1<<PORTB1)));
	TCNT1 = 0;
	while ((PINB & (1<<PORTB1)) && TCNT1 < 11800); //stay here until data form echo is returned (count the time)

	dis = ( (float)TCNT1/2)/58;
	return dis;
}
float getdist3(void){
	//PB0 TRIGGER PD7 ECHO

	float dis;
	//sENDING THE TRIGGER

	PORTB |= (1<<PORTB0);
	TCNT1 = 0;
	while (TCNT1 < 10);
	//RECIVE ECCHO

	PORTB &= ~(1<<PORTB0);
	TCNT1 = 0;
	while (!(PIND & (1<<PORTD7)));
	TCNT1 = 0;
	while ((PIND & (1<<PORTD7)) && TCNT1 < 11800); //stay here until data form echo is returned (count the time)

	dis = ( (float)TCNT1/2)/58;
	return dis;
	
}
float getdist4(void){
	//PD6 TRIGGER PD5 ECHO

	float dis;
	//sENDING THE TRIGGER

	PORTD |= (1<<PORTD6);
	TCNT1 = 0;
	while (TCNT1 < 10);
	//RECIVE ECCHO

	PORTD &= ~(1<<PORTD6);
	TCNT1 = 0;
	while (!(PIND & (1<<PORTD5)));
	TCNT1 = 0;
	while ((PIND & (1<<PORTD5)) && TCNT1 < 11800); //stay here until data form echo is returned (count the time)

	dis = ( (float)TCNT1/2)/58;
	return dis;
	
}
void init_timers(){
	TCCR1B = (1<<CS11);
}
void min_dist(int dis)
{
	if((getdist1()>dis) && (getdist2()>dis) && (getdist3()>dis) )
	{
		obs = 0;
	}
	else
	{
		obs = 1;
	}
}
volatile float distance;
volatile float distance2;
volatile float distance3;
volatile float distance4;

int main(void)
{
    uart_init(); //open comms to microcontroller (Realterm)
    io_redirect();
	init_timers();

    while (1) 
    {
		 distance= getdist1();
		 distance2 = getdist2();
		// distance3 = getdist3();
		 distance4 = getdist4();
		printf("%.1f    %.1f   %.1f    \n",distance, distance2, distance4);
    }
}

