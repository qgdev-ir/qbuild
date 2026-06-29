#include <qstruct/qstruct.h>
#include <stdlib.h>
#include <string.h>

struct arraylist {
	size_t value_size;	// Size of each value
	size_t capacity;	// How much value fits in current array
	size_t length;		// How much is current array filled
	void *array;		// Current array
};

/*
 * Makes sure there is enough space for one more value
 * Extends the size of array if needed
 */
inline static void _ensure_capacity(struct arraylist *al) {
	if (al->capacity <= al->length) {
		void *old_array = al->array;
		size_t old_capacity = al->capacity;

		al->capacity *= 2;	// Doubles size of array
		al->array = malloc(al->capacity * al->value_size);

		memcpy(al->array, old_array, old_capacity * al->value_size);
		free(old_array);
	}
}

qstruct_result_t qstruct_arraylist_create(qstruct_arraylist_t *arraylist, size_t value_size, size_t initialize_capacity) {
	if (initialize_capacity == 0) initialize_capacity = QSTRUCT_ARRAYLIST_DEFAULT_INITIALIZE_CAPACITY;
	struct arraylist *al = malloc(sizeof(struct arraylist));
	al->value_size = value_size;
	al->capacity = initialize_capacity;
	al->array = malloc(initialize_capacity * value_size);
	al->length = 0;
	*arraylist = (qstruct_arraylist_t) al;
	return QSTRUCT_RESULT_OK;
}

qstruct_result_t qstruct_arraylist_add(qstruct_arraylist_t arraylist, void *value) {
	struct arraylist *al = (struct arraylist*) arraylist;
	_ensure_capacity(al);
	void *dest = al->array + al->length++ * al ->value_size;
	memcpy(dest, value, al->value_size);
	return QSTRUCT_RESULT_OK;
}

qstruct_result_t qstruct_arraylist_get(qstruct_arraylist_t arraylist, void *value, size_t index) {
	struct arraylist *al = (struct arraylist*) arraylist;
	if (index >= al->length) return QSTRUCT_RESULT_INDEX_OUTOF_BOUND;
	memcpy(value, al->array + index * al->value_size, al->value_size);
	return QSTRUCT_RESULT_OK;
}

qstruct_result_t qstruct_arraylist_remove(qstruct_arraylist_t arraylist, size_t index) {
	struct arraylist *al = (struct arraylist*) arraylist;
	if (index >= al->length) return QSTRUCT_RESULT_INDEX_OUTOF_BOUND;
	void *itemptr = al->array + index * al->value_size;
	memmove(itemptr, itemptr + al->value_size, (al->length * al->value_size) - (index * al->value_size));
	al->length--;
	return QSTRUCT_RESULT_OK;
}

size_t qstruct_arraylist_length(qstruct_arraylist_t arraylist) {
	struct arraylist *al = (struct arraylist*) arraylist;
	return al->length;

}

