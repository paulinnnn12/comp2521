// COMP2521 - Assigment 2
// Implementation of the station reader module

// !!! DO NOT MODIFY THIS FILE !!!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Station.h"
#include "stationReader.h"

#define MAX_NAME 100
#define DATA_PREFIX "data/"

static char *makePath(char *filename);

Station readStation(char *filename) {
	char *path = makePath(filename);
	FILE *fp = fopen(path, "r");
	if (fp == NULL) {
		fprintf(stderr, "error: could not open %s\n", path);
		free(path);
		exit(EXIT_FAILURE);
	}
	free(path);

	int numRooms = 0;
	if (fscanf(fp, "%d", &numRooms) != 1) {
		fprintf(stderr, "error: invalid station file\n");
		fclose(fp);
		exit(EXIT_FAILURE);
	}

	Station s = StationNew(numRooms);

	for (int i = 0; i < numRooms; i++) {
		int room;
		char podFlag;
		char name[MAX_NAME];
		if (fscanf(fp, "%d %c %99s", &room, &podFlag, name) != 3) {
			fprintf(stderr, "error: invalid room line\n");
			StationFree(s);
			fclose(fp);
			exit(EXIT_FAILURE);
		}
		StationSetRoomName(s, room, name);
		if (podFlag == 'e') {
			StationSetEscapePod(s, room);
		}
	}

	int room1, room2, time;
	while (fscanf(fp, "%d %d %d", &room1, &room2, &time) == 3) {
		StationInsertCorridor(s, room1, room2, time);
	}

	fclose(fp);
	return s;
}

static char *makePath(char *filename) {
	size_t len = strlen(DATA_PREFIX) + strlen(filename) + 1;
	char *path = malloc(len);
	if (path == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}
	snprintf(path, len, "%s%s", DATA_PREFIX, filename);
	return path;
}

