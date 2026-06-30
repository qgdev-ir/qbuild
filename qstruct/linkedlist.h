#ifndef _qstruct_linkedlist_h_
#define _qstruct_linkedlist_h_
#ifdef __cplusplus
extern "C" {
#endif

/*
 * A pointer to actual linkedlist
 */
typedef void* qstruct_linkedlist_t;

/*
 * Creates an empty linkedlist
 */
qstruct_result_t qstruct_linkedlist_create(qstruct_linkedlist_t *list, size_t value_size);

/*
 * Adds value to end of the list
 * Time complexity: O(1)
 */
qstruct_result_t qstruct_linkedlist_add(qstruct_linkedlist_t list, void *value);

/*
 * Gets pointer of value at given index
 * Only use it when you’re sure the value won’t be removed or changed by another function or thread
 * Time complexity: O(n) (in worst case n/2)
 */
qstruct_result_t qstruct_linkedlist_getp(qstruct_linkedlist_t list, size_t index, void **value);

/*
 * Gets value at given index
 * Time complexity: O(n) (in worst case n/2)
 */
qstruct_result_t qstruct_linkedlist_get(qstruct_linkedlist_t list, size_t index, void *value);

#ifdef __cplusplus
}
#endif
#endif
