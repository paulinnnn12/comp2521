// COMP2521 - Assignment 1
// Implementation of the Course Catalogue ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Catalogue.h"
#include "CatalogueStructs.h"
#include "course.h"

 
static struct node *newNode(int code, char *name, int creditPoints);
static struct node *insertNode(struct node *root, int code, char *name, int creditPoints);
static struct node *deleteNode(struct node *root, int code);
static struct node *findMinNode(struct node *root);
static struct node *findNode(struct node *root, int code);
static void freeTree(struct node *root);
static void printTree(struct node *root, FILE *out, bool *first);
static void *checkedMalloc(size_t size);
 
static struct node *nodeClosest(struct node *root, int targetCode);
static struct node *nodeClosestHelp(struct node *root, int targetCode, int *diff);
static int nodeGetRange(struct node *root, int lower, int upper, struct course courses[], int count);
////////////////////////////////////////////////////////////////////////

static int size(struct node *n);
static void updateSize(struct node *n);
static struct node *nodeAtIndex(struct node *root, int index);
static int nodeIndexOf(struct node *root, int code);
static int nodeCountLower(struct node *root, int code);
static struct node *bstConstruct(struct course courses[], int lo, int hi);
////////////////////////////////////////////////////////////////////////
// Queue Implementation
typedef struct QueueNode {
	struct node *node;
	struct QueueNode *next;
} QueueNode;

typedef struct Queue {
	QueueNode *head;
	QueueNode *tail;
} Queue;

static Queue *createQueue(void) {
	Queue *new_queue = malloc(sizeof(Queue));
	if (new_queue) {
		new_queue->head = NULL;
		new_queue->tail = NULL;
	}
	return new_queue;
}

static void enQueue(Queue *queue, struct node *node) {
	QueueNode *queueNode = malloc(sizeof(QueueNode));
	queueNode->node = node;
	queueNode->next = NULL;
	if (queue->tail == NULL) {
		queue->head = queue->tail = queueNode;
	} else {
		queue->tail->next = queueNode;
	}
	queue->tail = queueNode;
}

static QueueNode *deQueue(Queue *queue) {
	QueueNode *tem = queue->head;
	queue->head = queue->head->next;
	if (queue->head == NULL) {
		queue->tail = NULL;
	}
	return tem;
}

////////////////////////////////////////////////////////////////////////
// balancing Implementation
static int maxInt(int a, int b) {
	return (a > b)? a : b;
}
static int height(struct node *node) {
	return (node == NULL)? 0 : node->height;
}
static void updateHeight(struct node *node) {
	node->height = 1 + maxInt(height(node->left), height(node->right));
}

static struct node *rotateLeft(struct node *root) {
	struct node *rightChild = root->right;
	root->right = rightChild->left;
	rightChild->left = root;
	updateHeight(root);
	updateHeight(rightChild);
	updateSize(root);
	updateSize(rightChild);
	return rightChild;
}

static struct node *rotateRight(struct node *root) {
	struct node *leftChild = root->left;
	root->left = leftChild->right;
	leftChild->right = root;
	updateHeight(root);
	updateHeight(leftChild);
	updateSize(root);
	updateSize(leftChild);
	return leftChild;
}

static int getBalance(struct node *n) {
	return (n == NULL)? 0 : height(n->left) - height(n->right);
}
static struct node *rebalance(struct node *root) {
	updateHeight(root);
	updateSize(root);
	int balance = getBalance(root);
	if (balance < -1) {
		//right subtree is heavier
		if(getBalance(root->right) > 0) {
			//RL additional right rotation
			root->right = rotateRight(root->right);
		}
		return rotateLeft(root);
	}
	if (balance > 1) {
		//left is heavier
		if(getBalance(root->left) < 0) {
			//LR addtional left rotation
			root->left = rotateLeft(root->left);
		}
		return rotateRight(root);
	}
	return root;
}

////////////////////////////////////////////////////////////////////////
// Basic Operations

Catalogue CatalogueNew(void) {
	Catalogue catalogue = checkedMalloc(sizeof(*catalogue));

	catalogue->tree = NULL;
	catalogue->numCourses = 0;
	return catalogue;
}	

void CatalogueFree(Catalogue catalogue) {
	freeTree(catalogue->tree);
	free(catalogue);
}

