// testEvacuation.c

#include <stdio.h>
#include <stdlib.h>
#include "Station.h"
#include "stationReader.h"
#include "evacuation.h"

static void printReachable(struct reachableRoomsResult res);
static void printRoute(struct route r);
static void freeReachable(struct reachableRoomsResult res);
static void freeRoute(struct route r);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <test file>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "error: could not open %s\n", argv[1]);
        return 1;
    }

    int task;
    char stationFile[100];
    if (fscanf(fp, "%d", &task) != 1 || fscanf(fp, "%99s", stationFile) != 1) {
        fprintf(stderr, "error: invalid test file\n");
        fclose(fp);
        return 1;
    }

    Station s = readStation(stationFile);

    if (task == 2) {
        struct reachableRoomsResult res = reachableRooms(s);
        printReachable(res);
        freeReachable(res);
    } else if (task == 3) {
        int fromRoom;
        fscanf(fp, "%d", &fromRoom);
        struct route r = fastestEscape(s, fromRoom);
        printRoute(r);
        freeRoute(r);
    } else if (task == 4) {
        int fromRoom, numBlocked;
        fscanf(fp, "%d", &fromRoom);
        fscanf(fp, "%d", &numBlocked);
        struct blockedCorridor *blocked = malloc(numBlocked * sizeof(struct blockedCorridor));
        if (blocked == NULL && numBlocked > 0) {
            fprintf(stderr, "error: out of memory\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < numBlocked; i++) {
            fscanf(fp, "%d %d", &blocked[i].roomA, &blocked[i].roomB);
        }
        struct route r = fastestEscapeAvoiding(s, fromRoom, blocked, numBlocked);
        printRoute(r);
        freeRoute(r);
        free(blocked);
    } else {
        fprintf(stderr, "error: unknown task\n");
        StationFree(s);
        fclose(fp);
        return 1;
    }

    StationFree(s);
    fclose(fp);
    return 0;
}

static void printReachable(struct reachableRoomsResult res) {
    printf("Rooms that can reach an escape pod: %d\n", res.numRooms);
    for (int i = 0; i < res.numRooms; i++) {
        printf("- room %d\n", res.rooms[i]);
    }
}

static void printRoute(struct route r) {
    if (r.numRooms == 0) {
        printf("No escape route found.\n");
        return;
    }

    printf("Escape route from room %d to room %d\n", r.fromRoom, r.toRoom);
    printf("Total duration: %d minutes\n", r.totalDuration);
    printf("Path:");
    for (int i = 0; i < r.numRooms; i++) {
        printf(" %d", r.rooms[i]);
        if (i < r.numRooms - 1) printf(" ->");
    }
    printf("\n");
}

static void freeReachable(struct reachableRoomsResult res) {
    free(res.rooms);
}

static void freeRoute(struct route r) {
    free(r.rooms);
}
