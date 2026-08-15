
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BSTree.h"


int buildUp(struct node *t, int parentIndex, int index, int leftIndex,
  char keys[], int parents[], int leftSiblings[]) {
	if (t == NULL) {
		return index;
	}

	keys[index] = t->key;
	parents[index] = parentIndex;
	leftSiblings[index] = leftIndex;

	int next = index + 1;

	next = buildUp(t->left, index, next, next, keys, parents, leftSiblings);

	leftIndex = (t->left == NULL)? next : index + 1;
	next = buildUp(t->right, index, next, leftIndex, keys, parents, leftSiblings);

	return next;

}
void bstToArrays(struct node *t, char keys[], int parents[], int leftSiblings[]) {

	buildUp(t, 0, 0, 0, keys, parents, leftSiblings);
}

