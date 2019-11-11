/*
 * PWM_init.h
 *
 * Created: 9/30/2019 11:09:04 AM
 *  Author: Red
 */ 


#ifndef PWM_INIT_H_
#define PWM_INIT_H_


uint8_t	M_Direc;
uint8_t M1_DutyCycle;
uint8_t M2_DutyCycle;


void T0_init(void);

void T1_init(void);

void T2_init(void);

void SetDrive(uint8_t M1_DutyCycle, uint8_t M2_DutyCycle , uint8_t M_direc);



#endif /* PWM_INIT_H_ */