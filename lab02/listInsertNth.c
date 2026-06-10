
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void listInsertNth(struct list *list, int n, int value);

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
		printf("Enter list values: ");
	}
	struct list *list = readWrappedList(size);

	printf("List: ");
	printWrappedList(list);
	printf("\n");

	printf("Enter position and value to insert: ");
	int n = 0;
	int value = 0;
	if (scanf("%d %d", &n, &value) != 2) {
		fprintf(stderr, "error: failed to read position/value\n");
		exit(EXIT_FAILURE);
	} else if (n < 0) {
		fprintf(stderr, "error: invalid position\n");
		exit(EXIT_FAILURE);
	}

	listInsertNth(list, n, value);
	printf("List after inserting %d at position %d: ", value, n);
	printWrappedList(list);
	printf("\n");

	freeWrappedList(list);
	return 0;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
// (unless you are adding function prototypes)
////////////////////////////////////////////////////////////////////////
// Your task

void listInsertNth(struct list *list, int n, int value) {
	// TODO
}

