
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphAdjListRep.h"
#include "graphReader.h"
#include "Queue.h"

struct result {
	int vertex;
	int distance;
};

struct result furthestVertex(Graph g, int src);

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "usage: %s <graph file> <source vertex>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	char *graphFile = argv[1];

	Graph g = readGraph(graphFile);

	int src;

	char c;
	if (sscanf(argv[2], "%d%c", &src, &c) != 1) {
		fprintf(stderr, "error: invalid source vertex '%s'\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	if (src < 0 || src >= GraphNumVertices(g)) {
		fprintf(stderr, "error: invalid source vertex '%s'\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	printf("-----\n");
	printf("Graph\n");
	printf("-----\n");
	GraphShow(g);
	printf("\n");

	struct result result = furthestVertex(g, src);

	printf("Furthest vertex: %d (distance = %d)\n", result.vertex,
			result.distance);

	GraphFree(g);

	return 0;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
// (unless you are adding function prototypes)
////////////////////////////////////////////////////////////////////////
// Your task

struct result furthestVertex(Graph g, int src) {
	int nV = GraphNumVertices(g);

	bool *visited = calloc(nV, sizeof(bool));
	int *distance = malloc(nV * sizeof(int));
	if (visited == NULL || distance == NULL) {
		exit(EXIT_FAILURE);
	}

	Queue q = QueueNew();
	QueueEnqueue(q, src);
	visited[src] = true;
	distance[src] = 0;

	int furthestVertexNum = src;
	int furthestDistance = 0;

	while (!QueueIsEmpty(q)) {
		int u = QueueDequeue(q);

		// BFS dequeues in non-decreasing order of distance, so the last
		// vertex dequeued will have the maximum distance, but we track
		// the max as we go either way
		if (distance[u] > furthestDistance) {
			furthestDistance = distance[u];
			furthestVertexNum = u;
		}

		for (struct adjNode *curr = g->edges[u]; curr != NULL;
				curr = curr->next) {
			int v = curr->v;
			if (!visited[v]) {
				visited[v] = true;
				distance[v] = distance[u] + 1;
				QueueEnqueue(q, v);
			}
		}
	}

	QueueFree(q);
	free(visited);
	free(distance);

	struct result result = {
		.vertex = furthestVertexNum,
		.distance = furthestDistance,
	};

	return result;
}