void CatalogueInsert(Catalogue catalogue, int code, char *name, int creditPoints) {
	struct course course = CatalogueFind(catalogue, code);
	if (course.creditPoints != 0) {
		return;
	}
	catalogue->tree = insertNode(catalogue->tree, code, name, creditPoints);
	catalogue->numCourses += 1;
}

void CatalogueDelete(Catalogue catalogue, int code) {
	struct course course = CatalogueFind(catalogue, code);
	if (course.creditPoints == 0) {
		return;
	}
	catalogue->tree = deleteNode(catalogue->tree, code);
	catalogue->numCourses -= 1;
}

int CatalogueNumCourses(Catalogue catalogue) {
	return catalogue->numCourses;
}

struct course CatalogueFind(Catalogue catalogue, int code) {
	struct node *node = findNode(catalogue->tree, code);
	if (node == NULL) {
		return (struct course){COURSE_UNDEFINED, "", 0};
	} else {
		return node->course;
	}

}

void CataloguePrint(Catalogue catalogue, FILE *out) {
	fprintf(out, "{");
	bool first = true;
	printTree(catalogue->tree, out, &first);
	fprintf(out, "}");
}

////////////////////////////////////////////////////////////////////////
// Course Queries

struct course CatalogueClosest(Catalogue catalogue, int targetCode) {
	return nodeClosest(catalogue->tree, targetCode)->course;
}

int CatalogueLevelOrder(Catalogue catalogue, struct course courses[]) {
	int count = 0;
	if (catalogue == NULL || catalogue->tree == NULL) return count;
	
	Queue *queue = createQueue();
	enQueue(queue, catalogue->tree);
	while (queue->head != NULL) {
		QueueNode *queueNode = deQueue(queue);
		struct node *curr = queueNode->node;
		courses[count ++] = curr->course;
		free(queueNode);

		if (curr->left != NULL) enQueue(queue, curr->left);
		if (curr->right != NULL) enQueue(queue, curr->right);
	}
	free(queue);
	return count;
}

int CatalogueGetRange(Catalogue catalogue, int lowerCode, int upperCode,
                      struct course courses[]) {
	return nodeGetRange(catalogue->tree, lowerCode, upperCode, courses, 0);
}

////////////////////////////////////////////////////////////////////////
// Index Operations

struct course CatalogueAtIndex(Catalogue catalogue, int index) {
	if (catalogue == NULL || index > catalogue->numCourses - 1 || index < 0) {
		return (struct course) {COURSE_UNDEFINED, "", 0};
	}
	return nodeAtIndex(catalogue->tree, index)->course;
}

int CatalogueIndexOf(Catalogue catalogue, int code) {
	if (catalogue == NULL) return -1;
	if (findNode(catalogue->tree, code) == NULL) return -1;

	return nodeIndexOf(catalogue->tree, code);
}

int CatalogueCountLower(Catalogue catalogue, int code) {
	if (catalogue == NULL) return 0;
	return nodeCountLower(catalogue->tree, code);
}

////////////////////////////////////////////////////////////////////////
// Efficient Construction

Catalogue CatalogueConstruct(struct course courses[], int size) {
	Catalogue catalogue = checkedMalloc(sizeof(*catalogue));

	catalogue->tree = bstConstruct(courses, 0, size - 1);
	catalogue->numCourses = size;
	return catalogue;
}

////////////////////////////////////////////////////////////////////////
static void *checkedMalloc(size_t size) {
	void *p = malloc(size);
	if (p == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}
	return p;
}
static void freeTree(struct node *root) {
	if (root == NULL) {
		return;
	}
	freeTree(root->left);
	freeTree(root->right);
	free(root);
}

static struct node *newNode(int code, char *name, int creditPoints) {
	struct node *n = checkedMalloc(sizeof(struct node));
 
	n->course.code = code;
	strcpy(n->course.name, name);
	n->course.creditPoints = creditPoints;
	n->left = NULL;
	n->right = NULL;
	n->height = 1;
	n->size = 1;
	return n;
}
static struct node *insertNode(struct node *root, int code, char *name, int creditPoints) {
	if (root == NULL) {
		return newNode(code, name, creditPoints);
	}
	root->size += 1;
	if (code < root->course.code) {
		root->left = insertNode(root->left, code, name, creditPoints);
	} else{
		root->right = insertNode(root->right, code, name, creditPoints);
	}
	return rebalance(root);
}

