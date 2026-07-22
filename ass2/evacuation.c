// COMP2521 - Assignment 2
// Implementation of evacuation algorithms

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "evacuation.h"
#include "Station.h"

struct reachableRoomsResult reachableRooms(Station s) {
	// TODO: Task 2
	struct reachableRoomsResult res = {0, NULL};
	return res;
}

struct route fastestEscape(Station s, int fromRoom) {
	// TODO: Task 3
	struct route route = {fromRoom, -1, 0, 0, NULL};
	return route;
}

struct route fastestEscapeAvoiding(Station s, int fromRoom,
		struct blockedCorridor blocked[], int numBlocked) {
	// TODO: Task 4
	struct route route = {fromRoom, -1, 0, 0, NULL};
	return route;
}

