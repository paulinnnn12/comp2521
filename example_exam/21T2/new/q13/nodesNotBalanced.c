#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

// Computes the height of the subtree rooted at t (empty = -1, a single
// leaf = 0), and increments *count once for every node whose left and
// right subtree heights differ by more than 1.
static int heightAndCount(struct node *t, int *count) {
	if (t == NULL) {
		return -1;
	}

	int leftHeight = heightAndCount(t->left, count);
	int rightHeight = heightAndCount(t->right, count);

	int diff = leftHeight - rightHeight;
	if (diff < 0) diff = -diff;
	if (diff > 1) {
		(*count)++;
	}

	return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Worst case time complexity of this solution: O(n), where n is the
// number of nodes - each node's height is computed exactly once via a
// single post-order traversal (rather than recomputing height from
// scratch at every node, which would cost O(n^2) in the worst case on
// a skewed tree).
int nodesNotBalanced(struct node *t) {
	int count = 0;
	heightAndCount(t, &count);
	return count;
}
