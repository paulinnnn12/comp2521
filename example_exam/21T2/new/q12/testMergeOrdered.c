// testMergeOrdered.c

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct list *mergeOrdered(struct list *list1, struct list *list2);

int main(int argc, char *argv[]) {
    char buffer[1024];

    char *line1 = fgets(buffer, sizeof(buffer), stdin);
    struct list *list1 = ListRead(line1);
    printf("list1: ");
    ListShow(list1);

    char *line2 = fgets(buffer, sizeof(buffer), stdin);
    struct list *list2 = ListRead(line2);
    printf("list2: ");
    ListShow(list2);

    struct list *merged = mergeOrdered(list1, list2);
    printf("merged list: ");
    ListShow(merged);

    ListFree(list1);
    ListFree(list2);
    ListFree(merged);
}

