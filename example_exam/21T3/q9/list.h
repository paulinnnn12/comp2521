// list.h - Interface to linked list

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

struct list {
    struct node *first;
    struct node *last;
};

// Creates a new empty list
struct list *ListNew(void);

// Creates a new list node
struct node *newNode(int value);

// Frees all memory associated with the given list
void ListFree(struct list *l);

// Prints a list to stdout
void ListShow(struct list *l);

// Creates a list by reading integer values from a line 
struct list *ListRead(char *line);

#endif

