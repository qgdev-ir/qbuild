#ifndef _qson_deserialize_h_
#define _qson_deserialize_h_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Current state of deserialization
 */
typedef enum {
	QSON_DESERIALIZING_STATE_NONE = 0,		// no specific deserialization is running
	QSON_DESERIALIZING_STATE_OBJECT = 1,		// deserializing an object
	QSON_DESERIALIZING_STATE_OBJECT_VALUE = 2,	// deserializing value of an object
	QSON_DESERIALIZING_STATE_ARRAY = 3,		// deserializing an array
	QSON_DESERIALIZING_STATE_ARRAY_VALUE = 4,	// deserializing memeber of an array
} qson_deserialize_state;

/*
 * Context for deserilizing a json
 */
typedef struct {
	char *buffer;	// Buffer which contains the json
	int size;	// Size of the buffer
	int index;	// Current index in buffer
	qson_deserialize_state state;	// Current state of deserialization
	char flags;	// flags for current ctx
} qson_deserialize_ctx_t;

/*
 * Create a deserialize context for given byte buffer
 */
qson_result qson_create_deserialize_ctx(qson_deserialize_ctx_t *ctx, char *buffer, int size);

//
// Check if given char is a white space in a JSON
//
bool qson_is_white_space(char chr);

//
// Skip charachters until reach a non white space char
// Returns UNEXPECTED_EOF if no non-whitespace char is found before buffer end
//
qson_result qson_skip_white_spaces(qson_deserialize_ctx_t *ctx);

/*
 * Read a string in current context
 * Ignores state
 */
qson_result qson_read_string(qson_deserialize_ctx_t *ctx, char *buffer, int *size);

/*
 * Read a boolean value in current context
 * Ignores state
 */
qson_result qson_read_bool(qson_deserialize_ctx_t *ctx, bool *value);

/*
 * Skip null value
 * Ignores state
 */
qson_result qson_skip_null(qson_deserialize_ctx_t *ctx);


/*
 * Read a number value in current context and return it as a signed double
 * Ignores state
 */
qson_result qson_read_number(qson_deserialize_ctx_t *ctx, double *value);

/*
 * Create a deserialize context that deserialize an object or and array nested in current context
 * Ignores state
 */
qson_result qson_create_sub_deserialize_ctx(qson_deserialize_ctx_t *ctx, qson_deserialize_ctx_t *sub_ctx);

#ifdef __cplusplus
}
#endif

#include "object.h"
#include "array.h"

#endif

