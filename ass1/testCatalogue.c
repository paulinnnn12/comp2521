// COMP2521 - Assignment 1
// Tests for the Course Catalogue ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Catalogue.h"
#include "CatalogueStructs.h"
#include "course.h"

static void testBasicOperations(void);
static void testBasicOperationsEdgeCases(void);
static void checkPrint(Catalogue catalogue, char *expectedPrint);
static void checkFileContents(FILE *file, char *expectedContents);

static void testClosest(void);
static void testClosestEdgeCases(void);
static void testLevelOrder(void);
static void testLevelOrderEdgeCases(void);
static void testGetRange(void);
static void testGetRangeEdgeCases(void);

static void testBalance(void);
static void testBalance1(void);
static void testBalance2(void);
static void testBalanceLargeSequential(void);
static bool isHeightBalanced(struct node *t);
static bool doIsHeightBalanced(struct node *t, int *height);
static bool isBstOrdered(struct node *t, const struct node *lower,
                          const struct node *upper);

static void testIndexingOperations(void);
static void testIndexingOperationsEdgeCases(void);

static void testConstruct(void);
static void testConstructEdgeCases(void);

int main(void) {
	testBasicOperations();
	testBasicOperationsEdgeCases();

	testClosest();
	testClosestEdgeCases();
	testLevelOrder();
	testLevelOrderEdgeCases();
	testGetRange();
	testGetRangeEdgeCases();

	testBalance();
	testBalanceLargeSequential();

	testIndexingOperations();
	testIndexingOperationsEdgeCases();

	testConstruct();
	testConstructEdgeCases();

	printf("All basic tests passed!\n");
}

////////////////////////////////////////////////////////////////////////
// Part 1

static void testBasicOperations(void) {
	Catalogue catalogue = CatalogueNew();

	CatalogueInsert(catalogue, 2521, "Data Structures and Algorithms", 6);
	CatalogueInsert(catalogue, 1511, "Programming Fundamentals", 6);
	CatalogueInsert(catalogue, 3121, "Algorithm Design and Analysis", 6);

	assert(CatalogueNumCourses(catalogue) == 3);
	assert(CatalogueFind(catalogue, 1511).code == 1511);
	assert(CatalogueFind(catalogue, 9999).code == COURSE_UNDEFINED);

	CatalogueDelete(catalogue, 1511);
	assert(CatalogueNumCourses(catalogue) == 2);
	assert(CatalogueFind(catalogue, 1511).code == COURSE_UNDEFINED);

	checkPrint(
		catalogue,
		"{"
		"(2521, Data Structures and Algorithms, 6), "
		"(3121, Algorithm Design and Analysis, 6)"
		"}"
	);

	CatalogueFree(catalogue);
}

/**
 * Tests edge cases not covered by testBasicOperations:
 *  - an empty catalogue (print, find, delete, numCourses)
 *  - a single-course catalogue
 *  - inserting a duplicate code is a no-op (original data is kept)
 *  - deleting a non-existent code does not change numCourses
 *  - deleting a node with two children (via successor replacement),
 *    and checking the remaining courses are still printed correctly
 *    in ascending order
 */
