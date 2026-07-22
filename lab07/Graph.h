// Interface to the undirected graph ADT

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph *Graph;

Graph GraphNew(int nV);

void GraphFree(Graph g);

int GraphNumVertices(Graph g);

int GraphNumEdges(Graph g);

void GraphInsertEdge(Graph g, int u, int v);

void GraphShow(Graph g);

void GraphPrint(Graph g, FILE *fp);

#endif

