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
#include "set_up.h"
int obs;
void init_io(){
	//Sensor1
	DDRD |= (1<<DDD4); //PB3 is an output (TRIG1)
	DDRD &= ~(1<<DDD3); //PB4 is an INPUT (Echo1)
	//Sensor2
	DDRB |= (1<<DDB2); //PB2 is an output (TRIG2)
	DDRB &= ~(1<<DDB1); //PB1 is an INPUT (Echo2)
	//Sensor3
	DDRB |= (1<<DDB0); //PB0 is an output (TRIG3)
	DDRD &= ~(1<<DDD7); //PD7 is an INPUT (Echo3)
}
int getdist1(void){

//PD4 TRIGGER PD3 ECHO

int dis;
//SENDING THE TRIGGER

PORTD |= (1<<PORTD4);
TCNT1 = 0;
while (TCNT1 < 10);
//RECIVE ECCHO

PORTD &= ~(1<<PORTD4);
TCNT1 = 0;
while (!(PIND & (1<<PORTD3)));
TCNT1 = 0;
while ((PIND & (1<<PORTD3)) && TCNT1 < 1475); //stay here until data form echo is returned (count the time) the value 1475 is for 0.5 m

dis = ( (int)TCNT1/2)/58;
return dis;
}
int getdist2(void){
	//PB2 TRIGGER PB1 ECHO

	int dis;
	//sENDING THE TRIGGER

	PORTB |= (1<<PORTB2);
	TCNT1 = 0;
	
	while (TCNT1 < 10);
	
	//RECIVE ECCHO
	PORTB &= ~(1<<PORTB2);
	
	TCNT1 = 0;
	while (!(PINB & (1<<PORTB1)));
	TCNT1 = 0;
	while ((PINB & (1<<PORTB1)) && TCNT1 < 1475); //stay here until data form echo is returned (count the time) the value 1475 is for 0.5 m
	
	dis = ( (int)TCNT1/2)/58;
	
	return dis;
}
int getdist3(void){
	//PB0 TRIGGER PD7 ECHO

	int dis;
	//sENDING THE TRIGGER

	PORTB |= (1<<PORTB0);
	TCNT1 = 0;
	while (TCNT1 < 10);
	//RECIVE ECCHO

	PORTB &= ~(1<<PORTB0);
	TCNT1 = 0;
	while (!(PIND & (1<<PORTD7)));
	TCNT1 = 0;
	while ((PIND & (1<<PORTD7)) && TCNT1 < 1475); //stay here until data form echo is returned (count the time) the value 1475 is for 0.5 m
	dis = ( (int)TCNT1/2)/58;
	return dis;
	
}
int getdist4(void){
	//PD6 TRIGGER PD5 ECHO

	int dis;
	//sENDING THE TRIGGER

	PORTD |= (1<<PORTD6);
	TCNT1 = 0;
	while (TCNT1 < 10);
	//RECIVE ECCHO
	PORTD &= ~(1<<PORTD6);
	TCNT1 = 0;
	 while (!(PIND & (1<<PORTD5))) 		
	TCNT1 = 0;
	while ((PIND & (1<<PORTD5)) && TCNT1 < 1475); //stay here until data form echo is returned (count the time) the value 1475 is for 0.5 m

	dis = ( (int)TCNT1/2)/58;
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



int main(void)
{
	
    uart_init(); //open comms to microcontroller (Realterm)
    io_redirect();
	init_timers();
	
	int sample=10;
	int sum = 0;
	int n = 30;
	int i;
	volatile int distance_1_array[n], distance_2_array[n], distance_3_array[n], distance_4_array[n];
	
    while (1) 
    {
		volatile int av_distance1 = 0, av_distance2 = 0, av_distance3 = 0, av_distance4 = 0;
		// Fill arrays with n distance samples (100ms)
		
		for (i=0; i<n; i++) 
		{
				// Fill array with distances
			//distance_1_array[i] = getdist1();
			distance_2_array[i] = getdist2();
		
			// Build sum of distances 
			
			//av_distance1 = av_distance1 + distance_1_array[i];
			av_distance2 = av_distance2 + distance_2_array[i];
		}

		// Calculate average 
		//av_distance1=av_distance1/n;
		av_distance2 = av_distance2/n;
		//printf("Average: %d \n", av_distance2);
		
		if (TCNT1 == 5900) // toggle pin every time you read the four sensors. XOR the pin to see it
		{
			PORTD ^=(1<<PORTD2);
		}
		 }
}

