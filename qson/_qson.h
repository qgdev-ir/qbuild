/*
 * Its not part of qson API its for internal use only
 */

#ifndef _qson__qson_h_
#define _qson__qson_h_
#ifdef __cplusplus
extern "C" {
#endif

#define array_len(a) (sizeof(a) / sizeof(a[0]))
#define qson_run(call) \
	do { \
		qson_result res = call; \
		if (res != QSON_RESULT_OK) return res; \
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

#ifdef __cplusplus
}
#endif
#endif
