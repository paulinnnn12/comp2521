// COMP2521 - Assignment 2
// Interface to evacuation algorithms

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef EVACUATION_H
#define EVACUATION_H

#include "Station.h"

struct reachableRoomsResult {
	int numRooms;
	int *rooms; // dynamically allocated array of room IDs in ascending order
};

struct route {
	int fromRoom;
	int toRoom;
	int totalDuration;
	int numRooms;
	int *rooms; // dynamically allocated array containing the path of room IDs
};

struct blockedCorridor {
	int roomA;
	int roomB;
};

// Task 2
struct reachableRoomsResult reachableRooms(Station s);

// Task 3
struct route fastestEscape(Station s, int fromRoom);

// Task 4
struct route fastestEscapeAvoiding(Station s, int fromRoom,
		struct blockedCorridor blocked[], int numBlocked);

#endif

