/* Binary Search struct node *ADT interface
   Written by Ashesh Mahidadia
*/

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef BSTree_H
#define BSTree_H

#include <stdbool.h>

/* External view of struct node *(key is of type char)
   To simplify this exam setup, we are exposing the
   following types to a client.
*/

struct node {
	char key;
	struct node *left;
   struct node *right;
};


struct node *newBSTree();        // create an empty BSTree
void freeBSTree(struct node *t);   // free memory associated with BSTree
void showBSTree(struct node *t);   // display a struct node *(sideways)
struct node *BSTreeInsert(struct node *t, char k);   // insert a new key into a BSTree
int BSTreeNumNodes(struct node *t);   // count #nodes in BSTree

struct node *getBST(char *line);

#endif

