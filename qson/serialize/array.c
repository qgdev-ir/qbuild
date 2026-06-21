#include <qson/qson.h>
#include "_serialize.h"

qson_result qson_write_array(qson_serialize_ctx_t *ctx) {
	if (ctx->state != QSON_SERIALIZE_STATE_NONE) return QSON_RESULT_INVALID_STATE;
	qson_ctx_write(ctx, QSON_BEGIN_ARRAY);
	ctx->state = QSON_SERIALIZE_STATE_ARRAY;
	return QSON_RESULT_OK;
}

