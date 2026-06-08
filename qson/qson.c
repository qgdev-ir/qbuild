#include "qson.h"

inline static qson_result _qson_skip_white_spaces(qson_deserialize_ctx_t *ctx) {
	int *index = &ctx->index;
	while (qson_is_white_space(ctx->buffer[*index])) {
		(*index)++;
		if (*index >= ctx->size || ctx->buffer[*index] == 0)
			return UNEXPECTED_EOF;
	}
	return OK;
}

qson_result qson_create_deserialize_ctx(qson_deserialize_ctx_t *ctx, char *buffer, int size) {
	ctx->buffer = buffer;
	ctx->size = size;
	ctx->index = 0;
	ctx->state = NONE;
	return OK;
}

bool qson_is_white_space(char chr) {
	int array_length = sizeof(QSON_WHITESPACES) / sizeof(QSON_WHITESPACES[0]);
	for (int i = 0; i < array_length; i++) {
		if (chr == QSON_WHITESPACES[i]) return true;
	}
	return false;
}

qson_result qson_skip_white_spaces(qson_deserialize_ctx_t *ctx) {
	return _qson_skip_white_spaces(ctx);
}

