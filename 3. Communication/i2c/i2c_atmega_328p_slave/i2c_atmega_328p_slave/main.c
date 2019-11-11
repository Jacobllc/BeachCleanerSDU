 #define F_CPU 16000000UL											//Freq of microcontroller
 #include <avr/io.h>
 #include <stdio.h>
 #include "usart.h"
 #include "i2c_atmega_328p_slave.h"									//here we used i2c slave lib
 #define I2C_ADDR 0x40												//make slave address as 0x10

 volatile uint8_t data;
 volatile uint8_t data2;												//declare volatile variable to use in isr routines

 void I2C_received(uint8_t received_data)							//isr on receiving a byte on i2c
 {

 data = received_data;
 data2=2+data;													//received data
 printf("%d\n",data);											//printing to lcd
 }

 void I2C_requested()												//if master request data from slave
 {
 
 i2c_transmit_data(data2);
 }

 void i2cslave_init()
 {
	 
 I2C_setCallbacks(I2C_received, I2C_requested);					// set received/requested callbacks
 i2c_init(I2C_ADDR);
 }

 int main()
 {
	 
 i2cslave_init();														//in this we only print the received data and echo it back when data is requested from master
 uart_init();
 io_redirect();
 
 
 
 while(1);
 }


