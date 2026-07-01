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
	uint8_t value[];	// Value of entry
};

/*
 * Gets pointer of entry at given index
 */
static inline qstruct_result_t _ll_getp(struct linkedlist *ll, struct entry **entry, size_t index) {
	size_t length = ll->length;
	if (length <= index) return QSTRUCT_RESULT_INDEX_OUTOF_BOUND;
	int i;
	struct entry *found_entry;
	if (ll->length / 2 < index) {
		i = length - 1;
		found_entry = ll->lentry;
		while (i != index) {
			found_entry = found_entry->previous;
			i--;
		}
	} else {
		i = 0;
		found_entry = ll->entry;
		while (i != index) {
			found_entry = found_entry->next;
			i++;
		}
	}
	*entry = found_entry;
	return QSTRUCT_RESULT_OK;
}

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
	memcpy(new_entry->value, value, ll->value_size);
	ll->length++;
	return QSTRUCT_RESULT_OK;
}

qstruct_result_t qstruct_linkedlist_getp(qstruct_linkedlist_t list, size_t index, void **value) {
	struct linkedlist *ll = list;
	struct entry *entry;
	qstruct_result_t res = _ll_getp(ll, &entry, index);
	if (res != QSTRUCT_RESULT_OK) return res;
	*value = entry->value;
	return QSTRUCT_RESULT_OK;
}

qstruct_result_t qstruct_linkedlist_get(qstruct_linkedlist_t list, size_t index, void *value) {
	struct linkedlist *ll = list;
	void *src;
	qstruct_result_t res = qstruct_linkedlist_getp(list, index, &src);
	if (res != QSTRUCT_RESULT_OK) {
		return res;
	}
	memcpy(value, src, ll->value_size);
	return QSTRUCT_RESULT_OK;
}

qstruct_result_t qstruct_linkedlist_destroy(qstruct_linkedlist_t list) {
	struct linkedlist *ll = list;
	struct entry *entry = ll->entry;
	while (entry != NULL) {
		struct entry *next_entry = entry->next;
		free(entry);
		entry = next_entry;
	}
	free(ll);
	return QSTRUCT_RESULT_OK;
}

size_t qstruct_linkedlist_length(qstruct_linkedlist_t list) {
	struct linkedlist *ll = list;
	return ll->length;
}

qstruct_result_t qstruct_linkedlist_remove(qstruct_linkedlist_t list, size_t index) {
	struct linkedlist *ll = list;
	struct entry *entry;
	qstruct_result_t res = _ll_getp(ll, &entry, index);
	if (res != QSTRUCT_RESULT_OK) return res;
	struct entry *previous = entry->previous;
	struct entry *next = entry->next;

	if (previous == NULL) {
		ll->entry = next;
	} else {
		previous->next = next;
	}

	if (next == NULL) {
		ll->lentry = previous;
	} else {
		next->previous = previous;
	}
	ll->length--;
	return QSTRUCT_RESULT_OK;
}

