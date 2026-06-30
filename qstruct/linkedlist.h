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

#ifdef __cplusplus
}
#endif
#endif
