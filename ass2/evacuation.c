// COMP2521 - 26T2 Assignment 2: Space Station Evacuation
// z5643770
// Written: 16/07 - 30/07  [check/update this date before submitting]
//
// Implementation of the evacuation algorithms (see evacuation.h for
// the interface).
//
// reachableRooms finds every room that can reach an escape pod using
// a multi-source DFS started from every pod room at once (corridors
// are undirected, so being reachable FROM a pod is the same as being
// able to reach one).
//
// fastestEscape and fastestEscapeAvoiding both use Dijkstra's
// algorithm to find the shortest path to the closest escape pod.
// fastestEscapeAvoiding builds a copy of the station with blocked
// corridors removed, then reuses fastestEscape on the copy, rather
// than duplicating Dijkstra's algorithm with extra blocked-corridor
// logic built in.
//
// No known bugs or limitations.

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "evacuation.h"
#include "Station.h"

// prototypes for helper functions
static void checkAlloc(void *ptr);
static void dfsFromRoom(Station s, int start, bool *visited, int nV);
static int compareRoomIds(const void *a, const void *b);
static void dijkstra(Station s, int fromRoom, int nV,
                     int *pred, int *dist, bool *included);
static int *buildPath(int *pred, int fromRoom, int toRoom, int nV,
                      int *numRooms);
static bool isBlocked(struct blockedCorridor blocked[], int numBlocked,
                      int room1, int room2);

// Prints an error message and exits if ptr is NULL, i.e. a malloc or
// calloc call has failed. Called after every allocation in this file.
static void checkAlloc(void *ptr) {
	if (ptr == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}
}

// Returns every room from which an escape pod is reachable, found by
// running a DFS from every escape pod room at once and marking
// everything reached along the way.
struct reachableRoomsResult reachableRooms(Station s) {
	int nV = StationNumRooms(s);
	bool *visited = calloc(nV, sizeof(bool));
	checkAlloc(visited);
	bool foundPod = false;

	for (int room = 0; room < nV; room++) {
		if (StationHasEscapePod(s, room)) {
			foundPod = true;
			visited[room] = true;
			dfsFromRoom(s, room, visited, nV);
		}
	}

	if (!foundPod) {
		free(visited);
		return (struct reachableRoomsResult) {0, NULL};
	}

	int numRooms = 0;
	int *rooms = malloc(sizeof(int) * nV);
	checkAlloc(rooms);
	for (int room = 0; room < nV; room++) {
		if (visited[room]) {
			rooms[numRooms] = room;
			numRooms++;
		}
	}
	free(visited);

	qsort(rooms, numRooms, sizeof(int), compareRoomIds);
	return (struct reachableRoomsResult) {.numRooms = numRooms, .rooms = rooms};
}

// Marks every room reachable from start as visited, using DFS.
static void dfsFromRoom(Station s, int start, bool *visited, int nV) {
	struct corridor *corridors = malloc(nV * sizeof(struct corridor));
	checkAlloc(corridors);
	int numCorridors = StationGetCorridorsFrom(s, start, corridors);

	for (int i = 0; i < numCorridors; i++) {
		int next = corridors[i].toRoom;
		if (!visited[next]) {
			visited[next] = true;
			dfsFromRoom(s, next, visited, nV);
		}
	}
	free(corridors);
}

// Compares two room IDs in ascending order, for use with qsort.
static int compareRoomIds(const void *a, const void *b) {
	return *(int *) a - *(int *) b;
}

// Returns the fastest route from fromRoom to the closest escape pod,
// using Dijkstra's algorithm. If fromRoom already has an escape pod,
// the returned route has a duration of 0 and contains just fromRoom.
// If no escape pod is reachable, toRoom is set to -1.
struct route fastestEscape(Station s, int fromRoom) {
	struct reachableRoomsResult reachable = reachableRooms(s);

	bool canEscape = false;
	for (int i = 0; i < reachable.numRooms; i++) {
		if (reachable.rooms[i] == fromRoom) {
			canEscape = true;
			break;
		}
	}
	free(reachable.rooms);

	if (!canEscape) {
		return (struct route) {fromRoom, -1, 0, 0, NULL};
	}

	int nV = StationNumRooms(s);
	int *pred = malloc(sizeof(int) * nV);
	checkAlloc(pred);
	int *dist = malloc(sizeof(int) * nV);
	checkAlloc(dist);
	bool *included = calloc(nV, sizeof(bool));
	checkAlloc(included);

