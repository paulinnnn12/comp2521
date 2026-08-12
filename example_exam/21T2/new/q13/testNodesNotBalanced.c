// testNodesNotBalanced.c

#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

int nodesNotBalanced(struct node *t);

int main(int argc, char *argv[]) {
    char buffer[1024];

    char *line = fgets(buffer, sizeof(buffer), stdin);
    struct node *t = BSTreeRead(line);
    printf("Tree:\n\n");
    BSTreeShow(t);
    printf("\n");

    int res = nodesNotBalanced(t);
    printf("nodesNotBalanced returned: %d\n", res);

    BSTreeFree(t);
}

