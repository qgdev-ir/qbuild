#include <stdio.h>
#include <qson/qson.h>
#include "_serialize.h"

qson_result qson_create_serialize_ctx(qson_serialize_ctx_t *ctx, char *buffer, int size) {
	ctx->buffer = buffer;
	ctx->size = size;
	ctx->index = 0;
	ctx->state = QSON_SERIALIZE_STATE_NONE;
	ctx->flags = 0;
	return QSON_RESULT_OK;
}

qson_result qson_end_serialize_ctx(qson_serialize_ctx_t *ctx) {
	if (ctx->state != QSON_SERIALIZE_STATE_NONE) return QSON_RESULT_INVALID_STATE;
	ctx->buffer[ctx->index] = '\0';
	return QSON_RESULT_OK;
}

static inline qson_result _qson_serialize_string_write_escaped(qson_serialize_ctx_t *ctx, char chr) {
	qson_ctx_write(ctx, QSON_STRING_ESCAPE_CHAR);
	qson_ctx_write(ctx, chr);
	return QSON_RESULT_OK;
}

qson_result qson_write_string(qson_serialize_ctx_t *ctx, char *value) {
	qson_ctx_write(ctx, QSON_QUOTATION_MARK);

	int i = 0;
	char chr;
	while ((chr = value[i]) != '\0') {
		switch (chr) {
		case '\b':
		case '\f':
		case '\n':
		case '\r':
		case '\t':
		case QSON_QUOTATION_MARK:
			qson_run(_qson_serialize_string_write_escaped(ctx, chr));
			break;
		default:
			if (chr < 32 || 126 < chr) return QSON_RESULT_INVALID_CHAR;
			qson_ctx_write(ctx, chr);
			break;
		}
		i++;
	}
	qson_ctx_write(ctx, QSON_QUOTATION_MARK);
	return QSON_RESULT_OK;
}

qson_result qson_write_number(qson_serialize_ctx_t *ctx, double value) {
	int available_size = ctx->size - ctx->index;
	int used_size = snprintf(ctx->buffer + ctx->index, available_size, "%f", value);
	if (used_size > available_size) return QSON_RESULT_BUFFER_TOO_SMALL;
	ctx->index += used_size;
	return QSON_RESULT_OK;
}

