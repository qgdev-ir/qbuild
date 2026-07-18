#include <qstruct/_qstruct.h>

/*
 * Detects which bucket the key should be in
 */
#define HM_BUCKET_INDEX(k, ks, hm) (hm->hasher(k, ks, hm->seed) & (hm->capacity - 1 ))

struct hashmap {
	size_t length;			// How much is current array filled
	qstruct_rbtree_t *buckets;	// Buckets
	size_t capacity;		// Capacity of buckets
	qstruct_rbtree_comparator_t comparator;	// Used for handling
	double max_loadfactor;			// max load factor
	qstruct_hashmap_hasher_t hasher;	// Hash function
	long seed;				// Seed for hash function
};

struct entry {
	struct hashmap *map;
	char *value;
	size_t value_size;
	size_t key_size;
	uint8_t key[];
};

/*
 * Compares two entries
 */
static int8_t _hm_entry_comparator(char *x, char *y) {
	struct entry *e1 = (void *) x;
	struct entry *e2 = (void *) y;
	return e1->map->comparator(e1->key, e2->key);
}

/*
 * Get bucket for given entry
 * Creates the bucket if doesnt exists
 */
static inline qstruct_result_t _hm_get_bucket(struct hashmap *hm, qstruct_rbtree_t *b, struct entry *e) {
	int bucket_index = HM_BUCKET_INDEX(e->key, e->key_size, hm);
	qstruct_rbtree_t bucket = hm->buckets[bucket_index];
	if (bucket == NULL) {
		qstruct_run(qstruct_rbtree_create(&bucket, &_hm_entry_comparator));
		hm->buckets[bucket_index] = bucket;
	}
	*b = bucket;
	return QSTRUCT_RESULT_OK;
}

/*
 * Add entry to the buckets
 * In this function load factor is not checked
 */
static inline qstruct_result_t _hm_put(struct hashmap *hm, struct entry *e) {
	qstruct_rbtree_t b;
	qstruct_run(_hm_get_bucket(hm, &b, e));
	qstruct_run(qstruct_rbtree_add(b, e, sizeof(struct entry) + e->key_size));
	return QSTRUCT_RESULT_OK;
}

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

qstruct_result_t qstruct_hashmap_destroy(qstruct_hashmap_t hashmap) {
	struct hashmap *hm = hashmap;
	qstruct_rbtree_t *buckets = hm->buckets;

	for (int i = 0; i < hm->capacity; i++) {
		qstruct_rbtree_t *bucket = buckets[i];
		if (bucket != NULL) qstruct_rbtree_destroy(bucket);
	}

	free(buckets);
	free(hm);
	return QSTRUCT_RESULT_OK;
}