static void testBasicOperationsEdgeCases(void) {
	// Empty catalogue
	Catalogue catalogue = CatalogueNew();
	assert(CatalogueNumCourses(catalogue) == 0);
	assert(CatalogueFind(catalogue, 1511).code == COURSE_UNDEFINED);
	checkPrint(catalogue, "{}");
	CatalogueDelete(catalogue, 1511); // no-op, should not crash
	assert(CatalogueNumCourses(catalogue) == 0);
	CatalogueFree(catalogue);

	// Single-course catalogue
	catalogue = CatalogueNew();
	CatalogueInsert(catalogue, 1511, "Programming Fundamentals", 6);
	checkPrint(catalogue, "{(1511, Programming Fundamentals, 6)}");
	CatalogueDelete(catalogue, 1511);
	assert(CatalogueNumCourses(catalogue) == 0);
	checkPrint(catalogue, "{}");
	CatalogueFree(catalogue);

	// Duplicate insert should not overwrite the existing course
	catalogue = CatalogueNew();
	CatalogueInsert(catalogue, 2521, "Data Structures and Algorithms", 6);
	CatalogueInsert(catalogue, 2521, "Some Other Name", 9);
	assert(CatalogueNumCourses(catalogue) == 1);
	struct course found = CatalogueFind(catalogue, 2521);
	assert(strcmp(found.name, "Data Structures and Algorithms") == 0);
	assert(found.creditPoints == 6);
	CatalogueFree(catalogue);

	// Deleting a code that doesn't exist should not change numCourses
	catalogue = CatalogueNew();
	CatalogueInsert(catalogue, 1, "One", 6);
	CatalogueInsert(catalogue, 2, "Two", 6);
	CatalogueDelete(catalogue, 999);
	assert(CatalogueNumCourses(catalogue) == 2);
	CatalogueFree(catalogue);

	// Deleting a node with two children requires replacing it with
	// its in-order successor
	catalogue = CatalogueNew();
	CatalogueInsert(catalogue, 50, "Fifty", 6);
	CatalogueInsert(catalogue, 30, "Thirty", 6);
	CatalogueInsert(catalogue, 70, "Seventy", 6);
	CatalogueInsert(catalogue, 20, "Twenty", 6);
	CatalogueInsert(catalogue, 40, "Forty", 6);
	CatalogueInsert(catalogue, 60, "Sixty", 6);
	CatalogueInsert(catalogue, 80, "Eighty", 6);
	CatalogueDelete(catalogue, 50); // 50 has two children
	assert(CatalogueNumCourses(catalogue) == 6);
	assert(CatalogueFind(catalogue, 50).code == COURSE_UNDEFINED);
	checkPrint(
		catalogue,
		"{(20, Twenty, 6), (30, Thirty, 6), (40, Forty, 6), "
		"(60, Sixty, 6), (70, Seventy, 6), (80, Eighty, 6)}"
	);
	CatalogueFree(catalogue);
}

static void checkPrint(Catalogue catalogue, char *expectedPrint) {
	FILE *out = tmpfile();
	CataloguePrint(catalogue, out);
	checkFileContents(out, expectedPrint);
	fclose(out);
}

/**
 * This function checks if the contents of a file matches the expected
 * contents. If the contents do not match, the program will exit with an
 * assertion error.
 */
static void checkFileContents(FILE *file, char *expectedContents) {
	fflush(file);
	fseek(file, 0, SEEK_SET);
	char *line = NULL;
	size_t n = 0;
	getline(&line, &n, file);
	if (strcmp(line, expectedContents) != 0) {
		printf("Test failed for CataloguePrint: expected \"%s\", "
		       "saw \"%s\"\n", expectedContents, line);

		assert(strcmp(line, expectedContents) == 0);
	}
	free(line);
}

////////////////////////////////////////////////////////////////////////
// Part 2

static void testClosest(void) {
	Catalogue catalogue = CatalogueNew();
	CatalogueInsert(catalogue, 1511, "Programming Fundamentals", 6);
	CatalogueInsert(catalogue, 2521, "Data Structures and Algorithms", 6);
	CatalogueInsert(catalogue, 3121, "Algorithm Design and Analysis", 6);

	assert(CatalogueClosest(catalogue, 2000).code == 1511);
	assert(CatalogueClosest(catalogue, 2500).code == 2521);
	CatalogueFree(catalogue);
}

/**
 * Tests edge cases for CatalogueClosest:
 *  - a single-course catalogue (only one possible answer)
 *  - a target that exactly matches an existing code
 *  - an explicit tie between two codes equidistant from the target,
 *    where the smaller code must be returned
 *  - a target below the smallest code and above the largest code
 */
