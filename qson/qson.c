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
	int array_length = array_len(QSON_WHITESPACES);
	for (int i = 0; i < array_length; i++) {
		if (chr == QSON_WHITESPACES[i]) return true;
	}
	return false;
}

qson_result qson_skip_white_spaces(qson_deserialize_ctx_t *ctx) {
	return _qson_skip_white_spaces(ctx);
}

qson_result qson_read_bool(qson_deserialize_ctx_t *ctx, bool *value) {
	char chr = ctx->buffer[ctx->index];

	int i;
	for (i = 0; i < array_len(QSON_BOOL_TRUE) - 1; i++) {
		if (ctx->buffer[ctx->index + i] != QSON_BOOL_TRUE[i]) {
			for (i = 0; i < array_len(QSON_BOOL_FALSE) - 1; i++) {
				if (ctx->buffer[ctx->index + i] != QSON_BOOL_FALSE[i]) {
					ctx->index += i;
					return QSON_RESULT_INVALID_CHAR;
				}
			}
			*value = false;
			goto qson_read_bool_exit;
		}
	}
	*value = true;
qson_read_bool_exit:
	ctx->index += i;
	return QSON_RESULT_OK;
}

