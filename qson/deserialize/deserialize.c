#include <stdlib.h>
#include <qson/qson.h>
#include "_deserialize.h"

qson_result qson_create_deserialize_ctx(qson_deserialize_ctx_t *ctx, char *buffer, int size) {
	ctx->buffer = buffer;
	ctx->size = size;
	ctx->index = 0;
	ctx->state = QSON_DESERIALIZING_STATE_NONE;
	ctx->flags = 0;
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

static inline qson_result skip_string(qson_deserialize_ctx_t *ctx) {
	qson_ctx_skip(ctx, 1);
	while (ctx->buffer[ctx->index] != QSON_QUOTATION_MARK && ctx->index < ctx->size) {
		int move = ctx->buffer[ctx->index] == '\\' ? 2 : 1;
		qson_ctx_size_check(ctx, move);
		ctx->index += move;
	}
	return QSON_RESULT_OK;
}

qson_result qson_create_sub_deserialize_ctx(qson_deserialize_ctx_t *ctx, qson_deserialize_ctx_t *sub_ctx) {
	char startChar = ctx->buffer[ctx->index];
	char endChar;
	switch(startChar) {
	case QSON_BEGIN_OBJECT: endChar = QSON_END_OBJECT; break;
	case QSON_BEGIN_ARRAY: endChar = QSON_END_ARRAY; break;
	default: return QSON_RESULT_INVALID_CHAR;
	}

	sub_ctx->buffer = ctx->buffer + ctx->index;
	sub_ctx->index = 0;
	sub_ctx->size = 0;

	int old_index = ctx->index++;
	while(ctx->buffer[ctx->index] != endChar && ctx->index < ctx->size) {
		char chr = ctx->buffer[ctx->index];
		if (chr == QSON_QUOTATION_MARK) {
			qson_run(skip_string(ctx));
		} else if (chr == startChar) {
			while (ctx->buffer[ctx->index] != endChar && ctx->index < ctx->size) {
				if (ctx->buffer[ctx->index] == QSON_QUOTATION_MARK) qson_run(skip_string(ctx));
				ctx->index++;
			}
			ctx->index++;
		}
		ctx->index++;
	}
	ctx->index++;
	sub_ctx->size = ctx->index - old_index;
	if (ctx->index >= ctx->size) return QSON_RESULT_UNEXPECTED_EOF;
	sub_ctx->state = QSON_DESERIALIZING_STATE_NONE;
	return QSON_RESULT_OK;
}

