 #define F_CPU 16000000UL											//Freq of microcontroller
 #include <avr/io.h>
 #include <stdio.h>
 #include "usart.h"
 #include "i2c_atmega_328p_slave.h"									//here we used i2c slave lib
 #define I2C_ADDR 0x40												//make slave address as 0x10

											


 int main()
 {
	 
 i2c_init(I2C_ADDR);														//in this we only print the received data and echo it back when data is requested from master
 uart_init();
 io_redirect();
 
 
 
 while(1);
 }


