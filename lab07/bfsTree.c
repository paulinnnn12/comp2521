
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphAdjListRep.h"
#include "graphReader.h"
#include "Queue.h"

Graph bfsTree(Graph g, int src);

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

	Graph t = bfsTree(g, src);
	printf("----------------------\n");
	printf("BFS tree from vertex %d\n", src);
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

Graph bfsTree(Graph g, int src) {
	Graph t = GraphNew(g->nV);
	int *visited = calloc(g->nV, sizeof(int));

	Queue q = QueueNew();
	QueueEnqueue(q, src);
	visited[src] = 1;

	while(QueueSize(q) > 0) {
		int u = QueueDequeue(q);
		struct adjNode *curr = g->edges[u];
		while (curr != NULL) {
			if (visited[curr->v] != 1) {
				visited[curr->v] = 1;
				GraphInsertEdge(t, curr->v, u);
				QueueEnqueue(q, curr->v);
			}
			curr = curr->next;
		}
	}

	QueueFree(q);
	free(visited);
	
	return t;
}


