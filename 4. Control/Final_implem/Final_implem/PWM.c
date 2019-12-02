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
 #define rampslow_scale 100
 #define safty_scale 400
 
 #include <stdio.h>
 #include <avr/io.h>
 #include <util/delay.h>
 #include <avr/interrupt.h>
 #include "PWM.h"
 #include "MACROS.h"
 #include "Motor_i2c.h"
 
 #define Zone3_MAX_PWM  255
 #define Zone2_MAX_PWM  (255 * 0.7)
 #define MPWM_MIN 45
 #define ERROR_RIGHT 15
 #define ERROR_LEFT -15
 #define STEP ((PWM_MAX - MPWM_MIN)/(ERROR_RIGHT))
 
 volatile int PWM_MAX;

 
 typedef struct PWM_struct
 {
	 int desired_pwm_m1;
	 int desired_pwm_m2;		
	 int desired_pwm_m3;		// MOTOR LEFT
	 int desired_pwm_m4;		// MOTOR RIGHT
	 
	 
 }PWM_sturct;

 PWM_sturct Motor_pwm;
 
 
 char kp_1 = 0.4;
 char kp_2 = 0.4;
 
 char sortState = 0;

volatile int counter_rampslow=0;
volatile int counter_safety=0;
	
//////////////////////         Timer0 Setup 
void T0_init(void)
{
		TCCR0A |= (1 << COM0A1) | (0 << COM0A0); // set OC0A Clear OC0! on compare, sett OC0A at Bottom ( non inverting)
		TCCR0A |= (1 << COM0B1) | (0 << COM0B0); // set OC0B to non-inverting mode
		TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << WGM02);  // set Timer0 to 8bit fast PWM mode		
		OCR0A = 0; //duty cycle OCR0A PIND6		For motor 1 (motor left)
		OCR0B = 0;//duty cycle OCR0B PIND5		For motor 2 (motor right)
		TCCR0B |= (0 << CS00) | (1 << CS01) | (0 << CS02);			// 7.8kHz
		//TIMSK0 |= (1 << TOIE0);
}


//////////////////////         Timer1 Setup 
void T1_init(void)
{
		TCCR1A = 0;
		TCNT1 = 0;
		OCR1A = 3999;  //duty cycle OCR0A PIN13
		TCCR1B |= (0<<CS12) | (0<<CS11) | (1 << CS10) | (1 << WGM12);				  // set pre-scaler to 64 FREQ - 7.8kHz
		TIMSK1 |= (1 << OCIE1A );			
}


//////////////////////         Timer2 Setup 
void T2_init(void){
		TCCR2A |= (1 << COM2A1) | (0 << COM2A0);			    // set OC2A to non-inverting mode
		TCCR2A |= (1 << COM2B1)	| (0 << COM2B0);			    // set OC2B to non-inverting mode
		TCCR2A |= (1<<WGM22) | (1 << WGM21) | (1 << WGM20);	// Time2 to 8bit fast PWM mode
		OCR2A =  0;	//duty cycle OCR2A  PIND11   For motor 3 (motor PICKUP )
		OCR2B =  0;	//duty cycle OCR2B  PIND3     For motor 4 (motor ORGER )
		TCCR2B |= (0 << CS22) | (1 << CS21) | (0 << CS20);					// 7.8kHz
		//TIMSK2 |= (1 << TOIE2 );
}
			

void TimersInit(void){
		T0_init();     //
		T1_init();	   //
		T2_init();     //
	
}
		
//////////////////////         Motor functions


void Motor_init(void)
{
	Motor_pwm.desired_pwm_m1=0;
	Motor_pwm.desired_pwm_m2=0;
	Motor_pwm.desired_pwm_m3=0;
	Motor_pwm.desired_pwm_m4=0;
	
	PinState(pd4, low);
	
	
	
}


void set_pwm(int value)
{
		Motor_pwm.desired_pwm_m1=value;
		Motor_pwm.desired_pwm_m2=value;
		Motor_pwm.desired_pwm_m3=value;
		Motor_pwm.desired_pwm_m4=value;
}


void change_pwm_slow(void)
{
	
	if (Motor_pwm.desired_pwm_m1>OCR0A)
	{	
		if (OCR0A<MPWM_MIN)
		{
			OCR0A=MPWM_MIN;
		}
		else
		{
			OCR0A++;		
		}
	}
	
	if (Motor_pwm.desired_pwm_m1<OCR0A)
	{
		if (OCR0A>MPWM_MIN)
		{
			OCR0A--;
		}
		else
		{
			OCR0A=0;
		}
	}
	
	
	
	
	
	if (Motor_pwm.desired_pwm_m2>OCR0B)
	{
		if (OCR0B<MPWM_MIN)
		{
			OCR0B=MPWM_MIN;
		}
		else
		{
			OCR0B++;
		}
	}
	
	if (Motor_pwm.desired_pwm_m2<OCR0B)
	{
		if (OCR0B>MPWM_MIN)
		{
			OCR0B--;
		}
		else
		{
			OCR0B=0;
		}
	}
	
}

