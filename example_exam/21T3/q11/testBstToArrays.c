// Main program for testing bstToArrays

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

void bstToArrays(struct node *t, char keys[], int parents[], int leftSiblings[]);

int main(int argc, char *argv[]) {
	char buffer[1024];

	char *line1 = fgets(buffer, sizeof(buffer), stdin);
	struct node *t = getBST(line1);
	printf("\nDisplaying tree (sideways) \n");
	showBSTree(t);

	int sizeBST = BSTreeNumNodes(t);

	char *keys = malloc(sizeBST * sizeof(char));
	int *parents = malloc(sizeBST * sizeof(int));
	int *leftSiblings = malloc(sizeBST * sizeof(int));
	
	for (int i = 0; i < sizeBST; i++) {
		keys[i] = 'A';
		parents[i] = 0;
		leftSiblings[i] = 0;
	}

	printf("\n -------  \n");
	bstToArrays(t, keys, parents, leftSiblings);

	fprintf(stdout, "keys:\n");
	for (int i = 0; i < sizeBST; i++) {
		fprintf(stdout, " %c ", keys[i]);
	}
	fprintf(stdout, "\n");

	fprintf(stdout, "parents:\n");
	for (int i = 0; i < sizeBST; i++) {
		fprintf(stdout, "%2d ", parents[i]);
	}
	fprintf(stdout, "\n");

	fprintf(stdout, "leftSiblings:\n");
	for (int i = 0; i < sizeBST; i++) {
		fprintf(stdout, "%2d ", leftSiblings[i]);
	}
	fprintf(stdout, "\n");

	printf(" -------  \n");

	freeBSTree(t);
	free(keys);
	free(parents);
	free(leftSiblings);

	return 0;
}

