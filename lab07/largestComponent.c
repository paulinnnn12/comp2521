
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphAdjMatrixRep.h"
#include "graphReader.h"
#include "Queue.h"

int largestComponent(Graph g, int component[]);
void sort(int arr[], int size);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <graph file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	char *graphFile = argv[1];

	Graph g = readGraph(graphFile);

	printf("-----\n");
	printf("Graph\n");
	printf("-----\n");
	GraphShow(g);
	printf("\n");

	int *component = calloc(GraphNumVertices(g), sizeof(int));
	if (component == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	int compSize = largestComponent(g, component);

	sort(component, compSize);

	printf("Largest component contains %d %s:", compSize,
			compSize == 1 ? "vertex" : "vertices");
	for (int i = 0; i < compSize; i++) {
		printf(" %d", component[i]);
	}
	printf("\n");

	GraphFree(g);
	free(component);

	return 0;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
// (unless you are adding function prototypes)
////////////////////////////////////////////////////////////////////////
// Your task


int largestComponent(Graph g, int component[]) {
	int nV = GraphNumVertices(g);

	bool *visited = calloc(nV, sizeof(bool));
	int *temp = malloc(nV * sizeof(int));
	if (visited == NULL || temp == NULL) {
		exit(EXIT_FAILURE);
	}

	int bestSize = 0;
	Queue q = QueueNew();

	// try every vertex as a fresh BFS root, skipping ones already
	// claimed by an earlier component
	for (int start = 0; start < nV; start++) {
		if (visited[start]) {
			continue;
		}

		int size = 0;
		visited[start] = true;
		temp[size++] = start;
		QueueEnqueue(q, start);

		while (!QueueIsEmpty(q)) {
			int u = QueueDequeue(q);

			for (int v = 0; v < nV; v++) {
				if (g->edges[u][v] && !visited[v]) {
					visited[v] = true;
					temp[size++] = v;
					QueueEnqueue(q, v);
				}
			}
		}

		// keep this component only if it's the largest seen so far
		if (size > bestSize) {
			bestSize = size;
			for (int i = 0; i < size; i++) {
				component[i] = temp[i];
			}
		}
	}

	QueueFree(q);
	free(visited);
	free(temp);

	return bestSize;
}
////////////////////////////////////////////////////////////////////////
// !!! DO NOT MODIFY THE CODE BELOW !!!

void sort(int arr[], int size) {
	for (int i = 0; i < size - 1; i++) {
		int min = i;
		for (int j = i + 1; j < size; j++) {
			if (arr[j] < arr[min]) {
				min = j;
			}
		}

		int tmp = arr[i];
		arr[i] = arr[min];
		arr[min] = tmp;
	}
}