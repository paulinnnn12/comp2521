// Internal representation of the adjacency list representation

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef GRAPH_ADJ_LIST_REP_H
#define GRAPH_ADJ_LIST_REP_H

struct graph {
	int nV;
	int nE;
	struct adjNode **edges; // lists are kept in increasing order
};

struct adjNode {
	int v;
	struct adjNode *next;
};

#endif

