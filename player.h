/*	
	File:   player.h
	Author: Courteney Brownie (cjb261) and Sara Dyson (sed65)
	Date:   11 Oct 2016
	Descr:  Module runs the player calls

*/

#ifndef PLAYER_H
#define PLAYER_H

#include "system.h"
#include "struct.h"
#include "traffic.h"

void init_player(Player* frog);
int run_over(Vehicle* cars, Player* frog);
void penalty(GameState* game);
void check_player_scored(GameState* game);

#endif	