static void testClosestEdgeCases(void) {
	Catalogue catalogue = CatalogueNew();
	CatalogueInsert(catalogue, 1511, "Programming Fundamentals", 6);
	assert(CatalogueClosest(catalogue, 9999).code == 1511);
	assert(CatalogueClosest(catalogue, -100).code == 1511);
	assert(CatalogueClosest(catalogue, 1511).code == 1511);
	CatalogueFree(catalogue);

	// Codes 1000 and 2000 are both 500 away from 1500; 1000 (the
	// smaller code) must be returned
	catalogue = CatalogueNew();
	CatalogueInsert(catalogue, 1000, "A", 6);
	CatalogueInsert(catalogue, 2000, "B", 6);
	CatalogueInsert(catalogue, 3000, "C", 6);
	assert(CatalogueClosest(catalogue, 1500).code == 1000);
	assert(CatalogueClosest(catalogue, 0).code == 1000);
	assert(CatalogueClosest(catalogue, 10000).code == 3000);
	assert(CatalogueClosest(catalogue, 2000).code == 2000);
	CatalogueFree(catalogue);
}

static void testLevelOrder(void) {
	Catalogue catalogue = CatalogueNew();

	CatalogueInsert(catalogue, 1521, "Computer Systems Fundamentals", 6);
	CatalogueInsert(catalogue, 1511, "Programming Fundamentals", 6);
	CatalogueInsert(catalogue, 3121, "Algorithm Design and Analysis", 6);
	CatalogueInsert(catalogue, 2521, "Data Structures and Algorithms", 6);
	CatalogueInsert(catalogue, 3311, "Database Systems", 6);

	struct course courses[5];
	int numCourses = CatalogueLevelOrder(catalogue, courses);
	assert(numCourses == 5);
	assert(courses[0].code == 1521);
	assert(courses[1].code == 1511);
	assert(courses[2].code == 3121);
	assert(courses[3].code == 2521);
	assert(courses[4].code == 3311);

	CatalogueFree(catalogue);
}

/**
 * Tests edge cases for CatalogueLevelOrder:
 *  - an empty catalogue returns 0 and stores nothing
 *  - a single-node catalogue returns just that node
 *  - a perfectly balanced 7-node tree, where the expected
 *    level-order is fully determined (root, then both children,
 *    then all four grandchildren) since insertion order was chosen
 *    to build that exact shape
 */
static void testLevelOrderEdgeCases(void) {
	Catalogue catalogue = CatalogueNew();
	struct course courses[10];
	assert(CatalogueLevelOrder(catalogue, courses) == 0);
	CatalogueFree(catalogue);

	catalogue = CatalogueNew();
	CatalogueInsert(catalogue, 42, "Only Course", 6);
	assert(CatalogueLevelOrder(catalogue, courses) == 1);
	assert(courses[0].code == 42);
	CatalogueFree(catalogue);

	// Inserting in this order onto an AVL tree builds the perfectly
	// balanced shape (root 40, children 20 and 60, then all four
	// grandchildren 10, 30, 50, 70), so the level order is fully
	// determined: 40, 20, 60, 10, 30, 50, 70.
	catalogue = CatalogueNew();
	int codes[] = {40, 20, 60, 10, 30, 50, 70};
	for (int i = 0; i < 7; i++) {
		char name[16];
		snprintf(name, sizeof(name), "C%d", codes[i]);
		CatalogueInsert(catalogue, codes[i], name, 6);
	}
	int n = CatalogueLevelOrder(catalogue, courses);
	assert(n == 7);
	int expected[] = {40, 20, 60, 10, 30, 50, 70};
	for (int i = 0; i < 7; i++) {
		assert(courses[i].code == expected[i]);
	}
	CatalogueFree(catalogue);
}

static void testGetRange(void) {
	Catalogue catalogue = CatalogueNew();
	CatalogueInsert(catalogue, 1511, "Programming Fundamentals", 6);
	CatalogueInsert(catalogue, 1521, "Computer Systems Fundamentals", 6);
	CatalogueInsert(catalogue, 2521, "Data Structures and Algorithms", 6);
	CatalogueInsert(catalogue, 3121, "Algorithm Design and Analysis", 6);

	struct course result[4];
	int numCourses = CatalogueGetRange(catalogue, 1500, 2600, result);
	assert(numCourses == 3);
	assert(result[0].code == 1511);
	assert(result[1].code == 1521);
	assert(result[2].code == 2521);
	CatalogueFree(catalogue);
}

