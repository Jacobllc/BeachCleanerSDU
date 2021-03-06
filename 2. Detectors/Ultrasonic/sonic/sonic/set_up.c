
#include "set_up.h"

//zone=0; 

int obs,flag; 

void init_io(){
	//Sensor1
	DDRD |= (1<<DDD4); //PD3 is an output (TRIG1)
	DDRD &= ~(1<<DDD3); //PD4 is an INPUT (Echo1)
	//Sensor2
	DDRB |= (1<<DDB2); //PB2 is an output (TRIG2)
	DDRB &= ~(1<<DDB1); //PB1 is an INPUT (Echo2)
	//Sensor3
	DDRB |= (1<<DDB0); //PB0 is an output (TRIG3)
	DDRD &= ~(1<<DDD7); //PD7 is an INPUT (Echo3)
	//Sensor 4
	DDRD |= (1<<DDD6); // PD6 OUTPUT (TRIGGER)
	DDRD &= ~(1<<DDD5); // PD5 INOUT (ECCHO)
}
int getdist1(void){

//PD4 TRIGGER PD3 ECHO

int dis;
//SENDING THE TRIGGER
PORTD |= (1<<PORTD4);
TCNT1 = 0;
while (TCNT1 < 10);
PORTD &= ~(1<<PORTD4);
//RECIVE ECCHO
TCNT1 = 0;
while ((!(PIND & (1<<PORTD3))) && TCNT1 < 5900); //Wait for echo PIN to go high
TCNT1 = 0;
while ((PIND & (1<<PORTD3)) && TCNT1 < 5900); //stay here until data form echo is returned (count the time) the value 1475 is for 0.5 m

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
	PORTB &= ~(1<<PORTB2);
	//RECIVE ECCHO
	TCNT1 = 0;
	while ((!(PINB & (1<<PORTB1))) && TCNT1 < 5900);
	TCNT1 = 0;
	while ((PINB & (1<<PORTB1)) && TCNT1 < 5900); //stay here until data form echo is returned (count the time) the value 1475 is for 0.5 m
	
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
	PORTB &= ~(1<<PORTB0);
	//RECIVE ECCHO
	TCNT1 = 0;
	while ((!(PIND & (1<<PORTD7)))  && TCNT1 < 5900);
	TCNT1 = 0;
	while ((PIND & (1<<PORTD7)) && TCNT1 < 5900); //stay here until data form echo is returned (count the time) the value 1475 is for 0.5 m
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
	PORTD &= ~(1<<PORTD6);
	//RECIVE ECCHO
	TCNT1 = 0;
	while ((!(PIND & (1<<PORTD5))) && TCNT1 < 5900 );
	//printf("echo4 high! ")	;
	TCNT1 = 0;
	while ((PIND & (1<<PORTD5)) && TCNT1 < 5900); //stay here until data form echo is returned (count the time) the value 5900 is for 0.5 m

	dis = ( (int)TCNT1/2)/58;
	return dis;
	
}
void init_timers()
{
	TCCR1B = (1<<CS11);
}

void min_dist(int dis)
{
	if((getdist1()>dis) && (getdist2()>dis) && (getdist3()>dis) && (getdist4()>dis))
	{
		obs = 0;
	}
	else
	{
		obs = 1;
	}
}
int deadswitch(void)
{
	DDRD &= ~(1 << DDD2); //CLEAR PD2 INT0 PIN IS NOW INPUT
	PORTD |= (1 << PORTD2); // TURN ON PULL UP, PULL UP ENABLE
	
	EICRA |= (1 << ISC01); //SET INTO TO TRIGGER AT FALLING EDGES
	EIMSK |= (1 << INT0); //TURNS ON THE INTERRPUT FOR INT0
	sei();
	
	
	
}
ISR (INT0_vect)// EXTERNAL INTERRUPT 0
{
	if ((1<<PIND2))
	{
		flag=1;
		zone = 1;
		// commands for the respective motors and what to look for have to be implemented
		
	}
	//printf("%d",flag);
}

int distance (void)
{
	int n = 30;		// Samples per average
	//int s = 4;		// Number of sensors
	int i;
	
	volatile int distance_1_array[n], distance_2_array[n], distance_3_array[n], distance_4_array[n];
	//volatile int av_distance_array[4];
	volatile int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
	
	for (i=0; i<n; i++)
	{
		// Fill arrays with distances
		distance_1_array[i] = getdist1();
		//printf("dist1 ok");
		distance_2_array[i] = getdist2();
		//printf("dist2 ok");
		distance_3_array[i] = getdist3();
		//printf("dist3 ok");
		distance_4_array[i] = getdist4();
		//printf("dist4 ok");
				
		// Build sum of distances
		sum1 = sum1 + distance_1_array[i];
		sum2 = sum2 + distance_2_array[i];
		sum3 = sum3 + distance_3_array[i];
		sum4 = sum4 + distance_4_array[i];
		
	}
	// Calculate average
	av_distance_array[1] = sum1/n;
	av_distance_array[2] = sum2/n;	
	av_distance_array[3] = sum3/n;
	av_distance_array[4] = sum4/n;	
	
	//Determine the zone
	if ((av_distance_array[1])>=41 && (av_distance_array[2])>=41 && (av_distance_array[3])>=41 && (av_distance_array[4])>=41) zone=3;
	if (((av_distance_array[1])<=40 || (av_distance_array[2])<=40 ||(av_distance_array[3])<=40 || (av_distance_array[4])<=40) && ((av_distance_array[1])>=21 && (av_distance_array[2])>=21 && (av_distance_array[3])>=21) &&  (av_distance_array[4])>=21) zone=2;
	if ((av_distance_array[1])<=20 || (av_distance_array[2])<=20 || (av_distance_array[3])<=20 || (av_distance_array[4])<=20) zone=1;

	return zone;
}