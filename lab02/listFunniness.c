
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int listFunniness(struct node *list);

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

	int funniness = listFunniness(list);
	printf("The funniness of the list is: %d\n", funniness);

	freeList(list);
	return 0;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
////////////////////////////////////////////////////////////////////////
// Your task

int listFunniness(struct node *list) {
	if (list == NULL) return 0;
	if (list->next == NULL) {
		if (list->value == 67) return 1;
		else return 0;
	}
	if (list->value == 67 || (list->value == 6 && list->next->value == 7)) {
		return listFunniness(list->next) + 1;
	} else {
		return listFunniness(list->next);
	}
}

