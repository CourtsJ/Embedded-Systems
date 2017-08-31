/*	
	File:   navigation.h
	Author: Courteney Brownie (cjb261) and Sara Dyson (sed65)
	Date:   11 Oct 2016
	Descr:  Module runs the navigation calls

*/

#ifndef NAVAIGATION_H
#define NAVAIGATION_H

#include "system.h"
#include "global.h"

void navigation_init (void);
void navigation_update (void);
char get_movement(void);

#endif
