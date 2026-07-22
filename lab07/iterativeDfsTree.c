
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphAdjListRep.h"
#include "graphReader.h"
#include "Stack.h"

Graph iterativeDfsTree(Graph g, int src);

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

	Graph t = iterativeDfsTree(g, src);

	printf("----------------------\n");
	printf("DFS tree from vertex %d\n", src);
	printf("----------------------\n");
	GraphShow(t);
	printf("\n");

	GraphFree(g);
	GraphFree(t);
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
// (unless you are adding function prototypes)
////////////////////////////////////////////////////////////////////////
// Your task

Graph iterativeDfsTree(Graph g, int src) {
	// TODO
	Graph t = GraphNew(g->nV);

	return t;
}

