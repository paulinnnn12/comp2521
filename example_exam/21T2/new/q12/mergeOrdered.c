// mergeOrdered.c ... implementation of mergeOrdered function

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void helper (struct node * new,struct node *node1, struct node *node2) {
    if (node1 == NULL && node2 == NULL) {
        return;
    }

    if (node1 != NULL && node2 == NULL) {
        new->next = newNode(node1->value);
        helper(new->next, node1->next, node2);
    } else if (node1 == NULL && node2 != NULL) {
        new->next = newNode(node2->value);
        helper(new->next, node1, node2->next);
    }
    else {
        int n1 = node1->value;
        int n2 = node2->value;
        if (n1 > n2) {
            new->next = newNode(n2);
            helper(new->next, node1, node2->next);
        } else {
            new->next = newNode(n1);
            helper(new->next, node1->next, node2);
        }
    }
}

struct list *mergeOrdered(struct list *list1, struct list *list2) {
    struct list *new = ListNew();
    int n1 = list1->first->value;
    int n2 = list2->first->value;
    if (n1 < n2) {
        new->first = newNode(n1);
        helper(new->first, list1->first->next, list2->first);
    } else {
        new->first = newNode(n2);
        helper(new->first, list1->first, list2->first->next);
    }

    return new;
}

