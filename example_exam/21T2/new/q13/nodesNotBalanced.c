// nodesNotBalanced.c ... implementation of nodesNotBalanced function

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

int levelFind(struct node *t, int level) {
    if (t == NULL) {
        return level;
    }

    int left = levelFind(t->left, level + 1);
    int right = levelFind(t->right, level + 1);
    return left > right ? left : right;
}
bool balance(struct node *t) {
    if (t->right == NULL && t->left != NULL) {
        if (levelFind(t->left, 0) > 1) {
            return false;
        }
    } else if (t->right != NULL && t->left == NULL) {
        if (levelFind(t->right, 0) > 1) {
            return false;
        }
    } else {
        int left = levelFind(t->left, 0);
        int right = levelFind(t->right, 0);
        if (abs(left - right) > 1) {
            return false;
        }
    }
    return true;
}
int helper(struct node *t, int count) {
    if (t == NULL || (t->right == NULL && t->left == NULL)) {
        return count;
    }
    if (!balance(t)) count ++;
    if (t->right == NULL && t->left != NULL) {
        return helper(t->left, count);
    } else if (t->right != NULL && t->left == NULL) {
        return helper(t->right, count);
    } else {
        return helper(t->left, count) + helper(t->right, count);
    }
    
}
int nodesNotBalanced(struct node *t) {
    int count = 0;
    return helper(t, count);
}

