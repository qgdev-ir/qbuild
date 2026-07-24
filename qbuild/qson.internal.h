/*
 * QBuild internal helper for qson
 */

#ifndef _qbuild_qson_internal_h_
#define _qbuild_qson_internal_h_

#include <qson/qson.h>

#ifdef __cplusplus
extern "C" {
#endif

#define qson_deserialize_run(call) do { \
		qson_result_t res = call; \
		if (res != QSON_RESULT_OK) return QBUILD_RESULT_JSON_DESERIALIZE_FAILED; \
	} while (0);

#ifdef __cplusplus
}
#endif

#endif

