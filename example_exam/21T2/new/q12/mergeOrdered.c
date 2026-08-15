#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

static void appendNode(struct list *l, struct node *n) {
	if (l->first == NULL) {
		l->first = n;
	} else {
		l->last->next = n;
	}
	l->last = n;
}

// Worst case time complexity of this solution: O(n + m), where n and m
// are the lengths of list1 and list2 - each node from each input list
// is visited exactly once, and the function uses O(1) auxiliary space
// (excluding the newly allocated output nodes, which are unavoidable).
struct list *mergeOrdered(struct list *list1, struct list *list2) {
	struct list *merged = ListNew();

	struct node *n1 = list1->first;
	struct node *n2 = list2->first;

	while (n1 != NULL && n2 != NULL) {
		if (n1->value <= n2->value) {
			appendNode(merged, newNode(n1->value));
			n1 = n1->next;
		} else {
			appendNode(merged, newNode(n2->value));
			n2 = n2->next;
		}
	}

	struct node *remaining = (n1 != NULL) ? n1 : n2;
	while (remaining != NULL) {
		appendNode(merged, newNode(remaining->value));
		remaining = remaining->next;
	}

	return merged;
}
