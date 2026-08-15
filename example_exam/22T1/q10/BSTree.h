// BST definition and interface to utility functions

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef BSTREE_H
#define BSTREE_H

struct node {
    int key;
    struct node *left;
    struct node *right;
};

// Creates a new empty BST
struct node *BSTreeNew(void);

// Frees all memory associated with the given BST
void BSTreeFree(struct node *t);

// Prints a BST (sideways) to stdout
void BSTreeShow(struct node *t);

// Inserts a new key into a BST
struct node *BSTreeInsert(struct node *t, int k);

// Creates a BST by reading integer values from a line 
struct node *BSTreeRead(char *line);

#endif

