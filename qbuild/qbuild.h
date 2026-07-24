#ifndef _qbuild_qbuild_h_
#define _qbuild_qbuild_h_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	QBUILD_RESULT_OK = 0, // Operation successful
	QBUILD_RESULT_JSON_DESERIALIZE_FAILED = 1, // Failed to deserialize json
	QBUILD_RESULT_JSON_SERIALIZE_FAILED = 2, // Failed to serialize json
} qbuild_result_t;

#ifdef __cplusplus
}
#endif

#endif

