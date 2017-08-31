/*	
	File:   time.c
	Author: Courteney Brownie (cjb261) and Sara Dyson (sed65)
	Date:   13 Oct 2016
	Descr: Functions that help create game length 
*/

#include "system.h"
#include "timer.h"
#include "time.h"
#include "global.h"

//Calculates time, ensures that time has not overflown, converts ticks to milliseconds
void time_diff(Timer* time) { 										
    timer_tick_t current = timer_get(); 							
    int diff;															
    if (current >= time->last) { 										
        diff = current - time->last; 									
    } else { 															 
        diff = (MAX_UINT_16 - (int) time->last) + (int) current;
    }
	int rem = time->ms - ((diff * 100) / ((float) TIMER_RATE)); 					
    time->ms = rem > 0 ? rem : 0; 									
}

//Gets duration in milliseconds and current time in ticks
void init_time(Timer* time, int ms) {
    time->ms = ms;
    time->last = timer_get(); 
}
