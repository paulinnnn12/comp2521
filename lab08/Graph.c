// Implementation of the Undirected Weighted Graph ADT
// Uses an adjacency matrix

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "Graph.h"
#include "Pq.h"

// DO NOT modify this struct
struct graph {
    int nV;         // #vertices
    int nE;         // #edges
    double **edges; // adjacency matrix storing positive weights
                    // 0 if nodes not adjacent
};

static bool validVertex(Graph g, Vertex v);

////////////////////////////////////////////////////////////////////////

Graph GraphNew(int nV) {
    assert(nV > 0);

    Graph g = malloc(sizeof(*g));
    if (g == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    g->nV = nV;
    g->nE = 0;

    g->edges = malloc(nV * sizeof(double *));
    if (g->edges == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nV; i++) {
        g->edges[i] = calloc(nV, sizeof(double));
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

////////////////////////////////////////////////////////////////////////

int GraphNumVertices(Graph g) {
    return g->nV;
}

bool GraphInsertEdge(Graph g, struct edge e) {
    assert(validVertex(g, e.v));
    assert(validVertex(g, e.w));
    assert(e.v != e.w);
    assert(e.weight > 0.0);

    if (g->edges[e.v][e.w] == 0.0) {
        g->edges[e.v][e.w] = e.weight;
        g->edges[e.w][e.v] = e.weight;
        g->nE++;
        return true;
    } else {
        return false;
    }
}

bool GraphRemoveEdge(Graph g, Vertex v, Vertex w) {
    assert(validVertex(g, v));
    assert(validVertex(g, w));

    if (g->edges[v][w] != 0.0) {   // edge e in graph
        g->edges[v][w] = 0.0;
        g->edges[w][v] = 0.0;
        g->nE--;
        return true;
    } else {
        return false;
    }
}

double GraphIsAdjacent(Graph g, Vertex v, Vertex w) {
    assert(validVertex(g, v));
    assert(validVertex(g, w));
    
    return g->edges[v][w];
}

void GraphShow(Graph g) {
    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    for (int v = 0; v < g->nV; v++) {
        for (int w = v + 1; w < g->nV; w++) {
            if (g->edges[v][w] != 0.0) {
                printf("Edge %d - %d: %lf\n", v, w, g->edges[v][w]);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////
// Your task
Graph GraphMst(Graph g) {
    int nV = GraphNumVertices(g);

    // key[v]    = weight of the cheapest edge connecting v to the
    //             tree built so far (DBL_MAX if none found yet)
    // parent[v] = the tree vertex that edge connects v to
    // inTree[v] = whether v has already been added to the MST
    double *key = malloc(nV * sizeof(double));
    Vertex *parent = malloc(nV * sizeof(Vertex));
    bool *inTree = malloc(nV * sizeof(bool));

    for (int v = 0; v < nV; v++) {
        key[v] = DBL_MAX;
        parent[v] = -1;
        inTree[v] = false;
    }

    key[0] = 0.0; // start growing the tree from vertex 0

    for (int count = 0; count < nV; count++) {
        // find the vertex not yet in the tree with the smallest key
        Vertex u = -1;
        double best = DBL_MAX;
        for (int v = 0; v < nV; v++) {
            if (!inTree[v] && key[v] < best) {
                best = key[v];
                u = v;
            }
        }

        // if no reachable vertex remains, the graph is disconnected
        // and therefore has no spanning tree
        if (u == -1) {
            free(key);
            free(parent);
            free(inTree);
            return NULL;
        }

        inTree[u] = true;

        // relax the keys of all vertices adjacent to u
        for (int v = 0; v < nV; v++) {
            double weight = GraphIsAdjacent(g, u, v);
            if (weight > 0.0 && !inTree[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
            }
        }
    }

    Graph mst = GraphNew(nV);
    for (int v = 0; v < nV; v++) {
        if (parent[v] != -1) {
            struct edge e = { .v = parent[v], .w = v, .weight = key[v] };
            GraphInsertEdge(mst, e);
        }
    }

    free(key);
    free(parent);
    free(inTree);

    return mst;
}
////////////////////////////////////////////////////////////////////////

static bool validVertex(Graph g, Vertex v) {
    return v >= 0 && v < g->nV;
}

