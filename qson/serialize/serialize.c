#include <qson/qson.h>
#include "_serialize.h"

qson_result qson_create_serialize_ctx(qson_serialize_ctx_t *ctx, char *buffer, int size) {
	ctx->buffer = buffer;
	ctx->size = size;
	ctx->index = 0;
	ctx->state = QSON_SERIALIZE_STATE_NONE;
	return QSON_RESULT_OK;
}

qson_result qson_end_serialize_ctx(qson_serialize_ctx_t *ctx) {
	if (ctx->state != QSON_SERIALIZE_STATE_NONE) return QSON_RESULT_INVALID_STATE;
	ctx->buffer[ctx->index] = '\0';
	return QSON_RESULT_OK;
}

