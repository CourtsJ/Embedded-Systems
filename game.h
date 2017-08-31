/*	
	File:   game.h
	Author: Courteney Brownie (cjb261) and Sara Dyson (sed65)
	Date:   13 Oct 2016
	Descr:  Module runs the game calls

*/

#ifndef GAME_H
#define GAME_H

#include "system.h"
#include "struct.h"
#include "player.h"
#include "navigation.h"
#include "traffic.h"
#include "matrix.h"
#include "global.h"

void init_game(GameState* game);
void run_game(GameState* game);
int game_result(uint8_t op_score, uint8_t my_score);
#endif
