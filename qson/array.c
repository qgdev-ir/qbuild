#include "qson.h"
#include "_qson.h"

qson_result qson_start_array(qson_deserialize_ctx_t *ctx) {
	if (ctx->state != QSON_DESERIALIZING_STATE_NONE) return QSON_RESULT_INVALID_STATE;

	qson_run(_qson_skip_white_spaces(ctx));

	if (ctx->buffer[ctx->index] != QSON_BEGIN_ARRAY) return QSON_RESULT_INVALID_CHAR;
	ctx->state = QSON_DESERIALIZING_STATE_ARRAY;
	ctx->index++;
	return QSON_RESULT_OK;
}
