/*	
	File:   time.h
	Author: Courteney Brownie (cjb261) and Sara Dyson (sed65)
	Date:  11 Oct 2016
	Descr: Module runs the time calls

*/

#ifndef TIME_H
#define TIME_H

#include "system.h"
#include "timer.h"
#include "time.h"

typedef struct timer_s {
    int ms; 
    timer_tick_t last;
} Timer;

void time_diff(Timer* time);
void init_time(Timer* time, int ms);

#endif

