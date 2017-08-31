/*	
	File:   matrix.h
	Author: Courteney Brownie (cjb261) and Sara Dyson (sed65)
	Date:   13 Oct 2016
	Descr:  Module runs the matrix calls
*/

#ifndef MATRIX_H
#define MATRIX_H

#include "system.h"
#include "struct.h"
#include "traffic.h"

void maxtrix_config(void);
void matrix_display(GameState* game);
void move_frog(Player * frog, char direction);
void clear_board (void);
void draw_car(Vehicle * car);

#endif
