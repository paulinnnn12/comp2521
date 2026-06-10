// Definition of linked list and interface to utility functions

#ifndef LIST_H
#define LIST_H

struct list {
	struct node *head;
};

struct node {
	int value;
	struct node *next;
};

struct node *readList(int size);

struct list *readWrappedList(int size);

struct node *newNode(int value);

void printList(struct node *list);

void printWrappedList(struct list *list);

void freeList(struct node *list);

void freeWrappedList(struct list *list);

#endif

