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

/*
 * Destroy the hashmap
 * Time complexity: O(n)
 */
qstruct_result_t qstruct_hashmap_destroy(qstruct_hashmap_t hashmap);

/*
 * Add key and value to the tree
 * Time complexity: O(1) or O(log n) in a bad day
 */
qstruct_result_t qstruct_hashmap_add(qstruct_hashmap_t hashmap, void *key, size_t key_size, void *value, size_t value_size);

/*
 * Get value by key
 * if value is a null pointer only value_size is set
 * function will use value_size as size of value pointer given
 * if value_size is zero function will set it automatically
 * Time complexity: O(1) or O(log n) in a bad day
 */
qstruct_result_t qstruct_hashmap_get(qstruct_hashmap_t hashmap, void *key, size_t key_size, void *value, size_t *value_size);

#ifdef __cplusplus
}
#endif
#endif
