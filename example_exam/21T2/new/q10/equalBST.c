#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

// Worst case time complexity of this solution: O(min(n1, n2)), where n1
// and n2 are the sizes of t1 and t2 - in the worst case we walk both
// trees until a difference is found or one runs out, visiting at most
// min(n1, n2) nodes.
int equalBST(struct node *t1, struct node *t2) {
	if (t1 == NULL && t2 == NULL) {
		return 1; // both empty subtrees -> equal
	}
	if (t1 == NULL || t2 == NULL) {
		return 0; // one is empty and the other isn't -> different shape
	}
	if (t1->key != t2->key) {
		return 0;
	}
	return equalBST(t1->left, t2->left) && equalBST(t1->right, t2->right);
}


