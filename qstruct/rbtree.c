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

/*
 * Performes a right rotate
 */
static inline void _rbt_right_rotate(struct rbtree *t, struct node *n) {
	struct node *l = n->left;

	n->left = l->right;
	if (l->right != NULL) {
		l->right->parent = n;
	}

	l->parent = n->parent;
	if (n->parent == NULL) {
		t->root = l;
	} else if (n->parent->right == n) {
		n->parent->right = l;
	} else {
		n->parent->left = l;
	}

	l->right = n;
	n->parent = l;
}

/*
 * Performes a left rotate
 */
static inline void _rbt_left_rotate(struct rbtree *t, struct node *n) {
	struct node *l = n->right;

	n->right = l->left;
	if (l->left != NULL) {
		l->left->parent = n;
	}

	l->parent = n->parent;
	if (n->parent == NULL) {
		t->root = l;
	} else if (n->parent->right == n) {
		n->parent->right = l;
	} else {
		n->parent->left = l;
	}

	l->left = n;
	n->parent = l;
}

qstruct_result_t qstruct_rbtree_create(qstruct_rbtree_t *tree, qstruct_rbtree_comparator_t comparator) {
	struct rbtree *t = malloc(sizeof(struct rbtree));
	t->comparator = comparator;
	t->root = NULL;
	*tree = t;
	return QSTRUCT_RESULT_OK;
}

