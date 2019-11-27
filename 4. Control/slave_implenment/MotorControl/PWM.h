/*
 * PWM_init.h
 *
 * Created: 9/30/2019 11:09:04 AM
 *  Author: Red
 */ 


#ifndef PWM_INIT_H_
#define PWM_INIT_H_

//								i2C value

char sortState;

//								Global Variables for motor control 
volatile int TimerCounter;



//								Motor Control Functions
void T0_init(void);

void T1_init(void);

void T2_init(void);

void TimersInit(void);

void SetDrive(double M1_DutyCycle, double M2_DutyCycle);

void CalculatePwm(uint8_t error, uint8_t Zone);

void Sorting(char sortState);

void StartDrive(void);

void StopDrive(void);



#endif /* PWM_INIT_H_ */