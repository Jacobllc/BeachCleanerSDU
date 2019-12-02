/*
 * set_up.h
 *
 * Created: 06/11/2019 12.47.10
 *  Author: chalo
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#ifndef SET_UP_H_
#define SET_UP_H_

uint8_t zone; 
volatile int av_distance_array[4];


void init_io(void);
void init_timers(void);

int getdist1(void);
int getdist2(void);
int getdist3(void);
int getdist4(void);
void min_dist(int dis);


#endif /* SET_UP_H_ */