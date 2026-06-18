#ifndef _qson_serialize_h_
#define _qson_serialize_h_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Current state of serialization
 */
typedef enum {
	QSON_SERIALIZE_STATE_NONE = 0,		// no specific serialization is running
} qson_serialize_state;

/*
 * Context for serilizing a json
 */
typedef struct {
	char *buffer;	// Buffer which json should be writen in
	int size;	// Size of the buffer
	int index;	// Current index in buffer
	qson_serialize_state state;	// Current state of serialization
} qson_serialize_ctx_t;

/*
 * Create a serialize context for given byte buffer
 */
qson_result qson_create_serialize_ctx(qson_serialize_ctx_t *ctx, char *buffer, int size);

#ifdef __cplusplus
}
#endif

#include "object.h"

#endif
