// Implementation of the graph reader module

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

Graph readGraph(char *filename) {
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "error: failed to open '%s' for reading\n", filename);
		exit(EXIT_FAILURE);
	}

	int nV = 0;
	if (fscanf(fp, "%d", &nV) == 0) {
		fprintf(stderr, "error: failed to read number of vertices\n");
		exit(EXIT_FAILURE);
	}

	Graph g = GraphNew(nV);

	int u = 0;
	int v = 0;
	while (fscanf(fp, "%d %d", &u, &v) == 2) {
		GraphInsertEdge(g, u, v);
	}

	return g;
}

