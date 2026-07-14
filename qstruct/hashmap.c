#include <qstruct/_qstruct.h>

struct hashmap {
	size_t value_size;		// Size of each value
	size_t length;			// How much is current array filled
	qstruct_rbtree_t *buckets;	// Buckets
	size_t capacity;		// Capacity of buckets
};

