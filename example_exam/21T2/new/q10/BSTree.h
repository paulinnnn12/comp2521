// BSTree.h - Interface to binary search tree ADT

#ifndef BSTREE_H
#define BSTREE_H

typedef struct node *BSTree;

struct node {
    int key;
    struct node *left;
    struct node *right;
};

// Creates a new empty BSTree
struct node *BSTreeNew(void);

// Frees all memory associated with a BSTree
void BSTreeFree(struct node *t);

// Inserts a new key into a BSTree
struct node *BSTreeInsert(struct node *t, int k);

// Displays a BSTree
void BSTreeShow(struct node *t);

// Creates a struct node *by reading integer values from a line
struct node *BSTreeRead(char *line);

#endif

