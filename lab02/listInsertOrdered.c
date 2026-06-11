
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

bool listIsSorted(struct node *list);
struct node *listInsertOrdered(struct node *list, int value);

int main(void) {
	printf("Enter list size: ");
	int size = 0;
	if (scanf("%d", &size) == 0) {
		fprintf(stderr, "error: failed to read list size\n");
		exit(EXIT_FAILURE);
	} else if (size < 0) {
		fprintf(stderr, "error: invalid list size\n");
		exit(EXIT_FAILURE);
	}

	if (size > 0) {
		printf("Enter list values (must be in ascending order): ");
	}
	struct node *list = readList(size);
	if (!listIsSorted(list)) {
		fprintf(stderr, "error: list is not in ascending order\n");
		exit(EXIT_FAILURE);
	}

	printf("List: ");
	printList(list);
	printf("\n");

	printf("Enter value to insert: ");
	int value = 0;
	if (scanf("%d", &value) == 0) {
		fprintf(stderr, "error: failed to read value\n");
		exit(EXIT_FAILURE);
	}

	list = listInsertOrdered(list, value);
	printf("List after inserting %d: ", value);
	printList(list);
	printf("\n");

	freeList(list);
	return 0;
}

bool listIsSorted(struct node *list) {
	for (struct node *curr = list; curr != NULL; curr = curr->next) {
		if (curr->next != NULL && curr->value > curr->next->value) {
			return false;
		}
	}
	return true;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
////////////////////////////////////////////////////////////////////////
// Your task

struct node *listInsertOrdered(struct node *list, int value) {
	if (list == NULL) {
		return newNode(value);
	}
	
	if (list->next == NULL) {
		struct node *new = newNode(value);
		if (list->value > value) {
			new->next = list;
			return new;
		} else {
			list->next = new;
			return list;
		}
	}

	if (list->next->value > value) {
		struct node *new = newNode(value);
		new->next = list->next;
		list->next = new;
	} else {
		list->next = listInsertOrdered(list->next, value);
	}


	return list;

}

