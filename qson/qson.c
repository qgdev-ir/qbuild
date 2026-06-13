#include <stdlib.h>
#include "qson.h"
#include "_qson.h"

qson_result qson_create_deserialize_ctx(qson_deserialize_ctx_t *ctx, char *buffer, int size) {
	ctx->buffer = buffer;
	ctx->size = size;
	ctx->index = 0;
	ctx->state = QSON_DESERIALIZING_STATE_NONE;
	return QSON_RESULT_OK;
}

bool qson_is_white_space(char chr) {
	for (int i = 0; i < array_len(QSON_WHITESPACES) - 1; i++) {
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
	qson_ctx_size_check(ctx, 4);
	for (i = 0; i < array_len(QSON_BOOL_TRUE) - 1; i++) {
		if (ctx->buffer[ctx->index + i] != QSON_BOOL_TRUE[i]) {
			qson_ctx_size_check(ctx, 5);
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

qson_result qson_skip_null(qson_deserialize_ctx_t *ctx) {
	qson_ctx_size_check(ctx, 4);
	for (int i = 0; i < array_len(QSON_NULL) - 1; i++) {
		if (ctx->buffer[ctx->index] != QSON_NULL[i]) {
			return QSON_RESULT_INVALID_CHAR;
		}
		ctx->index++;
	}
	return QSON_RESULT_OK;
}

qson_result qson_read_number(qson_deserialize_ctx_t *ctx, double *value) {
	switch (ctx->buffer[ctx->index]) {
	case '0':
		ctx->index++;
		return QSON_RESULT_OK;
	case '+':
		return QSON_RESULT_INVALID_CHAR;
	}

	char *endptr;
	*value = strtod(ctx->buffer + ctx->index, &endptr);
	ctx->index = endptr - ctx->buffer;
	return QSON_RESULT_OK;
}

