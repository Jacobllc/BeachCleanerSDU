/*
 * ...
 *
 * Created: 9/26/2019 8:30:44 PM
 *  Author: Red
 */ 

#include <avr/io.h>
#include "PinSetup.h"
#include <avr/sfr_defs.h>



//						IO Setup
void IO_init(void){	
		
		// bit order 7 6 5 4 3 2 1 0
		DDRB  = 0b00001110;
		PORTB = 0b00000000;
		
		DDRC  = 0b00000000;
		PORTC = 0b00000000;
		
		DDRD  = 0b01101000;
		PORTD = 0b00000000;			
}