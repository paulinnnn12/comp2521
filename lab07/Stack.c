// Implementation of the Stack ADT using a linked list

// !!! DO NOT MODIFY THIS FILE !!!

#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"

struct node {
    Item item;
    struct node *next;
};

struct stack {
    struct node *head;
    int size;
};

static struct node *newNode(Item it);

/**
 * Creates a new empty stack
 * Complexity: O(1)
 */
Stack StackNew(void) {
    Stack s = malloc(sizeof(*s));
    if (s == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    s->head = NULL;
    s->size = 0;
    return s;
}

/**
 * Frees all resources associated with the given stack
 * Complexity: O(n)
 */
void StackFree(Stack s) {
    struct node *curr = s->head;
    while (curr != NULL) {
        struct node *temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(s);
}

/**
 * Adds an item to the top of the stack
 * Complexity: O(1)
 */
void StackPush(Stack s, Item it) {
    struct node *n = newNode(it);
    n->next = s->head;
    s->head = n;
    s->size++;
}

static struct node *newNode(Item it) {
    struct node *n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    n->item = it;
    n->next = NULL;
    return n;
}

/**
 * Removes an item from the top of the stack and returns it
 * Assumes that the stack is not empty
 * Complexity: O(1)
 */
Item StackPop(Stack s) {
    if (s->size == 0) {
        fprintf(stderr, "error: stack is empty\n");
        exit(EXIT_FAILURE);
    }

    struct node *oldHead = s->head;
    Item it = oldHead->item;
    s->head = oldHead->next;
    free(oldHead);
    s->size--;

    return it;
}

/**
 * Gets the item at the top of the stack without removing it
 * Assumes that the stack is not empty
 * Complexity: O(1)
 */
Item StackTop(Stack s) {
    if (s->size == 0) {
        fprintf(stderr, "error: stack is empty\n");
        exit(EXIT_FAILURE);
    }

    return s->head->item;
}

/**
 * Gets the size of the given stack
 * Complexity: O(1)
 */
int StackSize(Stack s) {
    return s->size;
}

/**
 * Returns true if the stack is empty, and false otherwise
 * Complexity: O(1)
 */
bool StackIsEmpty(Stack s) {
    return s->size == 0;
}

/**
 * Prints the stack to the given file with items space-separated
 * Complexity: O(n)
 */
void StackDump(Stack s, FILE *fp) {
    for (struct node *curr = s->head; curr != NULL; curr = curr->next) {
        fprintf(fp, "%d ", curr->item);
    }
    fprintf(fp, "\n");
}

