/*	
	File:   player.c
	Author: Courteney Brownie (cjb261) and Sara Dyson (sed65)
	Date:   13 Oct 2016
	Descr:  A file that contains a function to create a frog and functions that
			checks if the frog has been hit by car and resets the position. 
			The frog also keeps track of the score.
*/

#include "system.h"
#include "struct.h"
#include "traffic.h"

#define FROG_INIT_COL 2
#define FROG_INIT_ROW 6
#define FROG_END_ROW 0
#define FROG_CENTER_COL 2

// Initilizes a frog called Fregg
void init_player(Player * frog)
{
    frog->current.col = FROG_INIT_COL;
    frog->current.row = FROG_INIT_ROW;
    frog->previous.col = FROG_INIT_COL;
    frog->previous.row = FROG_INIT_ROW;
    frog->last_home = FROG_INIT_ROW;
}

// A function that checks if the frog and a car is at the same position
int position_equal(Position * pos1, Position * pos2)
{
    return (pos1->col == pos2->col) && (pos1->row == pos2->row);
}

// A function that checks that if our frog has been hit by a car. returns 1 on true, 0 on false
int run_over(Vehicle * cars, Player * frog)
{
    int i = 0;
    for (i = 0; i < MAX_VEHICLES; ++i) {
		if (EXISTS(cars[i])) {
			int small = position_equal(&(cars[i].current), &(frog->current));       //front of the car or if the car is of size one (small)
			Position back = {cars[i].current.col + (cars[i].current.row == CENTER_LANE ? 1 : -1),
							 cars[i].current.row };
			int large = cars[i].length != 1
				&& position_equal(&back, &(frog->current));
			if (small || large) {
				return 1;
			}
		}
    }
    return 0;
}

// If frog is hit, then frog is reset back to starting position. 
void penalty(GameState * game)
{
    game->frog.current.col = FROG_CENTER_COL;
    game->frog.current.row = game->frog.last_home;

}

// A function that returns the score of the frog.
void check_player_scored(GameState* game)
{
	if ((game->frog.last_home == FROG_END_ROW && game->frog.current.row == FROG_INIT_ROW) || 
		(game->frog.last_home == FROG_INIT_ROW && game->frog.current.row == FROG_END_ROW)) {
		game->my_score += 1;
		game->frog.last_home = game->frog.current.row;
	}
}
