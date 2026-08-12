// equalBST.c ... implementation of equalBST function

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

int equalBST(struct node *t1, struct node *t2) {
    if (t1 == NULL || t2 == NULL) {
        return 0;
    }
    if (t1->key != t2->key) {
        return 0;
    }
    
    int v1 = -1, v2 = -1;
    if (t1->left != NULL && t2->left != NULL) {
        v1 = equalBST(t1->left, t2->left);
    } if (t1->right != NULL && t2->right!= NULL) {
        v2 = equalBST(t1->right, t2->right);
    }
    if (v1 == 0 || v2 == 0) {
        return 0;
    } else {
        return 1;
    }
}