void change_pwm_fast(void)
{
	
	if (Motor_pwm.desired_pwm_m3>OCR2A)
	{
		if (OCR2A<MPWM_MIN)
		{
			OCR2A=MPWM_MIN;
		}
		else
		{
			OCR2A++;
		}
	}
		
	if (Motor_pwm.desired_pwm_m3<OCR2A)
	{
		if (OCR2A>MPWM_MIN)
		{
			OCR2A--;
		}
		else
		{
		OCR2A=0;
		}
	}
		
		
		
		
		
	if (Motor_pwm.desired_pwm_m4>OCR2B)
	{
		if (OCR2B<MPWM_MIN)
		{
			OCR2B=MPWM_MIN;
		}
		else
		{
			OCR2B++;
		}
	}
		
	if (Motor_pwm.desired_pwm_m4<OCR2B)
	{
		if (OCR2B>MPWM_MIN)
		{
			OCR2B--;
		}
		else
		{
			OCR2B=0;
		}
	}
	
}



void motor_handler(void)
{
	PWM_MAX = Zone3_MAX_PWM;
	
	switch(zone)
	{
	
	case 0:
		// Waiting for instruction from master
		StopDrive();
		stop_sort();
		break;
	
	case 1:
		StopDrive();
		// Do ADC calculation
		break;
		
	case 2:
		
		PWM_MAX = Zone2_MAX_PWM;
	
	case 3:	
		CalculatePwm(error);
		break;
		
	case 4:
		startup_sort();
		printf("sorting!!\n");
		break;		
	}
}



void CalculatePwm(int error)
{
	
if((error<=ERROR_RIGHT)&&(error>=ERROR_LEFT))
	{
		if ((PinRead(pd7)==0)||(PinRead(pb0)==1))
		{
		StopDrive();
		while((OCR2A)&&(OCR2B));		
		PinState(pd7, high);
		PinState(pb0, low);
		}
		
		if (error>=0)
		{
			Motor_pwm.desired_pwm_m3 = PWM_MAX - (STEP * error);
			Motor_pwm.desired_pwm_m4 = PWM_MAX;
			
		}
		
		if (error<=0)
		{
			Motor_pwm.desired_pwm_m4 =  PWM_MAX + (STEP * error);
			Motor_pwm.desired_pwm_m3 = PWM_MAX;
			
		}
		
		
		
	}
	
else
	{
	
		
		if (error>ERROR_RIGHT)
		{
			turn_left();
		}
		
		if (error<ERROR_LEFT)
		{
			turn_right();	
		}		
	}		
}
	
	
void startup_sort(void)
{
	PinState(pd4, high);
	
	Motor_pwm.desired_pwm_m1 = Zone3_MAX_PWM;
	Motor_pwm.desired_pwm_m2 = Zone3_MAX_PWM;
}

void stop_sort(void)
{
	Motor_pwm.desired_pwm_m1 = 0;
	Motor_pwm.desired_pwm_m2 = 0;
	
	PinState(pd4, low);
	
}

void StopDrive(void)
{
	Motor_pwm.desired_pwm_m3 = 0;
	Motor_pwm.desired_pwm_m4 = 0;	
}


void turn_right(void)
{
	
	if ((PinRead(pd7)==1)||(PinRead(pb0)==1))
		{
			StopDrive();
			while((OCR2A)&&(OCR2B));
	
			PinState(pd7, low);
			PinState(pb0, low);
		}
	Motor_pwm.desired_pwm_m3 = Zone3_MAX_PWM;
	Motor_pwm.desired_pwm_m4 = Zone3_MAX_PWM;	
}
void turn_left(void)
{
	if ((PinRead(pd7)==0)||(PinRead(pb0)==0))
		{
			StopDrive();
			while((OCR2A)&&(OCR2B));
	
			PinState(pd7, high);
			PinState(pb0, high);
		}
		
	Motor_pwm.desired_pwm_m3 = Zone3_MAX_PWM;
	Motor_pwm.desired_pwm_m4 = Zone3_MAX_PWM;
	
}

void Drive_forward(void)
{
		PinState(pd7, high);
		PinState(pb0, low);
	
	Motor_pwm.desired_pwm_m3 = Zone3_MAX_PWM;
	Motor_pwm.desired_pwm_m4 = Zone3_MAX_PWM;
}

void Drive_backward(void)
{
		PinState(pd7, low);
		PinState(pb0, high);
	
	Motor_pwm.desired_pwm_m3 = Zone3_MAX_PWM;
	Motor_pwm.desired_pwm_m4 = Zone3_MAX_PWM;
}


void print_pwm(void)
{
	printf("PWM m1 %d  PWM m2 %d  PWM m3 %d   PWM m4 %d\n",Motor_pwm.desired_pwm_m1, Motor_pwm.desired_pwm_m2,Motor_pwm.desired_pwm_m3, Motor_pwm.desired_pwm_m4);	
}



ISR(TIMER1_COMPA_vect)
{
	counter_rampslow++;
	
	if (zone!=1)
	{
		counter_safety++;
	}
	
	Toggle(pd2);
	
	if (counter_rampslow>rampslow_scale)
	{
		change_pwm_slow();
		change_pwm_fast();
		counter_rampslow=0;
	}
	

	if (counter_safety>safty_scale)
	{
		Toggle(pd2);	
	}
	
}


