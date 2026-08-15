#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

// Worst case time complexity of this solution: O(lengthB), since it
// stops as soon as the mismatch count exceeds the tolerance.
int isSubsequence(struct node *A, struct node *B, int t, int len) {
	struct node *va = A;
	struct node *vb = B;
	int mismatches = 0;
	for (int i = 0; i < len; i++) {
		if (va->value != vb->value) {
			mismatches++;
			if (mismatches > t) {
				return 0;
			}
		}
		va = va->next;
		vb = vb->next;
	}
	return 1;
}

// Worst case time complexity of this solution: O(lengthA * lengthB) -
// there are O(lengthA) starting positions (each window start advances
// by one node, no re-walking from the head), and each is checked in
// O(lengthB) worst case.
int numSubsequences(struct list *listA, struct list *listB, int tolerance) {
	int lengthA = 0, lengthB = 0;
	for (struct node *curr = listA->first; curr != NULL; curr = curr->next) {
		lengthA++;
	}
	for (struct node *curr = listB->first; curr != NULL; curr = curr->next) {
		lengthB++;
	}

	int numWindows = lengthA - lengthB + 1;
	int count = 0;
	struct node *windowStart = listA->first;
	for (int position = 0; position < numWindows; position++) {
		count += isSubsequence(windowStart, listB->first, tolerance, lengthB);
		windowStart = windowStart->next;
	}
	return count;
}
