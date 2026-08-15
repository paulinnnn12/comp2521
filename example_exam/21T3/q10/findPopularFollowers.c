#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

// Marks `cur` and every vertex that can reach `cur` (i.e. every vertex
// from which there's a directed path of "follows" edges to `cur`) as
// reachable, via a DFS that walks backwards along in-edges.
static void findReachable(Graph g, int cur, bool *visited, bool *reachable) {
	visited[cur] = true;
	reachable[cur] = true;
	for (int i = 0; i < g->nV; i++) {
		if (!visited[i] && GraphIsAdjacent(g, i, cur)) {
			findReachable(g, i, visited, reachable);
		}
	}
}

// Worst case time complexity of this solution: O(V^2)
//
// The graph is stored as an adjacency matrix, so there is no way to list
// a vertex's in/out-neighbours faster than scanning all V possible
// neighbours (GraphIsAdjacent is O(1), but enumerating neighbours of one
// vertex is O(V)). findReachable visits each vertex at most once and does
// an O(V) scan per visit -> O(V^2). The in/out-degree count below also
// does an O(V) scan for each of the (at most V) reachable vertices -> O(V^2).
// Since just reading every entry of the V x V matrix once is already
// O(V^2), this is optimal for this representation.
void findPopularFollowers(Graph g, int src, int followers[]) {
	int nV = g->nV;
	bool *visited   = calloc(nV, sizeof(bool));
	bool *reachable = calloc(nV, sizeof(bool));
	assert(visited != NULL && reachable != NULL);

	// Step 1: find every vertex that can reach src, directly or via a
	// chain of follows - O(V^2)
	findReachable(g, src, visited, reachable);

	// Step 2: only for vertices we know are reachable, check whether
	// in-degree exceeds out-degree, and mark them popular if so - O(V^2)
	for (int i = 0; i < nV; i++) {
		if (!reachable[i]) continue;

		int in = 0, out = 0;
		for (int j = 0; j < nV; j++) {
			if (GraphIsAdjacent(g, i, j)) out++;
			if (GraphIsAdjacent(g, j, i)) in++;
		}
		if (in > out) followers[i] = 1;
	}

	free(visited);
	free(reachable);
}
