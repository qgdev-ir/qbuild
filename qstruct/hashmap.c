#include <qstruct/_qstruct.h>

struct hashmap {
	size_t length;			// How much is current array filled
	qstruct_rbtree_t *buckets;	// Buckets
	size_t capacity;		// Capacity of buckets
	qstruct_rbtree_comparator_t comparator;	// Used for handling
	double max_loadfactor;			// max load factor
	qstruct_hashmap_hasher_t hasher;	// Hash function
	long seed;				// Seed for hash function
};

qstruct_result_t qstruct_hashmap_create(qstruct_hashmap_t *hashmap, qstruct_rbtree_comparator_t comparator, size_t capacity, double max_loadfactor, qstruct_hashmap_hasher_t hasher, long seed) {
	if (capacity == 0) capacity = QSTRUCT_HASHMAP_DEFAULT_CAPACITY;
	if (max_loadfactor == 0) max_loadfactor = QSTRUCT_HASHMAP_DEFAULT_MAX_LOADFACTOR;

	struct hashmap *hm = malloc(sizeof(struct hashmap));
	hm->length = 0;
	hm->capacity = capacity;
	hm->comparator = comparator;
	hm->max_loadfactor = max_loadfactor;
	hm->hasher = hasher;
	hm->seed = seed;

	qstruct_rbtree_t *buckets = calloc(capacity, sizeof(qstruct_rbtree_t));
	hm->buckets = buckets;

	*hashmap = hm;
	return QSTRUCT_RESULT_OK;
}

