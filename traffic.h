/*	
	File:   traffic.h
	Author: Courteney Brownie (cjb261) and Sara Dyson (sed65)
	Date:  11 Oct 2016
	Descr: Module runs the traffic calls

*/

#ifndef TRAFFIC_H
#define TRAFFIC_H

#include "system.h"
#include "struct.h"
#include <stdlib.h>

#define NOLANE -2
#define NOSPACE -1
#define MAX_CAR_LENGTH 2
#define NUM_VEHICLE_LANES 3
#define CENTER_LANE 3
#define CONVERT_LANE_INDEX(x) 2*x + 1
#define EXISTS(car) car.length > 0

int generate_vehicle(Vehicle* cars);
void init_vehicles(Vehicle* cars);
void update_traffic(Vehicle* cars);

#endif
