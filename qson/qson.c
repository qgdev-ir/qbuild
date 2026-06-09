#include "qson.h"
#include "_qson.h"

const char QSON_WHITESPACES[4] = {'\n', '\r', '\t', ' '};

qson_result qson_create_deserialize_ctx(qson_deserialize_ctx_t *ctx, char *buffer, int size) {
	ctx->buffer = buffer;
	ctx->size = size;
	ctx->index = 0;
	ctx->state = QSON_DESERIALIZING_STATE_NONE;
	return QSON_RESULT_OK;
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

