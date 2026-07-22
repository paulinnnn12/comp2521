// COMP2521 - Assignment 2
// Implementation of the Station ADT

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Station.h"

struct station {
	// TODO: Complete this struct
};

Station StationNew(int numRooms) {
	// TODO
	return NULL;
}

void StationFree(Station s) {
	// TODO
}

int StationNumRooms(Station s) {
	// TODO
	return 0;
}

int StationNumCorridors(Station s) {
	// TODO
	return 0;
}

void StationSetRoomName(Station s, int room, char *name) {
	// TODO
}

char *StationGetRoomName(Station s, int room) {
	// TODO
	return "unnamed";
}

void StationSetEscapePod(Station s, int room) {
	// TODO
}

bool StationHasEscapePod(Station s, int room) {
	// TODO
	return false;
}

void StationInsertCorridor(Station s, int room1, int room2, int travelTime) {
	// TODO
}

int StationContainsCorridor(Station s, int room1, int room2) {
	// TODO
	return NO_CORRIDOR;
}

int StationGetCorridorsFrom(Station s, int room, struct corridor corridors[]) {
	// TODO
	return 0;
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

