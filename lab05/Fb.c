// Implementation of the FriendBook ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Fb.h"
#include "List.h"
#include "Map.h"
#include "Queue.h"

#define DEFAULT_CAPACITY 1 // DO NOT change this line

// DO NOT modify this struct
struct fb {
	int numPeople;
	int capacity;

	char **names; // the id of a person is simply the index
	              // that contains their name in this array

	Map nameToId; // maps names to ids

	struct adjNode **adj; // adjacency lists, kept in increasing order
};

// DO NOT modify this struct
struct adjNode {
	int v;
	struct adjNode *next;
};

static void freeAdjList(struct adjNode *list);
static void increaseCapacity(Fb fb);
static int nameToId(Fb fb, char *name);
static bool inAdjList(struct adjNode *list, int v);
static struct adjNode *newAdjNode(int v);

// Please ignore this line
static struct adjNode * __attribute__((unused)) newAdjNode(int v);

////////////////////////////////////////////////////////////////////////

// Creates a new instance of FriendBook
Fb FbNew(void) {
	Fb fb = malloc(sizeof(*fb));
	if (fb == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	fb->numPeople = 0;
	fb->capacity = DEFAULT_CAPACITY;

	fb->names = calloc(fb->capacity, sizeof(char *));
	if (fb->names == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	fb->nameToId = MapNew();

	fb->adj = calloc(fb->capacity, sizeof(struct adjNode *));
	if (fb->adj == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	return fb;
}

void FbFree(Fb fb) {
	for (int i = 0; i < fb->numPeople; i++) {
		free(fb->names[i]);
	}
	free(fb->names);

	MapFree(fb->nameToId);

	for (int i = 0; i < fb->capacity; i++) {
		freeAdjList(fb->adj[i]);
	}
	free(fb->adj);

	free(fb);
}

static void freeAdjList(struct adjNode *list) {
	struct adjNode *curr = list;
	while (curr != NULL) {
		struct adjNode *temp = curr;
		curr = curr->next;
		free(temp);
	}
}

int FbNumPeople(Fb fb) {
	return fb->numPeople;
}

bool FbAddPerson(Fb fb, char *name) {
	if (fb->numPeople == fb->capacity) {
		increaseCapacity(fb);
	}

	if (!MapContains(fb->nameToId, name)) {
		int id = fb->numPeople++;
		fb->names[id] = strdup(name);
		MapSet(fb->nameToId, name, id);
		return true;
	} else {
		return false;
	}
}

static void increaseCapacity(Fb fb) {
	int newCapacity = fb->capacity * 2;

	fb->names = realloc(fb->names, newCapacity * sizeof(char *));
	if (fb->names == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}
	for (int i = fb->capacity; i < newCapacity; i++) {
		fb->names[i] = NULL;
	}

	fb->adj = realloc(fb->adj, newCapacity * sizeof(struct adjNode));
	if (fb->adj == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}
	for (int i = fb->capacity; i < newCapacity; i++) {
		fb->adj[i] = NULL;
	}

	fb->capacity = newCapacity;
}

bool FbHasPerson(Fb fb, char *name) {
	return MapContains(fb->nameToId, name);
}

List FbGetPeople(Fb fb) {
	List l = ListNew();
	for (int id = 0; id < fb->numPeople; id++) {
		ListAppend(l, fb->names[id]);
	}
	return l;
}

bool FbIsFriend(Fb fb, char *name1, char *name2) {
	int id1 = nameToId(fb, name1);
	int id2 = nameToId(fb, name2);
	return inAdjList(fb->adj[id1], id2);
}

// Converts a name to an ID. Raises an error if the name doesn't exist.
static int nameToId(Fb fb, char *name) {
	if (!MapContains(fb->nameToId, name)) {
		fprintf(stderr, "error: person '%s' does not exist!\n", name);
		exit(EXIT_FAILURE);
	}
	return MapGet(fb->nameToId, name);
}

static bool inAdjList(struct adjNode *list, int v) {
	for (struct adjNode *curr = list; curr != NULL && curr->v <= v;
			curr = curr->next) {
		if (curr->v == v) {
			return true;
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////
// Your tasks

bool FbFriend(Fb fb, char *name1, char *name2) {
	if (FbIsFriend(fb, name1, name2)) return false;
	int num1 = nameToId(fb, name1);
	int num2 = nameToId(fb, name2);
	struct adjNode *curr = fb->adj[num1];
	if (curr == NULL) fb->adj[num1] = newAdjNode(num2);
	else {
		while (curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = newAdjNode(num2);
	}
	
	curr = fb->adj[num2];
	if (curr == NULL) fb->adj[num2] = newAdjNode(num1);
	else {
		while (curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = newAdjNode(num1);
	}
	return true;
}

int FbNumFriends(Fb fb, char *name) {
	int id = nameToId(fb, name);

	int count = 0;
	struct adjNode *curr = fb->adj[id];
	while (curr != NULL) {
		curr = curr->next;
		count ++;
	}
	return count;
}

List FbMutualFriends(Fb fb, char *name1, char *name2) {
	List l = ListNew();
	int id1 = nameToId(fb, name1), id2 = nameToId(fb, name2);
	struct adjNode *curr = fb->adj[id1];

	while (curr != NULL) {
		if (curr->v != id2) {
			if (inAdjList(fb->adj[id2], curr->v)) {
				ListAppend(l, fb->names[curr->v]);
			}
		}
		curr = curr->next;
	}
	ListSort(l);
	return l;
}

bool FbUnfriend(Fb fb, char *name1, char *name2) {
	if (!FbIsFriend(fb, name1, name2)) return false;
	int id1 = nameToId(fb, name1), id2 = nameToId(fb, name2);
	struct adjNode *curr = fb->adj[id1];
	struct adjNode *tem = NULL;
	if (curr->v == id2) {
		fb->adj[id1] = NULL;
		free(curr);
	} else {
		while (curr->next != NULL) {
			if (curr->next->v == id2) {
				tem = curr->next;
				curr->next = curr->next->next;
				free(tem);
				break;
			}
			curr = curr->next;
		}
	}
	curr = fb->adj[id2];
	if (curr->v == id1) {
		fb->adj[id2] = NULL;
		free(curr);
	} else {
		while (curr->next != NULL) {
			if (curr->next->v == id1) {
				tem = curr->next;
				curr->next = curr->next->next;
				free(tem);
				break;
			}
			curr = curr->next;
		}
	}

	return true;
}
int FbFriendRecs1(Fb fb, char *name, struct recommendation recs[]) {
	int id = nameToId(fb, name);
	int n = fb->numPeople;

	// Mark which people are already friends of `name` (or are `name` themself)
	bool *isFriend = calloc(n, sizeof(bool));

	isFriend[id] = true;
	for (struct adjNode *curr = fb->adj[id]; curr != NULL; curr = curr->next) {
		isFriend[curr->v] = true;
	}

	// For every non-friend, count how many of `name`'s friends they're
	// also friends with (i.e. the number of mutual friends)
	int *mutualCount = calloc(n, sizeof(int));

	for (struct adjNode *f = fb->adj[id]; f != NULL; f = f->next) {
		for (struct adjNode *fof = fb->adj[f->v]; fof != NULL; fof = fof->next) {
			int candidate = fof->v;
			if (!isFriend[candidate]) {
				mutualCount[candidate]++;
			}
		}
	}

	// Build the recommendations array from the counts
	int numRecs = 0;
	for (int i = 0; i < n; i++) {
		if (mutualCount[i] > 0) {
			strcpy(recs[numRecs].name, fb->names[i]);
			recs[numRecs].numMutualFriends = mutualCount[i];
			numRecs++;
		}
	}

	free(isFriend);
	free(mutualCount);

	// Sort recommendations in descending order of mutual friend count
	for (int i = 0; i < numRecs - 1; i++) {
		int best = i;
		for (int j = i + 1; j < numRecs; j++) {
			if (recs[j].numMutualFriends > recs[best].numMutualFriends) {
				best = j;
			}
		}
		if (best != i) {
			struct recommendation tmp = recs[i];
			recs[i] = recs[best];
			recs[best] = tmp;
		}
	}

	return numRecs;
}

////////////////////////////////////////////////////////////////////////
// Optional task

List FbFriendRecs2(Fb fb, char *name) {
	// TODO
	List l = ListNew();
	return l;
}

////////////////////////////////////////////////////////////////////////

// Creates a new adjacency list node
static struct adjNode *newAdjNode(int v) {
	struct adjNode *n = malloc(sizeof(*n));
	if (n == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	n->v = v;
	n->next = NULL;
	return n;
}