static struct node *findMinNode(struct node *root) {
	while (root->left != NULL) {
		root = root->left;
	}
	return root;
}
static struct node *deleteNode(struct node *root, int code) {
	if (root == NULL) {
		return NULL;
	}
	root->size -= 1;
	if (root->course.code == code) {
		if (root->right == NULL) {
			struct node *tem = root->left;
			free(root);
			return tem;
		} else if (root->left == NULL) {
			struct node *tem = root->right;
			free(root);
			return tem;
		} else {
		struct node *successor = findMinNode(root->right);
		root->course = successor->course;
		root->right = deleteNode(root->right, successor->course.code);
		}
	} else if (root->course.code > code) {
		root->left = deleteNode(root->left, code);
	} else {
		root->right = deleteNode(root->right, code);
	}
	return rebalance(root);
}
static struct node *findNode(struct node *root, int code) {
	if (root == NULL) {
		return NULL;
	}
	if (root->course.code == code) {
		return root;
	} else if (root->course.code > code) {
		return findNode(root->left, code);
	} else {
		return findNode(root->right, code);
	}
}
static void printTree(struct node *root, FILE *out, bool *first) {
	if (root == NULL) {
		return;
	}	
	printTree(root->left, out, first);

	if (!*first) {
		fprintf(out, ", ");
	}
	*first = false;

	fprintf(out, "(%d, %s, %d)", root->course.code,
		root->course.name, root->course.creditPoints);

	printTree(root->right, out, first);
}

static struct node *nodeClosestHelp(struct node *root, int targetCode, int *diff) {
	*diff = targetCode - root->course.code;
	if (*diff == 0) {
		return root;
	}
	int temp;
	
	if (*diff < 0) {
		if (root->left == NULL) return root;
		temp = targetCode - root->left->course.code;
		if (temp > 0) {
			if (abs(*diff) < abs(temp)) {
				return root;
			} else {
				return root->left;
			}
		} else {
			return nodeClosestHelp(root->left, targetCode, diff);
		}
	
	} else {
		if (root->right == NULL) return root;
		temp = targetCode - root->right->course.code;
		if (temp < 0) {
			if (abs(*diff) > abs(temp)) {
				return root->right;
			} else {
				return root;
			}
		} else {
			return nodeClosestHelp(root->right, targetCode, diff);
		}

	}
}
static struct node *nodeClosest(struct node *root, int targetCode) {
	int diff = 0;
	return nodeClosestHelp(root, targetCode, &diff);
}
static int nodeGetRange(struct node *root, int lower, int upper, struct course courses[], int count) {
	if (root == NULL) {
		return count;
	}

	if (root->course.code > lower) {
		count = nodeGetRange(root->left, lower, upper, courses, count);
	}

	if (root->course.code >= lower && root->course.code <= upper) {
		courses[count] = root->course;
		count++;
	}

	if (root->course.code < upper) {
		count = nodeGetRange(root->right, lower, upper, courses, count);
	}

	return count;
}
static int size(struct node *node) {
	return (node == NULL)? 0 : node->size;
}
static void updateSize(struct node *node) {
	node->size = 1 + size(node->left) + size(node->right);
}

static struct node *nodeAtIndex(struct node *root, int index) {
	if (index > size(root->left)) {
		return nodeAtIndex(root->right, index - size(root->left) - 1);
	} else if (index < size(root->left)) {
		return nodeAtIndex(root->left, index);
	} else {
		return root;
	}
}
static int nodeIndexOf(struct node *root, int code) {
	if (code == root->course.code) {
		return size(root->left);
	} else if (code < root->course.code) {
		return nodeIndexOf(root->left, code);
	} else {
		return size(root->left) + 1 + nodeIndexOf(root->right, code);
	}
}
static int nodeCountLower(struct node *root, int code) {
	if (root == NULL) return 0;

	if (code < root->course.code) {
		return nodeCountLower(root->left, code);
	} else if (code == root->course.code) {
		return size(root->left);
	} else {
		return size(root->left) + 1 + nodeCountLower(root->right, code);
	}
}
static struct node *bstConstruct(struct course courses[], int lo, int hi) {
	if (lo > hi) return NULL;
	int mid = (lo + hi) / 2;
	
	struct node *node = newNode(courses[mid].code, 
		courses[mid].name, courses[mid].creditPoints);

	node->left = bstConstruct(courses, lo, mid - 1);
	node->right = bstConstruct(courses, mid + 1, hi);
	
	updateHeight(node);
	updateSize(node);
	return node;
}
