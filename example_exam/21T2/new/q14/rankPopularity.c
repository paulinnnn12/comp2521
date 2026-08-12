// rankPopularity.c ... implementation of rankPopularity function

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
struct queue{
    int *arr;
    int front;
    int end;
};
typedef struct queue * Queue;

Queue newQueue (int nV) {
    Queue new = malloc(sizeof(struct queue));
    new->arr = calloc(nV, sizeof(int));
    new->front = 0;
    new->end = 0;
    return new;
}

void enQueue (Queue q, int value) {
    q->arr[q->end] = value;
    q->end ++;
}

int deQueue (Queue q) {
    int temp = q->arr[q->front];
    q->front ++;
    return temp;
}

bool isEmpty (Queue q) {
    return q->front == q->end;
}

void rankPopularity(Graph g, int src, double *mnV) {
    int *visited = calloc (g->nV, sizeof(int));
    Queue q = newQueue(g->nV);
    enQueue(q, src);
    visited[src] = true;
    while (!isEmpty(q)) {
        int v = deQueue(q);
        double in = 0, out = 0;

        for (int w = 0; w < g->nV; w ++) {
            if (GraphIsAdjacent(g, v, w) && !visited[w]) {
                enQueue(q, w);
                visited[w] = true;
            }
            if (g->edges[v][w] != 0) {
                out ++;
            }
            if (g->edges[w][v] != 0) {
                in ++;
            }
            
        }
        if (out == 0) out = 0.5;
        mnV[v] = in / out;
    }
    
    free(visited);
    free(q->arr);
    free(q);
    
}

