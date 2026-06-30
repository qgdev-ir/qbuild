#include <qstruct/qstruct.h>
#include <stdlib.h>

struct linkedlist {
	size_t length;		// length size
	size_t value_size;	// size of each value
	struct entry *entry;	// pointer to first entry
	struct entry *lentry;	// pointer to last entry
};

struct entry {
	struct entry *previous;	// Previous entry
	struct entry *next;	// Next entry
	/*
	 * Value will be placed after this struct
	 * And value size is the value_size in linkedlist struct
	 */
};

qstruct_result_t qstruct_linkedlist_create(qstruct_linkedlist_t *list, size_t value_size) {
	struct linkedlist *ll = malloc(sizeof(struct linkedlist));
	ll->length = 0;
	ll->value_size = value_size;
	*list = ll;
	return QSTRUCT_RESULT_OK;
}

