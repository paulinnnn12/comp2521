// COMP2521 - 26T2 Assignment 2: Space Station Evacuation
// z5643770
// Written: 16/07 - 30/07  [check/update this date before submitting]
//
// Implementation of the Station ADT (see Station.h for the
// interface).
//
// A station is stored as an array of rooms, each holding a name and a
// flag for whether it contains an escape pod, plus a dynamically
// growing array of corridors. Each corridor is stored once as an
// unordered pair of rooms. StationGetCorridorsFrom builds a
// room-oriented view of the corridors connected to a given room on
// demand, sorted by the room at the other end.
//
// No known bugs or limitations.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Station.h"

struct room {
	char *name;
	bool escape;
};
typedef struct room Room;

struct station {
	Room *rooms;
	struct corridor *corridors;
	int numRooms;
	int numCorridors;
	int corridorCapacity;
};

// prototypes for helper functions
static void checkAlloc(void *ptr);
static int compareByToRoom(const void *a, const void *b);

// Prints an error message and exits if ptr is NULL, i.e. a malloc or
// realloc call has failed. Called after every allocation in this file.
static void checkAlloc(void *ptr) {
	if (ptr == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}
}

// Creates a new station with the given number of rooms and no
// corridors. All rooms start out unnamed and without an escape pod.
// Assumes that numRooms is positive.
Station StationNew(int numRooms) {
	Station new = malloc(sizeof(struct station));
	checkAlloc(new);
	new->rooms = malloc(numRooms * sizeof(Room));
	checkAlloc(new->rooms);
	for (int i = 0; i < numRooms; i++) {
		new->rooms[i].name = NULL;
		new->rooms[i].escape = false;
	}
	new->corridors = NULL;
	new->numRooms = numRooms;
	new->numCorridors = 0;
	new->corridorCapacity = 0;
	return new;
}

// Frees all memory associated with the station, including room names
// and the corridors array.
void StationFree(Station s) {
	for (int i = 0; i < s->numRooms; i++) {
		free(s->rooms[i].name);
	}
	free(s->rooms);
	free(s->corridors);
	free(s);
}

// Returns the number of rooms in the station.
int StationNumRooms(Station s) {
	return s->numRooms;
}

// Returns the number of corridors in the station.
int StationNumCorridors(Station s) {
	return s->numCorridors;
}

// Sets or replaces the name of the given room.
void StationSetRoomName(Station s, int room, char *name) {
	free(s->rooms[room].name);
	s->rooms[room].name = malloc(strlen(name) + 1);
	checkAlloc(s->rooms[room].name);
	strcpy(s->rooms[room].name, name);
}

// Returns the name of the given room, or "unnamed" if no name has
// been set.
char *StationGetRoomName(Station s, int room) {
	if (s->rooms[room].name == NULL) {
		return "unnamed";
	}
	return s->rooms[room].name;
}

// Marks the given room as containing an escape pod.
void StationSetEscapePod(Station s, int room) {
	s->rooms[room].escape = true;
}

// Returns whether the given room contains an escape pod.
bool StationHasEscapePod(Station s, int room) {
	return s->rooms[room].escape;
}

// Inserts a corridor between two rooms with the given travel time.
// Does nothing if a corridor already exists between the two rooms.
// Assumes that travelTime is positive.
void StationInsertCorridor(Station s, int room1, int room2, int travelTime) {
	if (StationContainsCorridor(s, room1, room2) != NO_CORRIDOR) {
		return;
	}

	if (s->numCorridors == s->corridorCapacity) {
		if (s->corridorCapacity == 0) {
			s->corridorCapacity = 4;
		} else {
			s->corridorCapacity *= 2;
		}
		s->corridors = realloc(s->corridors,
		                       sizeof(struct corridor) * s->corridorCapacity);
		checkAlloc(s->corridors);
	}
	s->corridors[s->numCorridors].fromRoom = room1;
	s->corridors[s->numCorridors].toRoom = room2;
	s->corridors[s->numCorridors].travelTime = travelTime;
	s->numCorridors++;
}

// Returns the travel time of the corridor between two rooms, or
// NO_CORRIDOR if no such corridor exists.
int StationContainsCorridor(Station s, int room1, int room2) {
	for (int i = 0; i < s->numCorridors; i++) {
		int from = s->corridors[i].fromRoom;
		int to = s->corridors[i].toRoom;
		if ((from == room1 && to == room2) || (from == room2 && to == room1)) {
			return s->corridors[i].travelTime;
		}
	}
	return NO_CORRIDOR;
}

// Stores all corridors connected to the given room in the corridors
// array, oriented so that fromRoom is always the given room, and
// sorted in ascending order of toRoom. Returns the number of
// corridors stored. Assumes that the corridors array is large enough.
int StationGetCorridorsFrom(Station s, int room, struct corridor corridors[]) {
	int count = 0;
	for (int i = 0; i < s->numCorridors; i++) {
		int from = s->corridors[i].fromRoom;
		int to = s->corridors[i].toRoom;
		int time = s->corridors[i].travelTime;

		if (from == room) {
			corridors[count].fromRoom = from;
			corridors[count].toRoom = to;
			corridors[count].travelTime = time;
			count++;
		} else if (to == room) {
			corridors[count].fromRoom = to;
			corridors[count].toRoom = from;
			corridors[count].travelTime = time;
			count++;
		}
	}

	qsort(corridors, count, sizeof(struct corridor), compareByToRoom);
	return count;
}

// Compares two corridors by their toRoom field, for use with qsort.
static int compareByToRoom(const void *a, const void *b) {
	return ((struct corridor *) a)->toRoom - ((struct corridor *) b)->toRoom;
}

////////////////////////////////////////////////////////////////////////
// !!! DO NOT MODIFY THE CODE BELOW !!!

void StationShow(Station s) {
	if (s == NULL) return;

	int numRooms = StationNumRooms(s);

	printf("Number of rooms: %d\n", numRooms);
	printf("Number of corridors: %d\n", StationNumCorridors(s));

	for (int i = 0; i < numRooms; i++) {
		printf("[%d] %s", i, StationGetRoomName(s, i));
		if (StationHasEscapePod(s, i)) {
			printf(" (escape pod)");
		}
		printf(" has corridors to:");

		struct corridor *corridors = malloc(numRooms * sizeof(struct corridor));
		if (corridors == NULL) {
			fprintf(stderr, "error: out of memory\n");
			exit(EXIT_FAILURE);
		}

		int n = StationGetCorridorsFrom(s, i, corridors);
		for (int j = 0; j < n; j++) {
			printf(" [%d] %s (%d)", corridors[j].toRoom,
					StationGetRoomName(s, corridors[j].toRoom),
					corridors[j].travelTime);
		}
		free(corridors);
		printf("\n");
	}
}