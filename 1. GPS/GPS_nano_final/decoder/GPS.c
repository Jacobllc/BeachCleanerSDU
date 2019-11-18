
/* GPS.c
* Created: 10/28/2019 11:15:13 AM
*  Author:  Hörður Hermannsson
*/

#include "GPS.h"
#include "NMEA_DECODER.h"
//#include "i2c_atmega_328p_slave.h"

//-----------------------------------------------------
//GLOBAL VAR, Structs
//-----------------------------------------------------
volatile uint8_t byte ;		// What byte is being worked with
//volatile uint8_t package=0;

volatile uint8_t process;


typedef struct GPS{
char length;
char data[80];
int msg_done_flag; 
}GPS;

//GPS Gps_data[Nr_msg];    //Array of GPGGA and GPGSA messages 

 GPS Gps_data; 

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
			//Gps_data[package].length=byte; //for 2 pakages 
			//package++;  
			
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

		/* Dont care about GPGSA message 
		if (package>=Nr_msg)
		{
			stop_gps_sample();
		}
		*/
	}
}


int get_gps_message (char* msg_main){
	
	if(Gps_data.msg_done_flag==1){
		Gps_data.msg_done_flag = 0; 
		
		memcpy(msg_main, Gps_data.data, sizeof(Gps_data.data));
		
		//msg_main = Gps_data.data; 
		
		return 1;	//Return address to message
	}
	else
	{
		return 0;		//return addrres to nothing 
	}
}

void stop_gps_sample(void)
{
	process=0;
	print_flag=0;
}


void printing_data(void)
{
	if (print_flag==0)
	{
		for (int i=0; i<Gps_data.length; i++){
			
			usart_send(Gps_data.data[i]);
		}

	/*
		for (int i=0; i<Nr_msg; i++)
		{

			for (int j=0; j<Gps_data[i].length; j++)
			{
				usart_send(Gps_data[i].data[j]);
			}

			//nmea_checksum(Gps_data[i].data);
			
			for (int j=0; j<=79; j++)
			{
				Gps_data[i].data[j]=0;
			}
	*/

			usart_send('\r');
			usart_send('\n');
	}
	print_flag=1;
}



//gete meassage 



ISR(INT0_vect) //Interrupt every data package start "Blue light" 
{
	process=1;
	//package=0;
	byte=-1;
	PORTC &= ~(1<<PORTC0); //Set data_ready_flag LOW When bearing and distance had been send.
}


/*  I2C commented out FOR NOW 


int command;  //FOR TEsTING 
void I2C_received(uint8_t received_data)							//isr on receiving a byte on i2c
{
	command = received_data;								
}

void I2C_requested(void)												//if master request data from slave
{
	 switch(command)
	 {
		 
		 case 0:
		 {
		 send_latitdue();
		 break;
		 }
		 
		 case 1:
		 {
		 send_logtitude();
		 break;
		 }
		  
		 case 2:
		 {
		 send_quality();
		 break;
		 }
		    
		 case 3:
		 {
		 send_age_of_data();
		 break;
		 }
		 
		 case 4:
		 {
		 send_direction();
		 break;
		 }
		  
		 case 5:
		 {
		 send_velocity();
		 break;
		 }
	 }
}

void I2C_slave_init()
{
	I2C_setCallbacks(I2C_received, I2C_requested);					// set received/requested callbacks
	i2c_init(I2C_ADD);
}


void send_latitdue(void)
{
	i2c_transmit_data(10);
}
void send_logtitude(void)
{
	i2c_transmit_data(20);
}
void send_age_of_data(void)
{
	i2c_transmit_data(30);
}
void send_quality(void)
{
	i2c_transmit_data(40);
}
void send_direction(void)
{
	i2c_transmit_data(50);
}
void send_velocity(void)
{
	i2c_transmit_data(60);
}

*/
