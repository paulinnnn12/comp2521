// Implementation of linked list utility functions

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct node *readList(int size) {
	struct node *head = NULL;
	struct node *curr = NULL;

	for (int i = 0; i < size; i++) {
		int value;
		if (scanf("%d", &value) != 1) {
			break;
		}

		struct node *n = newNode(value);

		if (head == NULL) {
			head = n;
		} else {
			curr->next = n;
		}
		curr = n;
	}

	return head;
}

struct list *readWrappedList(int size) {
	struct list *list = malloc(sizeof(struct list));
	if (list == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	list->head = readList(size);
	return list;
}

struct node *newNode(int value) {
	struct node *n = malloc(sizeof(struct node));
	if (n == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}
	n->value = value;
	n->next = NULL;
	return n;
}

void printList(struct node *list) {
	printf("[");
	for (struct node *curr = list; curr != NULL; curr = curr->next) {
		printf("%d", curr->value);
		if (curr->next != NULL) {
			printf(", ");
		}
	}
	printf("]");
}

void printWrappedList(struct list *list) {
	printList(list->head);
}

void freeList(struct node *list) {
	struct node *curr = list;
	while (curr != NULL) {
		struct node *temp = curr;
		curr = curr->next;
		free(temp);
	}
}

void freeWrappedList(struct list *list) {
	freeList(list->head);
	free(list);
}

