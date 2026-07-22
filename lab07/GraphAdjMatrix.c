// Adjacency matrix implementation of the undirected graph ADT

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphAdjMatrixRep.h"

static void checkValidVertex(Graph g, int v);

Graph GraphNew(int nV) {
	Graph g = malloc(sizeof(*g));
	if (g == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	g->nV = nV;
	g->nE = 0;

	g->edges = malloc(nV * sizeof(bool *));
	if (g->edges == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < nV; i++) {
		g->edges[i] = calloc(nV, sizeof(bool));
		if (g->edges[i] == NULL) {
			fprintf(stderr, "error: out of memory\n");
			exit(EXIT_FAILURE);
		}
	}

	return g;
}

void GraphFree(Graph g) {
	for (int i = 0; i < g->nV; i++) {
		free(g->edges[i]);
	}
	free(g->edges);
	free(g);
}

int GraphNumVertices(Graph g) {
	return g->nV;
}

int GraphNumEdges(Graph g) {
	return g->nE;
}

void GraphInsertEdge(Graph g, int u, int v) {
	checkValidVertex(g, u);
	checkValidVertex(g, v);

	if (!g->edges[u][v]) {
		g->edges[u][v] = true;
		g->edges[v][u] = true;
		g->nE++;
	}
}

static void checkValidVertex(Graph g, int v) {
	if (v < 0 || v >= g->nV) {
		fprintf(stderr, "error: invalid vertex %d\n", v);
		exit(EXIT_FAILURE);
	}
}

void GraphShow(Graph g) {
	GraphPrint(g, stdout);
}

void GraphPrint(Graph g, FILE *fp) {
	fprintf(fp, "Number of vertices: %d\n", g->nV);
	fprintf(fp, "Edges:\n");
	for (int i = 0; i < g->nV; i++) {
		fprintf(fp, " %d:", i);
		for (int j = 0; j < g->nV; j++) {
			if (g->edges[i][j]) {
				fprintf(fp, " %d", j);
			}
		}
		fprintf(fp, "\n");
	}
}

