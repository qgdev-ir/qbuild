#ifndef _qstruct_rbtree_h_
#define _qstruct_rbtree_h_
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Pointer to actual red-black tree
 */
typedef void* qstruct_rbtree_t;

/*
 * Compares to values and returns a number as result:
 * -1: x is smaller than y
 * 0: values are equal
 * 1: x is bigger than y
 */
typedef int8_t (*qstruct_rbtree_comparator_t)(char *x, char *y);

/*
 * Creates a red-black tree
 */
qstruct_result_t qstruct_rbtree_create(qstruct_rbtree_t *tree, qstruct_rbtree_comparator_t comparator);

/*
 * Adds given value to the tree
 * Time complexity: O(log n)
 */
qstruct_result_t qstruct_rbtree_add(qstruct_rbtree_t tree, void *value, size_t value_size);

/*
 * Gets value in of node in tree
 * if value is a null pointer only value_size is set
 * function will use value_size as size of value pointer given
 * if value_size is zero function will set it automatically
 * value must contains fields needed by comparator
 */
qstruct_result_t qstruct_rbtree_get(qstruct_rbtree_t tree, void *value, size_t *value_size);

#ifdef __cplusplus
}
#endif
#endif
