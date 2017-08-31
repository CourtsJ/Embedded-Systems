/*	
	File:   navigation.c
	Author: Courteney Brownie (cjb261) and Sara Dyson (sed65)
	Date:   13 Oct 2016
	Descr:  functions that intilize and call the navigation switch.
*/

#include "system.h"
#include "global.h"
#include "navswitch.h"

// Navigation switch intilize
void navigation_init (void) {
	navswitch_init ();
}

// Updates the navigation switch
void navigation_update (void) {
	navswitch_update();
}

// Defines the movements.
char get_movement(void){
	char direction = UNDIRECTED;
	if (navswitch_push_event_p (NAVSWITCH_SOUTH)){
		direction = SOUTH;
	}
	if (navswitch_push_event_p (NAVSWITCH_NORTH)){
		direction = NORTH;
	}

	if (navswitch_push_event_p (NAVSWITCH_EAST)){
		direction = EAST;
	}
	
	if (navswitch_push_event_p (NAVSWITCH_WEST)){
		direction = WEST;
	}
	if (navswitch_push_event_p (NAVSWITCH_PUSH)){
		direction = PRESSED;
	}

	return direction;
}	
