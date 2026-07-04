#include <qstruct/_qstruct.h>
#include <stdbool.h>

#define IS_RED(n) (n != NULL && n->red)

struct rbtree {
	qstruct_rbtree_comparator_t comparator;
	struct node *root;
};

struct node {
	struct node *parent;
	struct node *right;
	struct node *left;
	bool red;
	size_t value_size;
	char value[];
};

qstruct_result_t qstruct_rbtree_create(qstruct_rbtree_t *tree, qstruct_rbtree_comparator_t comparator) {
	struct rbtree *t = malloc(sizeof(struct rbtree));
	t->comparator = comparator;
	t->root = NULL;
	*tree = t;
	return QSTRUCT_RESULT_OK;
}

