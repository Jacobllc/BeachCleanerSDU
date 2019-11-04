
/* GPS.c
* Created: 10/28/2019 11:15:13 AM
*  Author:  Hörður Hermannsson
*/

#include "GPS.h"
#include "NMEA_DECODER.h"
#include "i2c_atmega_328p_slave.h"



volatile uint8_t byte = 0;		// What byte is being worked with
volatile uint8_t package=0;
volatile uint8_t print_flag=1;
volatile uint8_t process=0;

typedef struct{
char length;
char data[80];
} GPS;

GPS Gps_data[Nr_msg];

void GPS_init(void)
{				
	DDRD &= ~(1 << DDD2);	             // PD2 set as input
	PORTD |= (0 << PORTD2);				 // turn OFF the Pull-up
	EIMSK |= (1<<INT0);
	EICRA |= (1 << ISC00)| (1 << ISC01); // set INT0 to trigger on falling edge logic change
	sei();								 // turn on interrupts
}


void check_gps_data(void)
{
	if (process==1)
	{
		if (UDR0=='\n')
		{
			Gps_data[package].length=byte;
			package++;
			byte=-1;
		}
		else
		{
			Gps_data[package].data[byte]=UDR0;
			byte++;
		}


		if (package>=Nr_msg)
		{
			stop_gps_sample();
		}
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

	usart_send('\r');
	usart_send('\n');
	
}

}
print_flag=1;
}


void I2C_received(uint8_t received_data)							//isr on receiving a byte on i2c
{

										
}

void I2C_requested(void)												//if master request data from slave
{
	
//	i2c_transmit_data(data);
}

void setup()
{
	I2C_setCallbacks(I2C_received, I2C_requested);					// set received/requested callbacks
	i2c_init(I2C_ADD);
}



ISR(INT0_vect)
{
process=1;
package=0;
byte=-1;
}