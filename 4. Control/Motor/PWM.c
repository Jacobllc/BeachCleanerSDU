/*
 * PWM_init.c
 *
 * Created: 9/30/2019 11:09:44 AM
 *  Author: Red
 *
 *	All PWM signals should be as close to 15kHz as possible
 *
 *
 *
 *
 */ 

 #define F_CPU 16000000UL
 #include <stdio.h>
 #include <avr/io.h>
 #include <util/delay.h>
 #include "PWM.h"
 #include "MACROS.h"
 
 #define MPWM_MAX 100
 #define MPWM_MIN 20
 double M1_DutyCycle_n;
 double M2_DutyCycle_n;
 double M1_DutyCycle = MPWM_MIN;
 double M2_DutyCycle = MPWM_MIN;
 char kp_1 = 0.4;
 char kp_2 = 0.4;
 
 char sortState = 0;

//////////////////////         Timer0 Setup 
void T0_init(void){
		TCCR0A |= (1 << WGM00) | (1 << WGM01);  // set Timer0 to 8bit fast PWM mode
		TCCR0A |= (1 << COM0A1);			    // set OC0A to non-inverting mode
		TCCR0A |= (1 << COM0B1);			    // set OC0B to non-inverting mode
		TIMSK0 |= (1 << TOIE0) ;		
		OCR0A = 254; //duty cycle OCR0A PIN6
		OCR0B = 254;//duty cycle OCR0B PIN5
		TCCR0B |= (1 << CS00) | ( 1 << CS02 );				   // set pre scaler to 1024 12.5 kHz
}


//////////////////////         Timer1 Setup 
void T1_init(void){
		TCCR1A |= (1<<WGM12) | (1<<WGM11) | (1<<WGM10);   // set Timer1 to 16bit fast PWM mode TCCR1A max value 1023
		TCCR1A |= (1 << COM1A1);
		TCCR1A |= (1 << COM1B1);
		TIMSK1 |= (1 << TOIE1 );
		OCR1A = 254;  //duty cycle OCR0A PIN13
		//OCR1B = 254;  //duty cycle OCR0B PIN14
		TCCR1B |= (1<<CS11 ) | (1 << CS10);				  // set pre-scaler to 64 FREQ - 14.7kHz

	
}


//////////////////////         Timer2 Setup 
void T2_init(void){
		TCCR2A |= (1 << WGM21) | (1 << WGM20);	// Time2 to 8bit fast PWM mode
		TCCR2A |= (1 << COM2A1);			    // set OC2A to non-inverting mode
		TCCR2A |= (1 << COM2B1);			    // set OC2B to non-inverting mode
		TIMSK2 |= (1 << TOIE2 );
		//OCR2A =  255;
		//OCR2B = 255;
		TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);					// set pre-scaler to 1024 - 12.5 kHz
}
			

void TimersInit(void){
		T0_init();     //
		T1_init();	   //
		T2_init();     //
	
}
		
//////////////////////         Motor functions

void StopDrive(void){
	
	M1_DutyCycle = 0;
	M2_DutyCycle = 0;
	sortState = 0;
	Sorting(sortState);
	SetDrive(M1_DutyCycle, M2_DutyCycle);
	
	
}



void Sorting(char sortState){
	
	if(sortState == 1){
		OCR0A = 255;
		OCR0B = 255;
		OCR1A = 255;	
	}
	
	if(sortState == 0){
		OCR0A = 0;
		OCR0B = 0;
		OCR1A = 0;
		
	}
	
}

void CalculatePwm(uint8_t error, uint8_t Zone){
	
	switch(Zone){
		case 1:
		M1_DutyCycle_n = 100 - kp_1 * error;
		M2_DutyCycle_n = 100 - kp_2 * error;
		break;
		
		case 2:
		M1_DutyCycle_n = 70 - kp_1 * error;
		M2_DutyCycle_n = 70 - kp_2 * error;
		break;
		
		case 3:
		StopDrive();
		break;
	}
}

void StartDrive(void){
	
	PinState(pd7, high);			// H-Bridge Enable pin Motor 1
	PinState(pb0, high);		// H-Bridge Enable pin Motor 2
	
	while(M1_DutyCycle < 100 && M2_DutyCycle < 100){
		M1_DutyCycle += 10;
		M2_DutyCycle += 10;
		OCR2A =  (M1_DutyCycle/100)*254;			// DubyCycle Motor 1
		OCR2B =  (M2_DutyCycle/100)*254;			// DutyCycle Motor 2
		_delay_us(1);
	
	}
}


