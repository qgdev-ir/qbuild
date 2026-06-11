//
// Qson is a json serializer/deserializer based on RFC 8259
//

#ifndef _qson_qson_h_
#define _qson_qson_h_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define QSON_BEGIN_ARRAY	'['
#define QSON_END_ARRAY		']'
#define QSON_BEGIN_OBJECT	'{'
#define QSON_END_OBJECT		'}'
#define QSON_NAME_SEPARATOR	':'
#define QSON_VALUE_SEPARATOR	','
#define QSON_QUOTATION_MARK	'"'
#define QSON_STRING_ESCAPE_CHAR	'\\'
#define QSON_BOOL_TRUE		"true"
#define QSON_BOOL_FALSE		"false"

/*
 * Current state of deserialization
 */
typedef enum {
	QSON_DESERIALIZING_STATE_NONE = 0,		// no specific deserialization is running
	QSON_DESERIALIZING_STATE_OBJECT = 1,		// deserializing an object
	QSON_DESERIALIZING_STATE_OBJECT_VALUE = 2	// deserializing value of an object
} qson_deserialize_state;

/*
 * Context for deserilizing a json
 */
typedef struct {
	char *buffer;	// Buffer which contains the json
	int size;	// Size of the buffer
	int index;	// Current index in buffer
	qson_deserialize_state state;	// Current state of deserialization
} qson_deserialize_ctx_t;

typedef enum {
	QSON_RESULT_OK = 0,			// successfull
	QSON_RESULT_UNEXPECTED_EOF = 1,		// buffer ended where it shouldnt
	QSON_RESULT_INVALID_CHAR = 2,		// a char is where it shouldnt be
	QSON_RESULT_INVALID_STATE = 3,		// current state of context is invalid for this function
	QSON_RESULT_BUFFER_TOO_SMALL = 4,	// value dont fit in given buffer
} qson_result;

typedef enum {
	QSON_TYPE_AUTO = 0,		// Type should be auto detected
	QSON_TYPE_STRING = 1,		// Type is a string
	QSON_TYPE_NUMBER = 2,		// Type is a number (double)
	QSON_TYPE_NULL = 3,		// Type is null
	QSON_TYPE_BOOL = 4,		// Type is a boolean
	QSON_TYPE_OBJECT = 5,		// Type is an object
	QSON_TYPE_ARRAY = 6,		// Type is an array
} qson_type;

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

#ifdef __cplusplus
}
#endif

#include "object.h"

#endif

