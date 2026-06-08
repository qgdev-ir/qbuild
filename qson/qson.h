//
// Qson is a json serializer/deserializer based on RFC 8259
//

#ifndef _qson_qson_h_
#define _qson_qson_h_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#define QSON_BEGIN_ARRAY	'['
#define QSON_END_ARRAY		']'
#define QSON_BEGIN_OBJECT	'{'
#define QSON_END_OBJECT		'}'
#define QSON_NAME_SEPARATOR	':'
#define QSON_VALUE_SEPARATOR	','
#define QSON_QUOTATION_MARK	'"'
const char QSON_WHITESPACES[4] = {'\n', '\r', '\t', ' '};

/*
 * Context for deserilizing a json
 */
typedef struct {
	char *buffer;	// Buffer which contains the json
	int size;	// Size of the buffer
	int index;	// Current index in buffer
} qson_deserialize_ctx_t;

typedef enum {
	OK = 0,			// successfull
	UNEXPECTED_EOF = 1,	// buffer ended where it shouldnt
	INVALID_CHAR = 2,	// a char is where it shouldnt be
} qson_result;

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

#ifdef __cplusplus
}
#endif
#endif

