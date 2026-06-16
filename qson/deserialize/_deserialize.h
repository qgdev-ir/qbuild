/*
 * Its not part of qson API its for internal use only
 */

#ifndef _qson__deserialize_deserialize_h_
#define _qson__deserialize_deserialize_h_

#include <qson/_qson.h>

#ifdef __cplusplus
extern "C" {
#endif

#define qson_ctx_size_check(ctx, required_size) \
	do { \
		if ((ctx->size - ctx->index - 1) < required_size) return QSON_RESULT_UNEXPECTED_EOF; \
	} while (0)

inline qson_result _qson_skip_white_spaces(qson_deserialize_ctx_t *ctx) {
	int *index = &ctx->index;
	while (qson_is_white_space(ctx->buffer[*index])) {
		(*index)++;
		if (*index >= ctx->size || ctx->buffer[*index] == 0)
			return QSON_RESULT_UNEXPECTED_EOF;
	}
	return QSON_RESULT_OK;
}

/*
 * Detect current data type
 * If current given type is AUTO set detected type
 * otherwize check if given type is equal to detected type and if not return QSON_RESULT_INVALID_TYPE
 */
inline qson_result _qson_detect_type(qson_deserialize_ctx_t *ctx, qson_type *type) {
	qson_type dtype;
	char chr = ctx->buffer[ctx->index];
	switch (chr) {
	case QSON_QUOTATION_MARK: dtype = QSON_TYPE_STRING; break;
	case QSON_BEGIN_OBJECT: dtype = QSON_TYPE_OBJECT; break;
	case QSON_BEGIN_ARRAY: dtype = QSON_TYPE_ARRAY; break;
	case 't':
	case 'f': dtype = QSON_TYPE_BOOL; break;
	case 'n': dtype = QSON_TYPE_NULL; break;
	default:
		if (('0' <= chr && chr <= '9' ) || chr == '-')
			dtype = QSON_TYPE_NUMBER;
		else
			return QSON_RESULT_INVALID_CHAR;
	}

	if (*type == QSON_TYPE_AUTO || *type == dtype) {
		*type = dtype;
		return QSON_RESULT_OK;
	}
	return QSON_RESULT_INVALID_TYPE;
}

#ifdef __cplusplus
}
#endif
#endif