void SetDrive(double M1_DutyCycle, double M2_DutyCycle){
		
			if(M1_DutyCycle < MPWM_MIN)
			{
				M1_DutyCycle = MPWM_MIN;
			}
			
			if (M2_DutyCycle < MPWM_MIN)
			{
				M2_DutyCycle = MPWM_MIN;
			}
			
						if(M1_DutyCycle < 0)
						{
							M1_DutyCycle = 0;
						}
						
						if (M2_DutyCycle < 0)
						{
							M2_DutyCycle = 0;
						}
						
			if((error > 90) || (error < -90)){
//								   Turning ... 				
							if(error > 90){
								PinState(pd7, low);							 // H-Bridge Enable pin Motor 1
								PinState(pb0, low);							 // H-Bridge Enable pin Motor 2
								OCR2A =  (M1_DutyCycle/100)*254;			// DubyCycle Motor 1
								OCR2B =  (M2_DutyCycle/100)*254;			// DutyCycle Motor 2
							}
//									Turning ... 
									if(error < -90){
									PinState(pd7, high);							 // H-Bridge Enable pin Motor 1
									PinState(pb0, high);							 // H-Bridge Enable pin Motor 2
									OCR2A =  (M1_DutyCycle/100)*254;			// DubyCycle Motor 1
									OCR2B =  (M2_DutyCycle/100)*254;			// DutyCycle Motor 2
														}

			}
			

//									Turning ...
								PinState(pd7, low);							 // H-Bridge Enable pin Motor 1
								PinState(pb0, low);							 // H-Bridge Enable pin Motor 2
								OCR2A =  (M1_DutyCycle/100)*254;			// DubyCycle Motor 1
								OCR2B =  (M2_DutyCycle/100)*254;			// DutyCycle Motor 2								


		/*									L298 H-Bridge 
		//  Break
		if(M_Direc == 0b0000){
		PinState(pd4, low);  // L298 in1
		PinState(pd7, low);  // L298 in2
		PinState(pb0, low);  // L298 in3
		PinState(pb4, low);  // L298 in4
				printf("Direc Break Set \n");
		}
			
		//  Forward
		if(M_Direc == 0b0101){ // 0101
		PinState(pd4, low);  // L298 in1
		PinState(pd7, high);  // L298 in2
		PinState(pb0, low);  // L298 in3
		PinState(pb4, high);  // L298 in4
				printf("Direc Forward Set \n");
		}
		
		// Turn - ?
		if(M_Direc == 0b0110){   // 0110
		PinState(pd4, low);  // L298 in1
		PinState(pd7, high);  // L298 in2
		PinState(pb0, high);  // L298 in3
		PinState(pb4, low);  // L298 in4
				printf("Direc Turn 1 Set \n");
		}
		
		
		// Turn - ?
		if(M_Direc == 0b1001){  // 1001
		PinState(pd4, high);  // L298 in1
		PinState(pd7, low);  // L298 in2
		PinState(pb0, low);  // L298 in3
		PinState(pb4, high);  // L298 in4
				printf("Direc Turn 2 Set \n");
		}

		//  Backward
		if(M_Direc == 0b1010){ // 1010
		PinState(pd4, high);  // L298 in1
		PinState(pd7, low);  // L298 in2
		PinState(pb0, high);  // L298 in3
		PinState(pb4, low);  // L298 in4
				printf("Direc Set \n");
		}
		*/

			}

/*


///////////////             PWM PINS
Nr		Register		PORTnx			State				Timerx
3		OC2B			PORTD3			DDRD3/Output		Timer2
5		OC0B			PORTD5			DDRD5/Output		Timer1
6		OC0A			PORTD6			DDRD6/Output		Timer0
9		OC1A			PORTB1			DDRB1/Output		Timer0
10		OC1B			PORTB2			DDRB2/Output		Timer1
12		OC2A			PORTB3			DDRB2/Output		Timer2


////////////////			Prescaler Settings
			CA02	CA01	CS00
			0		0		0		Prescaler = Timer Stopped
			0		0		1		Prescaler =	1
			0		1		0		Prescaler = 8
			0		1		1		Prescaler = 64
			1		0		0		Prescaler = 256
			1		0		1		Prescaler = 1024
			1		1		0		Prescaler = external clk T0 pin Falling edge
			1		1		1		Prescaler = external clk T0 Pin Rising edge
			
			
//						TIMER0 Counter
//			OCR0A = 128;					       // duty cycle OCR0A PD6
//			OCR0B = 255;						   // duty cycle OCR0B PD5
//						TIMER1 Counter
//			OCR1A = 255;					      // duty cycle OCR1A PB1
//			OCR1B = 255;						  // duty cycle OCR1B PB2
//						TIMER2 Counter
//			OCR2A = 255;					      // duty cycle OCR2A PD3
//			OCR2B = 255;					      // duty cycle OCR2B PB3


*/ 
