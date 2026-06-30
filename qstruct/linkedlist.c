#include <qstruct/qstruct.h>
#include <stdlib.h>
#include <string.h>

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
	ll->entry = NULL;
	ll->lentry = NULL;
	*list = ll;
	return QSTRUCT_RESULT_OK;
}

qstruct_result_t qstruct_linkedlist_add(qstruct_linkedlist_t list, void *value) {
	struct linkedlist *ll = list;
	struct entry *new_entry = malloc(sizeof(struct entry) + ll->value_size);
	if (ll->length == 0) {
		new_entry->previous = NULL;
		new_entry->next = NULL;
		ll->entry = new_entry;
	} else {
		new_entry->previous = ll->lentry;
		new_entry->next = NULL;
		ll->lentry->next = new_entry;
	}
	ll->lentry = new_entry;
	memcpy(new_entry + sizeof(struct entry), value, ll->value_size);
	ll->length++;
	return QSTRUCT_RESULT_OK;
}

