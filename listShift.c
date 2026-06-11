
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct node *listShift(struct node *list);

int main(void) {
	printf("Enter list size: ");
	int size = 0;
	if (scanf("%d", &size) != 1) {
		fprintf(stderr, "error: failed to read list size\n");
		exit(EXIT_FAILURE);
	} else if (size < 0) {
		fprintf(stderr, "error: invalid list size\n");
		exit(EXIT_FAILURE);
	}

	if (size > 0) {
		printf("Enter list values: ");
	}
	struct node *list = readList(size);

	printf("List: ");
	printList(list);
	printf("\n");

	list = listShift(list);
	printf("List after shifting: ");
	printList(list);
	printf("\n");

	freeList(list);
	return 0;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
////////////////////////////////////////////////////////////////////////
// Your task

struct node *listShift(struct node *list) {
	// TODO
	return list;
}

