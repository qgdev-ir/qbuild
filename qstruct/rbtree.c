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

/*
 * Fix tree after add action
 */
static inline void _rbt_fix_add(struct rbtree *t, struct node *n) {
	while (IS_RED(n->parent)) {
		struct node *p = n->parent;
		struct node *g = p->parent;
		struct node *u;
		if (g->left == p) {
			u = g->right;
			if (IS_RED(u)) {
				goto _rbt_fix_add_recolor;
			} else {
				if (n == p->right) {
					n = p;
					p = n->parent;
					g = p->parent;
					_rbt_left_rotate(t, n);
				}
				p->red = false;
				g->red = true;
				_rbt_right_rotate(t, g);
			}
		} else {
			u = g->left;
			if (IS_RED(u)) {
				goto _rbt_fix_add_recolor;
			} else {
				if (n == p->left) {
					n = p;
					p = n->parent;
					g = p->parent;
					_rbt_right_rotate(t, n);
				}
				p->red = false;
				g->red = true;
				_rbt_left_rotate(t, g);
			}
		}
		continue;
_rbt_fix_add_recolor:
		p->red = false;
		u->red = false;
		g->red = true;
		n = g;
		continue;
	}
	t->root->red = false;
}

qstruct_result_t qstruct_rbtree_create(qstruct_rbtree_t *tree, qstruct_rbtree_comparator_t comparator) {
	struct rbtree *t = malloc(sizeof(struct rbtree));
	t->comparator = comparator;
	t->root = NULL;
	*tree = t;
	return QSTRUCT_RESULT_OK;
}

qstruct_result_t qstruct_rbtree_add(qstruct_rbtree_t tree, void *value, size_t value_size) {
	struct rbtree *t = tree;
	qstruct_rbtree_comparator_t comparator = t->comparator;

	struct node *current = t->root;
	struct node *parent = current;
	bool bigchild;
	while (current != NULL) {
		parent = current;
		int8_t cres = comparator(value, current->value);
		bigchild = cres > 0;
		if (cres == 0) {
			memcpy(current->value, value, value_size);
			return QSTRUCT_RESULT_OK;
		} else if (cres < 0) {
			current = current->right;
		} else {
			current = current->left;
		}
	}

	struct node *new_node = malloc(sizeof(struct node) + value_size);
	new_node->red = true;
	new_node->parent = parent;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->value_size = value_size;
	memcpy(new_node->value, value, value_size);

	if (parent == NULL) {
		t->root = new_node;
	} else if (bigchild) {
		parent->left = new_node;
	} else {
		parent->right = new_node;
	}

	_rbt_fix_add(t, new_node);
	return QSTRUCT_RESULT_OK;
}

