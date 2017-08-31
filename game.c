/*	
	File:   game.c
	Author: Courteney Brownie (cjb261) and Sara Dyson (sed65)
	Date:   13 Oct 2016
	Descr:  functions that help run the game (crossing the road)
*/

#include "system.h"
#include "struct.h"
#include "player.h"
#include "navigation.h"
#include "traffic.h"
#include "matrix.h"
#include "game.h"
#include "global.h"

//initialises functions in relation to the game
void init_game(GameState* game) 
{
	game->car_speed = 0;
	game->my_score = 0;
	game->op_score = MAX_UINT_8;
	init_vehicles(game->vehicles);
	init_player(&game->frog);
}

//calls functions that runs the game in order
void run_game(GameState* game) 
{
	move_frog(&(game->frog), game->direction);
	matrix_display(game);
	navigation_update();
	generate_vehicle(game->vehicles);
	game->direction = get_movement();
	game->car_speed = (game->car_speed + 1) % GAME_SPEED;  //change back to 300
	if (game->car_speed==0) update_traffic(game->vehicles);
	if (run_over(game->vehicles, &game->frog)) penalty(game);
	check_player_scored(game);
}

//Calculates the results of the game
int game_result(uint8_t op_score, uint8_t my_score){
	char result;
	if (op_score > my_score) {
		result = LOSER;
	}
	
	else if (my_score > op_score) {
		result = WINNER;
	}
	
	else {
		result = DRAW;
	} 
	return result;
}
