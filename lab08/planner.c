// Algorithms to design electrical grids

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "place.h"
#include "Pq.h"

////////////////////////////////////////////////////////////////////////
// Your task

/**
 * Designs  a minimal cost electrical grid that will deliver electricity
 * from a power plant to all the given cities. Power lines must be built
 * between cities or between a city and a power plant.  Cost is directly
 * proportional to the total length of power lines used.
 * Assumes  that  numCities  is at least 1 (numCities is the size of the
 * cities array).
 * Stores the power lines that need to be built in the given  powerLines
 * array, and returns the number of power lines stored. Assumes that the
 * powerLines array is large enough to store all required power lines.
 */
static double distance(struct place a, struct place b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

int planGrid1(struct place cities[], int numCities,
              struct place powerPlant,
              struct powerLine powerLines[]) {

    // Build a complete graph where vertices 0..numCities-1 are the
    // cities and vertex `numCities` is the power plant. Edge weights
    // are the Euclidean distance between the two places.
    int nV = numCities + 1;
    Graph g = GraphNew(nV);

    for (int i = 0; i < nV; i++) {
        struct place pi = (i < numCities) ? cities[i] : powerPlant;
        for (int j = i + 1; j < nV; j++) {
            struct place pj = (j < numCities) ? cities[j] : powerPlant;
            double w = distance(pi, pj);
            if (w <= 0.0) {
                // guard against coincident locations, since edge
                // weights must be strictly positive
                w = 1e-9;
            }
            GraphInsertEdge(g, (struct edge){i, j, w});
        }
    }

    Graph mst = GraphMst(g);

    int numLines = 0;
    if (mst != NULL) {
        for (int i = 0; i < nV; i++) {
            struct place pi = (i < numCities) ? cities[i] : powerPlant;
            for (int j = i + 1; j < nV; j++) {
                if (GraphIsAdjacent(mst, i, j) > 0.0) {
                    struct place pj = (j < numCities) ? cities[j] : powerPlant;
                    powerLines[numLines].p1 = pi;
                    powerLines[numLines].p2 = pj;
                    numLines++;
                }
            }
        }
        GraphFree(mst);
    }

    GraphFree(g);
    return numLines;
}

////////////////////////////////////////////////////////////////////////
// Optional task

/**
 * Designs  a minimal cost electrical grid that will deliver electricity
 * to all the given cities.  Power lines must be built between cities or
 * between a city and a power plant.  Cost is directly  proportional  to
 * the  total  length of power lines used.  Assume that each power plant
 * generates enough electricity to supply all cities, so not  all  power
 * plants need to be used.
 * Assumes  that  numCities and numPowerPlants are at least 1 (numCities
 * and numPowerPlants are the sizes of the cities and powerPlants arrays
 * respectively).
 * Stores the power lines that need to be built in the given  powerLines
 * array, and returns the number of power lines stored. Assumes that the
 * powerLines array is large enough to store all required power lines.
 */
int planGrid2(struct place cities[], int numCities,
              struct place powerPlants[], int numPowerPlants,
              struct powerLine powerLines[]) {
    // TODO: Complete this function
    return 0;
}
