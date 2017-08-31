/*	
	File:   message.h
	Author: Courteney Brownie (cjb261) and Sara Dyson (sed65)
	Date:   13 Oct 2016
	Descr:	Module runs the message calls
*/

#ifndef MESSAGE_H
#define MESSAGE_H

#include "system.h"

void text_init(void);
void start_message(void);
void points_message(uint8_t my_score);
void display_message(void);
void text_nonscroll_init(void);
void text_scroll_init(void);
void results_message(char result);

#endif
