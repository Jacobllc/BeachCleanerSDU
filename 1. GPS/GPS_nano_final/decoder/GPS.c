
/* GPS.c
* Created: 10/28/2019 11:15:13 AM
*  Author:  Hörður Hermannsson
*/

#include "GPS.h"
#include "NMEA_DECODER.h"

//-----------------------------------------------------
//GLOBAL VAR, Structs
//-----------------------------------------------------
volatile uint8_t byte ;		// What byte is being worked with
volatile uint8_t process;


typedef struct GPS{
char length;
char data[80];
int msg_done_flag; 
}GPS;

 GPS Gps_data; //Init GPS_data from the C94-M8P module 

//-----------------------------------------------------
//Functions
//-----------------------------------------------------
void GPS_init(void)
{				
	DDRD &= ~(1 << DDD2);	             // PD2 set as input
	PORTD |= (0 << PORTD2);				 // turn OFF the Pull-up
	EIMSK |= (1<<INT0);
	EICRA |= (1 << ISC00)| (1 << ISC01); // set INT0 to trigger on falling edge logic change
	sei();								 // turn on interrupts
}


void read_gps_data(void)
{
	if (process==1)   //if NMEA data is inbound 
	{
		print_flag=1; 
		if (UDR0=='\n')
		{
			Gps_data.length=byte;
			byte=-1;
			
			Gps_data.msg_done_flag=1; //raise when message is complete 
			stop_gps_sample(); //Wait for pin interrupt again 
		}
		else
		{
			Gps_data.data[byte]=UDR0;
			byte++;
		}
	}
}


int get_gps_message (char* msg_main){
	
	if(Gps_data.msg_done_flag==1){
		Gps_data.msg_done_flag = 0; 
		
		memcpy(msg_main, Gps_data.data, sizeof(Gps_data.data));
		 
		return 1;	//Return address to message
	}
	else
	{
		return 0;	//return addrres to nothing 
	}
}

void stop_gps_sample(void)
{
	process=0;
	print_flag=0;
}


void printing_data(void) //FOR TESTING PURPOSES 
{
	if (print_flag==0)
	{
		for (int i=0; i<Gps_data.length; i++){
			
			usart_send(Gps_data.data[i]);
		}

			usart_send('\r');
			usart_send('\n');
	}
	print_flag=1;
}


ISR(INT0_vect) //Interrupt every data package start "Blue light" 
{
	process=1;
	byte=-1;
}
