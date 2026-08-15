// Linked list utility functions

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

// Creates a new empty list
List ListNew(void) {
    List l = malloc(sizeof(*l));
    assert(l != NULL);
    l->first = NULL;
    l->last = NULL;
    return l;
}

// Creates a new list node
struct node *newNode(int value) {
    struct node *n = malloc(sizeof(*n));
    assert(n != NULL);
    n->value = value;
    n->next = NULL;
    return n;
}

// Frees all memory associated with the given list
void ListFree(List l) {
    struct node *curr = l->first;
    while (curr != NULL) {
        struct node *prev = curr;
        curr = curr->next;
        free(prev);
    }
    free(l);
}

// Prints a list to stdout
void ListShow(List l) {
    struct node *curr;
    bool first = true;
    for (curr = l->first; curr != NULL; curr = curr->next) {
        if (!first) {
            printf(", ");
        }
        printf("%d", curr->value);
        first = false;
    }
    printf("\n");
}

// Creates a list by reading integer values from a line 
List ListRead(char *line) {
    char delim[] = ", ";
    int key;

    struct node *head = NULL;
    struct node *curr = NULL;

    char *token = strtok(line, delim);

    while (token != NULL) {
        if (sscanf(token, "%d", &key) == 1) {
            if (head == NULL) {
                head = newNode(key);
                curr = head;
            } else {
                curr->next = newNode(key);
                curr = curr->next;
            }
        }

        token = strtok(NULL, delim);
    }

    List l = ListNew();
    l->first = head;
    l->last = curr;
    return l;
}

