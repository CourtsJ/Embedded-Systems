/*	
	File:   struct.h
	Author: Courteney Brownie (cjb261) and Sara Dyson (sed65)
	Date:  11 Oct 2016
	Descr: Structs for position, vehicle, frog and the state of the game.

*/

#ifndef STRUCT_H
#define STRUCT_H

#define MAX_VEHICLES 6

//Struct for postions in the matrix
typedef struct position_s {
	int col;
	int row;
} Position;

//struct for vechile postion in the matrix
typedef struct vehicle_s {
	Position current;
	Position previous;
	int length;
} Vehicle;

//struct for player postion in the matrix
typedef struct player_s {
	Position current;
	Position previous;
	int last_home;
} Player;

//Struct for updates made during play
typedef struct gamestate_s {
	Vehicle vehicles[MAX_VEHICLES];
	Player frog;
	int car_speed;
	uint8_t my_score;
	uint8_t op_score;
	char direction;
} GameState;

#endif
