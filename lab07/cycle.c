
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphAdjListRep.h"
#include "graphReader.h"
#include "Queue.h"

int cycle(Graph g, int path[]);

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

	int *path = calloc((GraphNumVertices(g) + 1), sizeof(int));	
	int pathLength = cycle(g, path);

	if (pathLength == 0) {
		printf("No cycle\n");
	} else {
		printf("Cycle:");
		for (int i = 0; i < pathLength; i++) {
			printf(" %d", path[i]);
		}
		printf("\n");

		if (path[0] != path[pathLength - 1]) {
			printf("Warning: cycle should start and end with the same vertex\n");
		} else if (pathLength < 4) { // 4 is intentional
			printf("Warning: cycle should contain at least 3 vertices\n");
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
int cycle(Graph g, int path[]) {
	int nV = g->nV;
	bool *visited = calloc(nV, sizeof(bool));
	int *predecessor = malloc(nV * sizeof(int));
	for (int i = 0; i < nV; i++) {
		predecessor[i] = -1;
	}

	int the_u = -1, the_v = -1;
	bool has_cycle = false;

	Queue q = QueueNew();

	for (int start = 0; start < nV && !has_cycle; start++) {
		if (visited[start]) {
			continue;
		}

		visited[start] = true;
		QueueEnqueue(q, start);

		while (!QueueIsEmpty(q) && !has_cycle) {
			int u = QueueDequeue(q);

			for (struct adjNode *curr = g->edges[u]; curr != NULL;
					curr = curr->next) {
				int v = curr->v;
				if (!visited[v]) {
					visited[v] = true;
					predecessor[v] = u;
					QueueEnqueue(q, v);
				} else if (v != predecessor[u]) {
					has_cycle = true;
					the_u = u;
					the_v = v;
					break;
				}
			}
		}
	}

	QueueFree(q);

	if (!has_cycle) {
		free(visited);
		free(predecessor);
		return 0;
	}

	int *chainU = malloc(nV * sizeof(int));
	int *chainV = malloc(nV * sizeof(int));
	int lenU = 0, lenV = 0;

	for (int cur = the_u; cur != -1; cur = predecessor[cur]) {
		chainU[lenU++] = cur;
	}
	for (int cur = the_v; cur != -1; cur = predecessor[cur]) {
		chainV[lenV++] = cur;
	}

	int i = lenU - 1, j = lenV - 1;
	while (i >= 0 && j >= 0 && chainU[i] == chainV[j]) {
		i--;
		j--;
	}
	int lcaIndexU = i + 1;
	int lcaIndexV = j + 1;

	int length = 0;

	for (int k = 0; k <= lcaIndexU; k++) {
		path[length++] = chainU[k];
	}

	for (int k = lcaIndexV - 1; k >= 0; k--) {
		path[length++] = chainV[k];
	}

	path[length++] = the_u;

	free(chainU);
	free(chainV);
	free(visited);
	free(predecessor);

	return length;
}
