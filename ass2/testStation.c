// COMP2521 - Assignment 2
// Main program for testing the Station ADT

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "Station.h"

static void test1_1(void);
static void test1_2(void);
static void test1_3(void);
static void test1_4(void);

int main(int argc, char *argv[]) {
	test1_1();
	test1_2();
	test1_3();
	test1_4();

	return 0;
}

static void test1_1(void) {
	Station s = StationNew(5);

	assert(StationNumRooms(s) == 5);
	assert(StationNumCorridors(s) == 0);

	StationFree(s);
	printf("Test 1.1 passed!\n");
}

static void test1_2(void) {
	Station s = StationNew(4);

	StationSetRoomName(s, 0, "airlock");
	StationSetRoomName(s, 1, "lab");
	assert(strcmp(StationGetRoomName(s, 0), "airlock") == 0);
	assert(strcmp(StationGetRoomName(s, 1), "lab") == 0);
	assert(strcmp(StationGetRoomName(s, 2), "unnamed") == 0);
	StationSetRoomName(s, 1, "medbay");
	assert(strcmp(StationGetRoomName(s, 1), "medbay") == 0);

	StationFree(s);
	printf("Test 1.2 passed!\n");
}

static void test1_3(void) {
	Station s = StationNew(4);

	assert(!StationHasEscapePod(s, 2));
	StationSetEscapePod(s, 2);
	assert(StationHasEscapePod(s, 2));
	StationSetEscapePod(s, 2);
	assert(StationHasEscapePod(s, 2));

	StationFree(s);
	printf("Test 1.3 passed!\n");
}

static void test1_4(void) {
	Station s = StationNew(5);

	StationInsertCorridor(s, 0, 1, 4);
	StationInsertCorridor(s, 0, 3, 2);
	StationInsertCorridor(s, 1, 2, 6);
	StationInsertCorridor(s, 0, 1, 99); // duplicate should do nothing

	assert(StationNumCorridors(s) == 3);
	assert(StationContainsCorridor(s, 0, 1) == 4);
	assert(StationContainsCorridor(s, 1, 0) == 4);
	assert(StationContainsCorridor(s, 0, 4) == NO_CORRIDOR);

	struct corridor corridors[5];
	int n = StationGetCorridorsFrom(s, 0, corridors);
	assert(n == 2);
	assert(corridors[0].fromRoom == 0);
	assert(corridors[0].toRoom == 1);
	assert(corridors[0].travelTime == 4);
	assert(corridors[1].fromRoom == 0);
	assert(corridors[1].toRoom == 3);
	assert(corridors[1].travelTime == 2);

	StationFree(s);
	printf("Test 1.4 passed!\n");
}