/**
 * Tests edge cases for CatalogueGetRange:
 *  - a range that contains no courses at all
 *  - a range that contains every course in the catalogue
 *  - a range whose bounds exactly equal existing course codes
 *    (both bounds are inclusive)
 *  - an empty catalogue
 */
static void testGetRangeEdgeCases(void) {
	Catalogue catalogue = CatalogueNew();
	CatalogueInsert(catalogue, 1511, "A", 6);
	CatalogueInsert(catalogue, 1521, "B", 6);
	CatalogueInsert(catalogue, 2521, "C", 6);
	CatalogueInsert(catalogue, 3121, "D", 6);

	struct course result[4];

	// Range entirely below all codes
	assert(CatalogueGetRange(catalogue, 0, 100, result) == 0);

	// Range entirely above all codes
	assert(CatalogueGetRange(catalogue, 9000, 9999, result) == 0);

	// Range covering everything
	int n = CatalogueGetRange(catalogue, 0, 9999, result);
	assert(n == 4);
	assert(result[0].code == 1511);
	assert(result[3].code == 3121);

	// Bounds exactly matching existing codes (inclusive on both ends)
	n = CatalogueGetRange(catalogue, 1511, 2521, result);
	assert(n == 3);
	assert(result[0].code == 1511);
	assert(result[1].code == 1521);
	assert(result[2].code == 2521);

	// A range matching a single course exactly
	n = CatalogueGetRange(catalogue, 1521, 1521, result);
	assert(n == 1);
	assert(result[0].code == 1521);

	CatalogueFree(catalogue);

	// Empty catalogue
	catalogue = CatalogueNew();
	assert(CatalogueGetRange(catalogue, 0, 9999, result) == 0);
	CatalogueFree(catalogue);
}

////////////////////////////////////////////////////////////////////////
// Part 3

static void testBalance(void) {
	testBalance1();
	testBalance2();
}

static void testBalance1(void) {
	Catalogue catalogue = CatalogueNew();

	CatalogueInsert(catalogue, 2521, "Data Structures and Algorithms", 6);
	CatalogueInsert(catalogue, 1521, "Computer Systems Fundamentals", 6);
	CatalogueInsert(catalogue, 1511, "Programming Fundamentals", 6);

	// The tree should have been rebalanced after inserting 1511
	// NOTE: Normally, a user should not have access to the concrete
	//       representation of an ADT, but since we have #included
	//       CatalogueStructs.h, we have access for testing purposes.
	assert(isHeightBalanced(catalogue->tree));

	CatalogueFree(catalogue);
}

static void testBalance2(void) {
	Catalogue catalogue = CatalogueNew();

	CatalogueInsert(catalogue, 2521, "Data Structures and Algorithms", 6);
	CatalogueInsert(catalogue, 1521, "Computer Systems Fundamentals", 6);
	CatalogueInsert(catalogue, 3121, "Algorithm Design and Analysis", 6);
	CatalogueInsert(catalogue, 3311, "Database Systems", 6);
	CatalogueDelete(catalogue, 1521);

	// The tree should have been rebalanced after deleting 1521
	assert(isHeightBalanced(catalogue->tree));

	CatalogueFree(catalogue);
}

/**
 * Tests that the tree stays height-balanced (and remains a valid
 * BST) through a larger, adversarial sequence of operations:
 * inserting 30 courses in strictly ascending order (which would
 * degenerate into a linked list without rebalancing), then deleting
 * every course again in ascending order. Balance and BST-ordering
 * are checked after every single insertion and deletion, not just
 * at the end.
 */
