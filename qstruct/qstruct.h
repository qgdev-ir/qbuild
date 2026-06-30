#ifndef _qstruct_qstruct_h_
#define _qstruct_qstruct_h_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Result of qstruct functions
 */
typedef enum {
	QSTRUCT_RESULT_OK = 0,		// successful
	QSTRUCT_RESULT_INDEX_OUTOF_BOUND = 1, // no value is stored in given index
} qstruct_result_t;

#ifdef __cplusplus
}
#endif

#include "arraylist.h"
#include "linkedlist.h"

#endif
