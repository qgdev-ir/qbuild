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

#ifdef __cplusplus
}
#endif
#endif
