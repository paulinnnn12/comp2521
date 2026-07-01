
#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

#define MAXLINE 1024

int numCommonValues(struct node *t1, struct node *t2);

int main(void) {
	char line1[MAXLINE];
	char line2[MAXLINE];

	printf("Enter values to insert in t1: ");
	fgets(line1, MAXLINE, stdin);
	struct node *t1 = bstRead(line1);

	printf("t1:\n\n");
	bstShow(t1);
	printf("\n");

	printf("Enter values to insert in t2: ");
	fgets(line2, MAXLINE, stdin);
	struct node *t2 = bstRead(line2);

	printf("t2:\n\n");
	bstShow(t2);
	printf("\n");

	int numCommon = numCommonValues(t1, t2);

	printf("Number of common values: %d\n", numCommon);

	bstFree(t1);
	bstFree(t2);
	return 0;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
////////////////////////////////////////////////////////////////////////
// Your task

// Returns the number of common values between the two given BSTs
int numCommonValues(struct node *t1, struct node *t2) {
	if (t1 == NULL || t2 == NULL) {
		return 0;
	}
	if (bstFind(t2, t1->value)) {
		return numCommonValues(t1->left, t2) + numCommonValues(t1->right, t2) + 1;
	} else {
		return numCommonValues(t1->left, t2) + numCommonValues(t1->right, t2);
	}
}

