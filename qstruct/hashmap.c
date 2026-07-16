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

