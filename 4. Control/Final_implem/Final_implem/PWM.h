/*
 * PWM_init.h
 *
 * Created: 9/30/2019 11:09:04 AM
 *  Author: Red
 */ 


#ifndef PWM_INIT_H_
#define PWM_INIT_H_



//								i2C value



//								Global Variables for motor control 



//								Motor Control Functions
void T0_init(void);

void T1_init(void);

void T2_init(void);

void TimersInit(void);

 
void Motor_init(void);

void set_pwm(int value);
void print_pwm(void);

void change_pwm_sort(void);

void change_pwm_drive(void);

void motor_handler(void);

void CalculatePwm(int error);


void startup_sort(void);
void stop_sort(void);
void turn_right(void);
void turn_left(void);
void Drive_forward(void);
void Drive_backward(void);


#endif /* PWM_INIT_H_ */