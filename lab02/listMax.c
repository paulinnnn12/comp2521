
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int listMax(struct node *list);

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

	int max = listMax(list);
	printf("The maximum element is: %d\n", max);

	freeList(list);
	return 0;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
////////////////////////////////////////////////////////////////////////
// Your task

int listMax(struct node *list) {
	if (list->next == NULL) return list->value;

	int max = listMax(list->next);
	if (max > list->value) {
		return max;
	} else {
		return list->value;
	}
} 

