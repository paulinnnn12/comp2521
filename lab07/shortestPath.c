
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphAdjMatrixRep.h"
#include "graphReader.h"
#include "Queue.h"

int shortestPath(Graph g, int src, int dest, int path[]);

int main(int argc, char *argv[]) {
	if (argc != 4) {
		fprintf(stderr,
				"usage: %s <graph file> <source vertex> <destination vertex>\n",
				argv[0]);
		exit(EXIT_FAILURE);
	}

	char *graphFile = argv[1];

	Graph g = readGraph(graphFile);

	int src;
	int dest;

	char c;
	if (sscanf(argv[2], "%d%c", &src, &c) != 1) {
		fprintf(stderr, "error: invalid source vertex '%s'\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	if (src < 0 || src >= GraphNumVertices(g)) {
		fprintf(stderr, "error: invalid source vertex '%s'\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	if (sscanf(argv[3], "%d%c", &dest, &c) != 1) {
		fprintf(stderr, "error: invalid destination vertex '%s'\n", argv[3]);
		exit(EXIT_FAILURE);
	}

	if (dest < 0 || dest >= GraphNumVertices(g)) {
		fprintf(stderr, "error: invalid destination vertex '%s'\n", argv[3]);
		exit(EXIT_FAILURE);
	}

	printf("-----\n");
	printf("Graph\n");
	printf("-----\n");
	GraphShow(g);
	printf("\n");

	int *path = calloc(GraphNumVertices(g), sizeof(int));
	int pathLength = shortestPath(g, src, dest, path);

	if (pathLength == 0) {
		printf("No path from %d to %d\n", src, dest);
	} else {
		printf("Shortest path from %d to %d:", src, dest);
		for (int i = 0; i < pathLength; i++) {
			printf(" %d", path[i]);
		}
		printf("\n");

		if (path[0] != src || path[pathLength - 1] != dest) {
			printf("Warning: path should start with %d and end with %d\n",
					src, dest);
		}
	}

	GraphFree(g);
	free(path);

	return 0;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
// (unless you are adding function prototypes)
////////////////////////////////////////////////////////////////////////
// Your task

int shortestPath(Graph g, int src, int dest, int path[]) {
	bool *visited = calloc(g->nV, sizeof(bool));
	int *predecessor = malloc(g->nV * sizeof(int));

	for (int i = 0; i < g->nV; i ++) {
		predecessor[i] = -1;
	}

	Queue q = QueueNew();
	QueueEnqueue(q, src);
	visited[src] = true;

	while (!QueueIsEmpty(q)) {
		int u = QueueDequeue(q);

		for (int v = 0; v < g->nV; v ++) {
			if (g->edges[u][v] && !visited[v]) {
				visited[v] = true;
				predecessor[v] = u;
				QueueEnqueue(q, v);
			}
		}
	}

	QueueFree(q);

	if (!visited[dest]) {
		free(visited);
		free(predecessor);
		return 0;
	}

	int length = 0;
	int curr = dest;
	while (curr != src) {
		path[length] = curr;
		curr = predecessor[curr];
		length ++;
	}
	path[length] = src;
	length ++;

	for (int i = 0; i < length / 2; i ++) {
		int tem = path[i];

		path[i] = path[length - i - 1];

		path[length - i - 1] = tem;
	}

	free(visited);
	free(predecessor);

	return length;
}

