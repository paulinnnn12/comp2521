// Implementation of BST utility functions

// !!! DO NOT MODIFY THIS FILE !!!

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BSTree.h"

/*
struct node {
    int key;
    struct node *left;
    struct node *right;
};
*/

static struct node *newNode(int k);
static void doBSTreeShow(struct node *t, int depth);

// Creates a new empty BST
struct node *BSTreeNew(void) {
    return NULL;
}

// Frees all memory associated with the given BST
void BSTreeFree(struct node *t) {
    if (t != NULL) {
        BSTreeFree(t->left);
        BSTreeFree(t->right);
        free(t);
    }
}

// Prints a BST (sideways) to stdout
void BSTreeShow(struct node *t) {
    doBSTreeShow(t, 0);
}

static void doBSTreeShow(struct node *t, int depth) {
    if (t != NULL) {
        doBSTreeShow(t->right, depth + 1);
        for (int i = 0; i < depth; i++) {
            putchar('\t');
        }
        printf("%d\n", t->key);
        doBSTreeShow(t->left, depth + 1);
    }
}

// Inserts a new key into a BST
struct node *BSTreeInsert(struct node *t, int k) {
    if (t == NULL) {
        t = newNode(k);
    } else if (k < t->key) {
        t->left = BSTreeInsert(t->left, k);
    } else if (k > t->key) {
        t->right = BSTreeInsert(t->right, k);
    }
    return t;
}

// Creates a new node containing the given key
static struct node *newNode(int k) {
    struct node *new = malloc(sizeof(*new));
    assert(new != NULL);
    new->key = k;
    new->left = NULL;
    new->right = NULL;
    return new;
}

// Creates a BST by reading integer values from a line 
struct node *BSTreeRead(char *line) {
    char delim[] = ", ";
    int key;

    struct node *t = BSTreeNew(); 

    char *tkn = strtok(line, delim);

    while (tkn != NULL) {
        int count = sscanf(tkn, "%d", &key);
        if (count == 1) {
            t = BSTreeInsert(t, key);
        }
        tkn = strtok(NULL, delim);
    }

    return t;
}

