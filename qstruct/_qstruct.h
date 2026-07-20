/*
 * This header file is NOT part of the qstruct API
 * FOR INTERNAL USE ONLY
 */
#ifndef _qstruct__qstruct_h_
#define _qstruct__qstruct_h_

#include <qstruct/qstruct.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define qstruct_run(call) \
	do { \
		qstruct_result_t res = call; \
		if (res != QSTRUCT_RESULT_OK) return res; \
	} while (0);

#ifdef __cplusplus
}
#endif
#endif
