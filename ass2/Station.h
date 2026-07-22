// COMP2521 - Assignment 2
// Interface to the Station ADT

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef STATION_H
#define STATION_H

#include <stdbool.h>

#define NO_CORRIDOR 0

struct corridor {
	int fromRoom;
	int toRoom;
	int travelTime;
};

typedef struct station *Station;

// Creates a new station with the given number of rooms and no corridors.
// Assumes numRooms is positive.
Station StationNew(int numRooms);

// Frees all memory allocated to the station.
void StationFree(Station s);

// Returns the number of rooms in the station.
int StationNumRooms(Station s);

// Returns the number of corridors in the station.
int StationNumCorridors(Station s);

// Sets the name of the given room. If the room already has a name, it is
// replaced. Assumes room and name are valid.
void StationSetRoomName(Station s, int room, char *name);

// Returns the name of the given room, or "unnamed" if no name has been set.
// The returned string must not be modified or freed by the caller.
char *StationGetRoomName(Station s, int room);

// Marks the given room as containing an escape pod. Does nothing if the room
// already contains an escape pod.
void StationSetEscapePod(Station s, int room);

// Returns true if the given room contains an escape pod, and false otherwise.
bool StationHasEscapePod(Station s, int room);

// Inserts a bidirectional corridor between two rooms with the given travel time.
// Does nothing if a corridor already exists between the two rooms.
// Assumes the rooms are valid and different, and travelTime is positive.
void StationInsertCorridor(Station s, int room1, int room2, int travelTime);

// Returns the travel time of the corridor between two rooms, or NO_CORRIDOR if
// no such corridor exists.
int StationContainsCorridor(Station s, int room1, int room2);

// Stores all corridors from the given room in the corridors array and returns
// the number of corridors stored. The corridors must be sorted by toRoom.
// Assumes the corridors array is large enough to store all corridors.
int StationGetCorridorsFrom(Station s, int room, struct corridor corridors[]);

// Displays the station in a textual format.
void StationShow(Station s);

#endif
