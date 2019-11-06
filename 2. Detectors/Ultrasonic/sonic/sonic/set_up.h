/*
 * set_up.h
 *
 * Created: 06/11/2019 12.47.10
 *  Author: chalo
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>

#ifndef SET_UP_H_
#define SET_UP_H_

void init_io(void);
void init_timers(void);

float getdist1(void);
float getdist2(void);
float getdist3(void);
float getdist4(void);
void min_dist(int dis);


#endif /* SET_UP_H_ */