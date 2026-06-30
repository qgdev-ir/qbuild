#include <qstruct/qstruct.h>

struct linkedlist {
	size_t length;		// length size
	size_t value_size;	// size of each value
	struct entry *entry;	// pointer to first entry
};

struct entry {
	struct entry *next;	// Next entry
	/*
	 * Value will be placed after this struct
	 * And value size is the value_size in linkedlist struct
	 */
};

