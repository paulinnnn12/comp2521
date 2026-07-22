
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphAdjMatrixRep.h"
#include "graphReader.h"

Graph dfsTree(Graph g, int src);

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

	Graph t = dfsTree(g, src);

	printf("----------------------\n");
	printf("DFS tree from vertex %d\n", src);
	printf("----------------------\n");
	GraphShow(t);
	printf("\n");

	GraphFree(g);
	GraphFree(t);

	return 0;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
// (unless you are adding function prototypes)
////////////////////////////////////////////////////////////////////////
// Your task

void recursiveDfs(Graph g, Graph t, int u, int *visited) {
	visited[u] = 1;

	for (int i = 0; i < g->nV; i ++) {
		if (g->edges[u][i]) {
			if (!visited[i]) {
				GraphInsertEdge(t, u, i);
				recursiveDfs(g, t, i, visited);
			}
		}
	}
}


Graph dfsTree(Graph g, int src) {
	Graph t = GraphNew(g->nV);
	int *visited = calloc(g->nV, sizeof(int));

	recursiveDfs(g, t, src, visited);
	free(visited);
	return t;
}