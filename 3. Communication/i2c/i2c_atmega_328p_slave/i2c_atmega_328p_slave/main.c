 #define F_CPU 16000000UL											//Freq of microcontroller
 #include <avr/io.h>
 #include <stdio.h>
 #include <util\delay.h>
 #include "usart.h"
 #include "i2c_atmega_328p_slave.h"									//here we used i2c slave lib
 #define I2C_ADDR 0x40												//make slave address as 0x10
 

int main()
{
	 

uart_init();
io_redirect();	
i2c_disable();

_delay_ms(5000);

	while(1)
	{
		
		i2c_init(I2C_ADDR);

		_delay_ms(960);
		
		//i2c_init(I2C_ADDR);
		i2c_disable();
		
		_delay_ms(40);
		
		
		data2++;
		//printf("Internal: %d\n", data2);		
	}
}