static void testBalanceLargeSequential(void) {
	Catalogue catalogue = CatalogueNew();

	int n = 30;
	for (int code = 0; code < n; code++) {
		char name[16];
		snprintf(name, sizeof(name), "C%d", code);
		CatalogueInsert(catalogue, code, name, 6);
		assert(isHeightBalanced(catalogue->tree));
		assert(isBstOrdered(catalogue->tree, NULL, NULL));
		assert(CatalogueNumCourses(catalogue) == code + 1);
	}

	for (int code = 0; code < n; code++) {
		CatalogueDelete(catalogue, code);
		assert(isHeightBalanced(catalogue->tree));
		assert(isBstOrdered(catalogue->tree, NULL, NULL));
		assert(CatalogueNumCourses(catalogue) == n - code - 1);
	}

	CatalogueFree(catalogue);
}

static bool isHeightBalanced(struct node *t) {
	int height = -1;
	return doIsHeightBalanced(t, &height);
}

static bool doIsHeightBalanced(struct node *t, int *height) {
	if (t == NULL) {
		*height = -1;
		return true;
	}

	int lh = -1;
	int rh = -1;
	if (!doIsHeightBalanced(t->left, &lh) || !doIsHeightBalanced(t->right, &rh)) {
		return false;
	}
	if (abs(lh - rh) > 1) return false;
	*height = (lh > rh ? lh : rh) + 1;
	return true;
}

/**
 * Checks that the tree rooted at `t` is a valid BST, i.e. every
 * node's code is strictly between the codes of `lower` and `upper`
 * (where NULL means "no bound"). Used to verify that AVL rotations
 * preserve BST ordering, not just height balance.
 */
static bool isBstOrdered(struct node *t, const struct node *lower,
                          const struct node *upper) {
	if (t == NULL) {
		return true;
	}
	if (lower != NULL && t->course.code <= lower->course.code) {
		return false;
	}
	if (upper != NULL && t->course.code >= upper->course.code) {
		return false;
	}
	return isBstOrdered(t->left, lower, t) && isBstOrdered(t->right, t, upper);
}

////////////////////////////////////////////////////////////////////////
// Part 4

static void testIndexingOperations(void) {
	Catalogue catalogue = CatalogueNew();

	CatalogueInsert(catalogue, 2521, "Data Structures and Algorithms", 6);
	CatalogueInsert(catalogue, 1511, "Programming Fundamentals", 6);
	CatalogueInsert(catalogue, 3121, "Algorithm Design and Analysis", 6);
	CatalogueInsert(catalogue, 1521, "Computer Systems Fundamentals", 6);

	assert(CatalogueAtIndex(catalogue, 0).code == 1511);
	assert(CatalogueAtIndex(catalogue, 2).code == 2521);
	assert(CatalogueIndexOf(catalogue, 3121) == 3);
	assert(CatalogueCountLower(catalogue, 2500) == 2);

	CatalogueFree(catalogue);
}

/**
 * Tests edge cases for the indexing operations:
 *  - CatalogueAtIndex with out-of-range indices (negative, and
 *    equal to numCourses) returns COURSE_UNDEFINED
 *  - CatalogueIndexOf on a non-existent code returns -1
 *  - CatalogueCountLower for a code below the smallest course
 *    (returns 0), above the largest (returns numCourses), and equal
 *    to an existing code (that code itself must not be counted,
 *    since it must be *strictly* lower)
 */
static void testIndexingOperationsEdgeCases(void) {
	Catalogue catalogue = CatalogueNew();
	CatalogueInsert(catalogue, 1511, "A", 6);
	CatalogueInsert(catalogue, 1521, "B", 6);
	CatalogueInsert(catalogue, 2521, "C", 6);
	CatalogueInsert(catalogue, 3121, "D", 6);

	assert(CatalogueAtIndex(catalogue, -1).code == COURSE_UNDEFINED);
	assert(CatalogueAtIndex(catalogue, 4).code == COURSE_UNDEFINED);
	assert(CatalogueAtIndex(catalogue, 100).code == COURSE_UNDEFINED);

	assert(CatalogueIndexOf(catalogue, 9999) == -1);

	assert(CatalogueCountLower(catalogue, 0) == 0);
	assert(CatalogueCountLower(catalogue, 9999) == 4);
	// 1521 itself must not be counted as lower than 1521
	assert(CatalogueCountLower(catalogue, 1521) == 1);
	assert(CatalogueCountLower(catalogue, 1511) == 0);

	CatalogueFree(catalogue);

	// Empty catalogue
	catalogue = CatalogueNew();
	assert(CatalogueAtIndex(catalogue, 0).code == COURSE_UNDEFINED);
	assert(CatalogueIndexOf(catalogue, 1) == -1);
	assert(CatalogueCountLower(catalogue, 1) == 0);
	CatalogueFree(catalogue);
}

