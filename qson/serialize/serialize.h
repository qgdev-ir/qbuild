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
	QSON_SERIALIZE_STATE_OBJECT = 1,	// writing an object
	QSON_SERIALIZE_STATE_ARRAY = 2,		// writing an object
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

/*
 * Finish buffer with a null terminator
 * Requires state NONE
 */
qson_result qson_end_serialize_ctx(qson_serialize_ctx_t *ctx);

/*
 * Writes a string value with needed escapes and with qutations
 * Ignores state
 */
qson_result qson_write_string(qson_serialize_ctx_t *ctx, char *value);

/*
 * Writes a number value
 * Ignores state
 */
qson_result qson_write_number(qson_serialize_ctx_t *ctx, double value);

#ifdef __cplusplus
}
#endif

#include "object.h"
#include "array.h"

#endif
