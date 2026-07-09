#include <qson/qson.h>
#include "_serialize.h"

static inline qson_result _handle_has_next(qson_serialize_ctx_t *ctx, bool has_next) {
	if (has_next) {
		qson_ctx_write(ctx, QSON_VALUE_SEPARATOR);
	} else {
		qson_ctx_write(ctx, QSON_END_ARRAY);
		ctx->state = QSON_SERIALIZE_STATE_NONE;
	}
	return QSON_RESULT_OK;
}

qson_result qson_write_array(qson_serialize_ctx_t *ctx) {
	if (ctx->state != QSON_SERIALIZE_STATE_NONE) return QSON_RESULT_INVALID_STATE;
	qson_ctx_write(ctx, QSON_BEGIN_ARRAY);
	ctx->state = QSON_SERIALIZE_STATE_ARRAY;
	return QSON_RESULT_OK;
}

qson_result qson_write_array_entry_string(qson_serialize_ctx_t *ctx, char *value, bool has_next) {
	if (ctx->state != QSON_SERIALIZE_STATE_ARRAY) return QSON_RESULT_INVALID_STATE;
	qson_run(qson_write_string(ctx, value));
	qson_run(_handle_has_next(ctx, has_next));
	return QSON_RESULT_OK;
}

qson_result qson_write_array_entry_null(qson_serialize_ctx_t *ctx, bool has_next) {
	if (ctx->state != QSON_SERIALIZE_STATE_ARRAY) return QSON_RESULT_INVALID_STATE;
	qson_ctx_write_buffer(ctx, QSON_NULL);
	qson_run(_handle_has_next(ctx, has_next));
	return QSON_RESULT_OK;
}

qson_result qson_write_array_entry_bool(qson_serialize_ctx_t *ctx, bool value, bool has_next) {
	if (ctx->state != QSON_SERIALIZE_STATE_ARRAY) return QSON_RESULT_INVALID_STATE;
	char *buffer = value ? QSON_BOOL_TRUE : QSON_BOOL_FALSE;
	qson_ctx_write_buffer(ctx, buffer);
	qson_run(_handle_has_next(ctx, has_next));
	return QSON_RESULT_OK;
}

qson_result qson_write_array_entry_number(qson_serialize_ctx_t *ctx, double value, bool has_next) {
	if (ctx->state != QSON_SERIALIZE_STATE_ARRAY) return QSON_RESULT_INVALID_STATE;
	qson_run(qson_write_number(ctx, value));
	qson_run(_handle_has_next(ctx, has_next));
	return QSON_RESULT_OK;
}

qson_result qson_write_array_entry_subctx(qson_serialize_ctx_t *ctx, qson_serialize_ctx_t *sub_ctx) {
	if (ctx->state != QSON_SERIALIZE_STATE_ARRAY) return QSON_RESULT_INVALID_STATE;
	qson_run(qson_create_sub_serialize_ctx(ctx, sub_ctx));
	return QSON_RESULT_OK;
}

qson_result qson_write_array_entry_subctx_end(qson_serialize_ctx_t *ctx, qson_serialize_ctx_t *sub_ctx, bool has_next) {
	if (ctx->state != QSON_SERIALIZE_STATE_SUBCTX) return QSON_RESULT_INVALID_STATE;
	if (sub_ctx->state != QSON_SERIALIZE_STATE_NONE) return QSON_RESULT_INVALID_STATE;
	ctx->index = sub_ctx->index;
	qson_run(_handle_has_next(ctx, has_next));
	return QSON_RESULT_OK;
}

qson_result qson_serialize_array_end(qson_serialize_ctx_t *ctx) {
	if (ctx->state != QSON_SERIALIZE_STATE_ARRAY) return QSON_RESULT_INVALID_STATE;
	qson_run(_handle_has_next(ctx, false));
	return QSON_RESULT_OK;
}

