#include <qson/qson.h>
#include "_serialize.h"

static inline qson_result _write_object_entry(qson_serialize_ctx_t *ctx, char *key) {
	qson_run(qson_write_string(ctx, key));
	qson_ctx_write(ctx, QSON_NAME_SEPARATOR);
	return QSON_RESULT_OK;
}

static inline qson_result _handle_has_next(qson_serialize_ctx_t *ctx, bool has_next) {
	if (has_next) {
		qson_ctx_write(ctx, QSON_VALUE_SEPARATOR);
	} else {
		qson_ctx_write(ctx, QSON_END_OBJECT);
		ctx->state = QSON_SERIALIZE_STATE_NONE;
	}
	return QSON_RESULT_OK;
}

qson_result qson_write_object(qson_serialize_ctx_t *ctx) {
	if (ctx->state != QSON_SERIALIZE_STATE_NONE) return QSON_RESULT_INVALID_STATE;
	qson_ctx_write(ctx, QSON_BEGIN_OBJECT);
	ctx->state = QSON_SERIALIZE_STATE_OBJECT;
	return QSON_RESULT_OK;
}

qson_result qson_write_object_entry_string(qson_serialize_ctx_t *ctx, char *key, char *value, bool has_next) {
	if (ctx->state != QSON_SERIALIZE_STATE_OBJECT) return QSON_RESULT_INVALID_STATE;
	qson_run(_write_object_entry(ctx, key));
	qson_run(qson_write_string(ctx, value));
	qson_run(_handle_has_next(ctx, has_next));
	return QSON_RESULT_OK;
}

qson_result qson_write_object_entry_null(qson_serialize_ctx_t *ctx, char *key, bool has_next) {
	if (ctx->state != QSON_SERIALIZE_STATE_OBJECT) return QSON_RESULT_INVALID_STATE;
	qson_run(_write_object_entry(ctx, key));
	qson_ctx_write_buffer(ctx, QSON_NULL);
	qson_run(_handle_has_next(ctx, has_next));
	return QSON_RESULT_OK;
}

qson_result qson_write_object_entry_bool(qson_serialize_ctx_t *ctx, char *key, bool value, bool has_next) {
	if (ctx->state != QSON_SERIALIZE_STATE_OBJECT) return QSON_RESULT_INVALID_STATE;
	qson_run(_write_object_entry(ctx, key));
	char *buffer = value ? QSON_BOOL_TRUE : QSON_BOOL_FALSE;
	qson_ctx_write_buffer(ctx, buffer);
	qson_run(_handle_has_next(ctx, has_next));
	return QSON_RESULT_OK;
}

qson_result qson_write_object_entry_number(qson_serialize_ctx_t *ctx, char *key, double value, bool has_next) {
	if (ctx->state != QSON_SERIALIZE_STATE_OBJECT) return QSON_RESULT_INVALID_STATE;
	qson_run(_write_object_entry(ctx, key));
	qson_run(qson_write_number(ctx, value));
	qson_run(_handle_has_next(ctx, has_next));
	return QSON_RESULT_OK;
}

