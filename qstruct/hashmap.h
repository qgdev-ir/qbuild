#ifndef _qstruct_hashmap_h_
#define _qstruct_hashmap_h_
#ifdef __cplusplus
extern "C" {
#endif

#define QSTRUCT_HASHMAP_DEFAULT_CAPACITY	16
#define QSTRUCT_HASHMAP_DEFAULT_MAX_LOADFACTOR	0.5

/*
 * A pointer to actual hashmap
 */
typedef void* qstruct_hashmap_t;

/*
 * Hash the given buffer
 */
typedef long (*qstruct_hashmap_hasher_t)(char *x, size_t size, long seed);

/*
 * Creates a hashmap
 * Time complexity: O(1)
 */
qstruct_result_t qstruct_hashmap_create(qstruct_hashmap_t *hashmap, qstruct_rbtree_comparator_t comparator, size_t capacity, double max_loadfactor, qstruct_hashmap_hasher_t hasher, long seed);

#ifdef __cplusplus
}
#endif
#endif
