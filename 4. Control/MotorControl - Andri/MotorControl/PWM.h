/*
 * PWM_init.h
 *
 * Created: 9/30/2019 11:09:04 AM
 *  Author: Red
 */ 


#ifndef PWM_INIT_H_
#define PWM_INIT_H_



//								i2C value


char new_data;
char status;
int error;
uint8_t zone;
char sortState;

//								Global Variables for motor control 



//								Motor Control Functions
void T0_init(void);

void T1_init(void);

void T2_init(void);

void TimersInit(void);

 
void PWM_init(void);

void set_pwm(int value);

void change_pwm_slow(void);

void change_pwm_fast(void);

void motor_handler(void);

void CalculatePwm(int error);


void startup_sort(void);
void stop_sort(void);
void turn_right(void);
void turn_left(void);
void Drive_forward(void);
void Drive_backward(void);


#endif /* PWM_INIT_H_ */