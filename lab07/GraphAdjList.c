// Adjacency list implementation of the undirected graph ADT

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphAdjListRep.h"

static void freeAdjList(struct adjNode *list);
static void checkValidVertex(Graph g, int v);
static struct adjNode *adjListInsert(struct adjNode *list, int v, Graph g);
static struct adjNode *newNode(int v);

Graph GraphNew(int nV) {
	Graph g = malloc(sizeof(*g));
	if (g == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	g->nV = nV;
	g->nE = 0;
	g->edges = calloc(nV, sizeof(struct adjNode *));
	if (g->edges == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	return g;
}

void GraphFree(Graph g) {
	for (int i = 0; i < g->nV; i++) {
		freeAdjList(g->edges[i]);
	}
	free(g->edges);
	free(g);
}

static void freeAdjList(struct adjNode *list) {
	struct adjNode *curr = list;
	while (curr != NULL) {
		struct adjNode *temp = curr;
		curr = curr->next;
		free(temp);
	}
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

	g->edges[u] = adjListInsert(g->edges[u], v, g);
	g->edges[v] = adjListInsert(g->edges[v], u, g);
}

static void checkValidVertex(Graph g, int v) {
	if (v < 0 || v >= g->nV) {
		fprintf(stderr, "error: invalid vertex %d\n", v);
		exit(EXIT_FAILURE);
	}
}

static struct adjNode *adjListInsert(struct adjNode *list, int v, Graph g) {
	if (list == NULL || v < list->v) {
		struct adjNode *n = newNode(v);
		n->next = list;
		g->nE++;
		return n;
	}

	if (list->v == v) {
		return list;
	}

	list->next = adjListInsert(list->next, v, g);
	return list;
}

static struct adjNode *newNode(int v) {
	struct adjNode *n = malloc(sizeof(*n));
	if (n == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	n->v = v;
	n->next = NULL;
	return n;
}

void GraphShow(Graph g) {
	GraphPrint(g, stdout);
}

void GraphPrint(Graph g, FILE *fp) {
	fprintf(fp, "Number of vertices: %d\n", g->nV);
	fprintf(fp, "Edges:\n");
	for (int i = 0; i < g->nV; i++) {
		fprintf(fp, " %d:", i);
		for (struct adjNode *curr = g->edges[i]; curr != NULL;
				curr = curr->next) {
			fprintf(fp, " %d", curr->v);
		}
		fprintf(fp, "\n");
	}
}

