#include "qson.h"

inline static void _qson_skip_white_spaces(qson_deserialize_ctx_t *ctx) {
	int *index = &ctx->index;
	while (qson_is_white_space(ctx->buffer[*index])) (*index)++;
}

void qson_create_deserialize_ctx(qson_deserialize_ctx_t *ctx, char *buffer, int size) {
	ctx->buffer = buffer;
	ctx->size = size;
	ctx->index = 0;
}

bool qson_is_white_space(char chr) {
	int array_length = sizeof(QSON_WHITESPACES) / sizeof(QSON_WHITESPACES[0]);
	for (int i = 0; i < array_length; i++) {
		if (chr == QSON_WHITESPACES[i]) return true;
	}
	return false;
}

void qson_skip_white_spaces(qson_deserialize_ctx_t *ctx) {
	_qson_skip_white_spaces(ctx);
}

