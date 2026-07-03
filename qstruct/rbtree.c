#include <qstruct/_qstruct.h>

struct rbtree {
	qstruct_rbtree_comparator_t comparator;
	struct node *root;
};

struct node {
	struct node *parent;
	struct node *right;
	struct node *left;
	bool red;
	char value[];
};

qstruct_result_t qstruct_rbtree_create(qstruct_rbtree_t *tree, qstruct_rbtree_comparator_t comparator) {
	struct rbtree *t = malloc(sizeof(struct rbtree));
	t->comparator = comparator;
	t->root = NULL;
	return QSTRUCT_RESULT_OK;
}

