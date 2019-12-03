/*
 * MACROS.c
 *
 * Created: 10/2/2019 1:01:53 PM
 *  Author: Red
 */ 


#include <avr/io.h>
#include "MACROS.h"

//----- I/O Macros -----


void IO_init(void){	///////////////////////// Initial Pin Setup
	
	// bit order 7 6 5 4 3 2 1 0
	DDRB  = 0b00001011;
	PORTB = 0b00000000;
	
	DDRC  = 0b00000000;
	PORTC = 0b00000000;
	
	DDRD  = 0b11101000;
	PORTD = 0b00000000;
}
