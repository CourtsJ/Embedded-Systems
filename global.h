/*	
	File:   global.h
	Author: Courteney Brownie (cjb261) and Sara Dyson (sed65)
	Date:   13 Oct 2016
	Descr:  Header file which contains the global variables used across 
			different .c files.

*/

#ifndef GLOABL_H
#define GLOBAL_H

//Global functions used for time and unint 
#define MAX_UINT_8 255
#define MAX_UINT_16 65535
#define GAME_LENGTH 5000
#define GAME_SPEED 300

//Global functions used for post-game messages
#define LOSER 'L'
#define WINNER 'W'
#define DRAW 'D'

#define RESULT_SCREEN 'R'
#define SCORE_SCREEN 'S'      

//Global functions used for the nav-switch 
#define PRESSED 'P'
#define UNDIRECTED 'U' 
#define SOUTH 'S'
#define NORTH 'N'
#define EAST 'E'
#define WEST 'W'

#endif
