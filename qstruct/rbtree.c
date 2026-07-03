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

