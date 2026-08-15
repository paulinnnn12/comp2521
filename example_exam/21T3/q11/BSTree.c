/*
 Binary Search struct node *ADT implementation 
*/

// !!! DO NOT MODIFY THIS FILE !!!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "BSTree.h"


// make a new node containing key
struct node *newNode(char k) {
   struct node *new = malloc(sizeof(struct node));
   assert(new != NULL);
   new->key = k;
   new->left = new->right = NULL;
   return new;
}

// create a new empty BSTree
struct node *newBSTree() {
   return NULL;
}

// free memory associated with BSTree
void freeBSTree(struct node *t) {
   if (t != NULL) {
      freeBSTree(t->left);
      freeBSTree(t->right);
      free(t);
   }
}

// display struct node *sideways
void showBSTreeR(struct node *t, int depth) {
   if (t != NULL) {
      showBSTreeR(t->right, depth+1);
      int i;
      for (i = 0; i < depth; i++)
	  putchar('\t');            // TAB character
      printf("%c\n", t->key);
      showBSTreeR(t->left, depth+1);
   }
}

void showBSTree(struct node *t) {
   showBSTreeR(t, 0);
}


// count #nodes in BSTree
int BSTreeNumNodes(struct node *t) {
   if (t == NULL)
      return 0;
   else
      return 1 + BSTreeNumNodes(t->left) + BSTreeNumNodes(t->right);
}

// insert a new key into a BSTree
struct node *BSTreeInsert(struct node *t, char k) {
   if (t == NULL)
      t = newNode(k);
   else if (k < t->key)
      t->left = BSTreeInsert(t->left, k );
   else if (k > t->key)
      t->right = BSTreeInsert(t->right, k );
   return t;
}


struct node * getBST(char *line){

	char delim[] = ", ";
	char key;

	struct node *t = newBSTree(); 

	char *tkn = strtok(line, delim);

	while (tkn != NULL) {
		//printf("'%s'\n", tkn);
		int count = sscanf(tkn, "%c", &key) ;
		if(count == 1) {
			t = BSTreeInsert(t, key) ;
		}
			
		tkn = strtok(NULL, delim);
	}

	return t;
}


