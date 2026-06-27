#include <qstruct/qstruct.h>
#include <stdlib.h>

struct arraylist {
	size_t value_size;	// Size of each value
	size_t capacity;	// How much value fits in current array
	size_t length;		// How much is current array filled
	void *array;		// Current array
};

qstruct_result_t qstruct_arraylist_create(qstruct_arraylist_t *arraylist, size_t value_size, size_t initialize_capacity) {
	if (initialize_capacity == 0) initialize_capacity = QSTRUCT_ARRAYLIST_DEFAULT_INITIALIZE_CAPACITY;
	struct arraylist *al = malloc(sizeof(struct arraylist));
	al->value_size = value_size;
	al->capacity = initialize_capacity;
	al->array = malloc(initialize_capacity * value_size);
	al->length = 0;
	*arraylist = (qstruct_result_t) al;
	return QSTRUCT_RESULT_OK;
}

