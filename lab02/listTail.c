
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int listTail(struct node *list);

int main(void) {
	printf("Enter list size: ");
	int size = 0;
	if (scanf("%d", &size) == 0) {
		fprintf(stderr, "error: failed to read list size\n");
		exit(EXIT_FAILURE);
	} else if (size <= 0) {
		fprintf(stderr, "error: invalid list size\n");
		exit(EXIT_FAILURE);
	}

	printf("Enter list values: ");
	struct node *list = readList(size);

	printf("List: ");
	printList(list);
	printf("\n");

	int last = listTail(list);
	printf("The last element is: %d\n", last);

	freeList(list);
	return 0;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
////////////////////////////////////////////////////////////////////////
// Your task

int listTail(struct node *list) {
	if (list->next == NULL) return list->value;

	return listTail(list->next);
}

