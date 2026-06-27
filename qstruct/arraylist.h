#ifndef _qstruct_arraylist_h_
#define _qstruct_arraylist_h_
#ifdef __cplusplus
extern "C" {
#endif

#define QSTRUCT_ARRAYLIST_DEFAULT_INITIALIZE_CAPACITY	16

/*
 * A pointer to actual arraylist
 */
typedef uint64_t qstruct_arraylist_t;

/*
 * Creates an arraylist
 * value_size: size of each value in array
 * initialize_capacity: initial size of array (if 0 value of QSTRUCT_ARRAYLIST_DEFAULT_INITIALIZE_CAPACITY is used instead)
 */
qstruct_result_t qstruct_arraylist_create(qstruct_arraylist_t *arraylist, size_t value_size, size_t initialize_capacity);

#ifdef __cplusplus
}
#endif
#endif