	dijkstra(s, fromRoom, nV, pred, dist, included);

	int closestPod = -1;
	int minDuration = INT_MAX;
	for (int room = 0; room < nV; room++) {
		if (StationHasEscapePod(s, room) && dist[room] < minDuration) {
			minDuration = dist[room];
			closestPod = room;
		}
	}

	struct route route;
	route.fromRoom = fromRoom;
	route.toRoom = closestPod;
	route.totalDuration = minDuration;
	route.rooms = buildPath(pred, fromRoom, closestPod, nV, &route.numRooms);

	free(pred);
	free(dist);
	free(included);
	return route;
}

// Runs Dijkstra's algorithm from fromRoom, filling in dist (shortest
// distance from fromRoom to each room) and pred (the previous room on
// the shortest path to each room). pred and dist must be allocated
// (but need not be initialised) by the caller; included must already
// be all false.
static void dijkstra(Station s, int fromRoom, int nV,
                     int *pred, int *dist, bool *included) {
	for (int i = 0; i < nV; i++) {
		pred[i] = -1;
		dist[i] = INT_MAX;
	}
	dist[fromRoom] = 0;

	for (int count = 0; count < nV; count++) {
		int u = -1;
		int minDist = INT_MAX;
		for (int i = 0; i < nV; i++) {
			if (!included[i] && dist[i] < minDist) {
				minDist = dist[i];
				u = i;
			}
		}
		if (u == -1) {
			return; // no more rooms are reachable
		}
		included[u] = true;

		for (int i = 0; i < nV; i++) {
			int edgeWeight = StationContainsCorridor(s, u, i);
			if (edgeWeight != NO_CORRIDOR && !included[i]) {
				int newDist = dist[u] + edgeWeight;
				if (newDist < dist[i]) {
					dist[i] = newDist;
					pred[i] = u;
				}
			}
		}
	}
}

// Reconstructs the path from fromRoom to toRoom using the predecessor
// array produced by dijkstra. Returns a dynamically allocated array
// of room IDs from fromRoom to toRoom (inclusive), and sets *numRooms
// to its length. The caller is responsible for freeing the array.
static int *buildPath(int *pred, int fromRoom, int toRoom, int nV,
                      int *numRooms) {
	int *path = malloc(sizeof(int) * nV);
	checkAlloc(path);
	int count = 0;
	int curr = toRoom;
	while (curr != fromRoom) {
		path[count++] = curr;
		curr = pred[curr];
	}
	path[count++] = curr;

	for (int i = 0; i < count / 2; i++) {
		int temp = path[i];
		path[i] = path[count - 1 - i];
		path[count - 1 - i] = temp;
	}

	*numRooms = count;
	return path;
}

// Returns the fastest route from fromRoom to the closest escape pod,
// avoiding a given set of blocked corridors. Builds a copy of the
// station with the blocked corridors removed, then reuses
// fastestEscape on the copy.
struct route fastestEscapeAvoiding(Station s, int fromRoom,
                                   struct blockedCorridor blocked[],
                                   int numBlocked) {
	int nV = StationNumRooms(s);
	Station copy = StationNew(nV);

	for (int room = 0; room < nV; room++) {
		StationSetRoomName(copy, room, StationGetRoomName(s, room));
		if (StationHasEscapePod(s, room)) {
			StationSetEscapePod(copy, room);
		}
		for (int other = 0; other < nV; other++) {
			int travelTime = StationContainsCorridor(s, room, other);
			if (travelTime != NO_CORRIDOR &&
			    !isBlocked(blocked, numBlocked, room, other)) {
				StationInsertCorridor(copy, room, other, travelTime);
			}
		}
	}

	struct route route = fastestEscape(copy, fromRoom);
	StationFree(copy);
	return route;
}

// Returns whether the corridor between room1 and room2 appears (in
// either direction) in the blocked corridors array.
static bool isBlocked(struct blockedCorridor blocked[], int numBlocked,
                      int room1, int room2) {
	for (int i = 0; i < numBlocked; i++) {
		if ((room1 == blocked[i].roomA && room2 == blocked[i].roomB) ||
		    (room1 == blocked[i].roomB && room2 == blocked[i].roomA)) {
			return true;
		}
	}
	return false;
}