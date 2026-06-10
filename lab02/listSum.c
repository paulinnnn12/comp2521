
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int listSum(struct list *list);

// int listSumhelper(struct list *list);

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

	int sum = listSum(list);
	printf("The sum of the values in the list is: %d\n", sum);

	freeWrappedList(list);
	return 0;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
// (unless you are adding function prototypes)
////////////////////////////////////////////////////////////////////////
// Your task
// int listSumhelper(struct list *list) {

// }
int listSum(struct list *list) {
	if (list == NULL) return 0;

	if (list->next == NULL) return list->value;



	return listSum(list->next) + list->value;
}