////////////////////////////////////////////////////////////////////////
// Part 5

static void testConstruct(void) {
	struct course courses[] = {
		{1511, "Programming Fundamentals", 6},
		{1521, "Computer Systems Fundamentals", 6},
		{2521, "Data Structures and Algorithms", 6},
		{3121, "Algorithm Design and Analysis", 6},
		{3311, "Database Systems", 6},
	};

	Catalogue catalogue = CatalogueConstruct(courses, 5);
	assert(CatalogueNumCourses(catalogue) == 5);
	assert(isHeightBalanced(catalogue->tree));

	CatalogueFree(catalogue);
}

/**
 * Tests edge cases for CatalogueConstruct:
 *  - constructing from an empty array (size 0) gives an empty,
 *    valid catalogue
 *  - constructing from a single-element array
 *  - the input array must not be modified by the call
 *  - the resulting catalogue must be a valid, height-balanced BST
 *    and support the indexing operations correctly
 *  - the resulting catalogue must behave like any other catalogue
 *    afterwards, i.e. further inserts/deletes should still work and
 *    keep the tree balanced
 */
static void testConstructEdgeCases(void) {
	// Empty array
	Catalogue catalogue = CatalogueConstruct(NULL, 0);
	assert(CatalogueNumCourses(catalogue) == 0);
	checkPrint(catalogue, "{}");
	CatalogueFree(catalogue);

	// Single element
	struct course single[] = {{7, "Solo Course", 6}};
	catalogue = CatalogueConstruct(single, 1);
	assert(CatalogueNumCourses(catalogue) == 1);
	assert(CatalogueFind(catalogue, 7).code == 7);
	CatalogueFree(catalogue);

	// Larger array: check the input is untouched, the tree is
	// balanced and a valid BST, and indexing operations agree with
	// the original sorted array
	struct course courses[] = {
		{10, "C10", 6}, {20, "C20", 6}, {30, "C30", 6}, {40, "C40", 6},
		{50, "C50", 6}, {60, "C60", 6}, {70, "C70", 6}, {80, "C80", 6},
	};
	int n = sizeof(courses) / sizeof(courses[0]);
	struct course coursesCopy[8];
	memcpy(coursesCopy, courses, sizeof(courses));

	catalogue = CatalogueConstruct(courses, n);

	// Input array must be unchanged
	assert(memcmp(courses, coursesCopy, sizeof(courses)) == 0);

	assert(CatalogueNumCourses(catalogue) == n);
	assert(isHeightBalanced(catalogue->tree));
	assert(isBstOrdered(catalogue->tree, NULL, NULL));
	for (int i = 0; i < n; i++) {
		assert(CatalogueAtIndex(catalogue, i).code == courses[i].code);
		assert(CatalogueIndexOf(catalogue, courses[i].code) == i);
	}

	// The constructed catalogue should support further mutation just
	// like a normal one
	CatalogueInsert(catalogue, 5, "C5", 6);
	assert(CatalogueNumCourses(catalogue) == n + 1);
	assert(isHeightBalanced(catalogue->tree));
	CatalogueDelete(catalogue, 40);
	assert(CatalogueNumCourses(catalogue) == n);
	assert(CatalogueFind(catalogue, 40).code == COURSE_UNDEFINED);
	assert(isHeightBalanced(catalogue->tree));

	CatalogueFree(catalogue);
}

////////////////////////////////////////////////////////////////////////