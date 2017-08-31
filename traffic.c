/*
	File:   traffic.c
	Author: Courteney Brownie (cjb261) and Sara Dyson (sed65)
	Date:   11 Oct 2016
	Descr:  A file that generates randomised traffic for the frog to navigate and moves 
			the vechiles along. 
			The first and last lane of the traffic run from left to right and middle lane
			runs right to left.  
*/

#include "traffic.h"
#include "timer.h"
#include "struct.h"

// definitiond of the row[0] and row[6]
#define FAR_ROW 4
#define NEAR_ROW 0

// returns an integer such that the first three bits indicate the truth value of the relevant lanes
// ie 0 is the first lane; 1 is the third lane and 2 is the 5th lane.
int valid_lanes(Vehicle* cars) {
	int lanes = 7; // 111, all lanes valid
	int i = 0;
	for (i = 0; i < MAX_VEHICLES; ++i) {
		if (EXISTS(cars[i])) {
			if (cars[i].current.row == 1) {
				if ((cars[i].current.col < 2 && cars[i].length == 1) ||
					(cars[i].current.col < 3 && cars[i].length == 2)) lanes &= ~1; // 1st bit false if car within 1 led of the end
			} else if (cars[i].current.row == 3) {
				if ((cars[i].current.col > 2 && cars[i].length == 1) ||
					(cars[i].current.col > 1 && cars[i].length == 2)) lanes &= ~2; // 2nd bit false if car within 1 led of the end
			} else if (cars[i].current.row == 5) {
				if ((cars[i].current.col < 2 && cars[i].length == 1) ||
					(cars[i].current.col < 3 && cars[i].length == 2)) lanes &= ~4; // 3rd bit false if car within 1 led of the end
			}
		}
	}
	return lanes;
}

// fills in a vehicle struct pointed to by car, assuming v_lanes has a valid lane
void fill_vehicle(Vehicle* car, int v_lanes)
{
	srand(timer_get());
	car->length = (rand() % MAX_CAR_LENGTH) + 1; //random number generator between 1 and 2
	int lane; 									// random lane index between 0 and 2
	do {										// block until valid lane stumbled upon 	
		lane = (rand() % NUM_VEHICLE_LANES);
	} while (!((1 << lane) & v_lanes));
	lane = CONVERT_LANE_INDEX(lane); // convert lane between 0 and 2, to 1, 3 or 5
	car->current.row = lane;
	car->current.col = lane == CENTER_LANE ? FAR_ROW : NEAR_ROW; // column is 0 unless row is 3, where column is 4
	car->previous.row = lane;
	car->previous.col = car->current.row; //set previous and current for each vehicle
}

// This will attempt to create a vehicle within the cars list
// returns 0 on success, -1 on no car space left, -2 on no valid lane space
int generate_vehicle(Vehicle* cars)
{
	int v_lanes = valid_lanes(cars);
	if (v_lanes) { // checks if there is at least one lane is valid.
		int i = 0;
		for (i = 0; i < MAX_VEHICLES; ++i) { // loop through all the vehicles looking for empty space
			if (!EXISTS(cars[i])) {
				fill_vehicle(cars+i, v_lanes);
				return 0; // success
			}
		}
		return NOSPACE; // no space for a car
	}
	return NOLANE; // no valid lane
}


// initialises the vehicles list to be full of zero length cars (empty)
void init_vehicles(Vehicle* cars)
{
	int i = 0;
	for (i = 0; i < MAX_VEHICLES; ++i) {
		cars[i].length = 0; // initialize all to zero to begin with
	}
}

int is_valid_position(Position* pos) {
	return pos->col >= 0 && pos->col < 5 && pos->row >= 0 && pos->row < 7;
}

// move a car forward.
void move_car(Vehicle* car) {
	car->previous.col = car->current.col; // update previous to current
    car->previous.row = car->current.row;
    car->current.col += car->current.row == 3 ? -1 : 1; // increment car position if not in col 3, else decrement
    if (!is_valid_position(&car->current)) { // if the new position is invalid
		car->current.row = car->previous.row; // move the car back to a valid position
		car->current.col = car->previous.col;
		--car->length; // decrease car length
	}
}

// A function that updates the position of the cars (if it exsists) 
void update_traffic(Vehicle* cars)
{
	int i = 0;
	for (i = 0; i < MAX_VEHICLES; ++i) { // loop through all the cars
		if (EXISTS(cars[i])) { // if the car exists
			move_car(&cars[i]); // update position of the car
			//draw_car(cars[i]); // draw the car (comment out to unlock animation from framerate)
		}
	}
}
