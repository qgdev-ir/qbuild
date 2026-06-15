#include "qson.h"
#include "_qson.h"

inline static qson_result set_has_next(qson_deserialize_ctx_t *ctx, bool *has_next) {
	char current_val = ctx->buffer[ctx->index];
	switch (current_val) {
	case QSON_VALUE_SEPARATOR:
		ctx->state = QSON_DESERIALIZING_STATE_ARRAY;
		*has_next = true;
		break;
	case QSON_END_ARRAY:
		ctx->state = QSON_DESERIALIZING_STATE_NONE;
		*has_next = false;
		break;
	default:
		return QSON_RESULT_INVALID_CHAR;
	}
	ctx->index++;
	return QSON_RESULT_OK;
}

qson_result qson_start_array(qson_deserialize_ctx_t *ctx) {
	if (ctx->state != QSON_DESERIALIZING_STATE_NONE) return QSON_RESULT_INVALID_STATE;

	qson_run(_qson_skip_white_spaces(ctx));

	if (ctx->buffer[ctx->index] != QSON_BEGIN_ARRAY) return QSON_RESULT_INVALID_CHAR;
	ctx->state = QSON_DESERIALIZING_STATE_ARRAY;
	ctx->index++;
	return QSON_RESULT_OK;
}

qson_result qson_get_array_entry(qson_deserialize_ctx_t *ctx, qson_type *type) {
	if (ctx->state != QSON_DESERIALIZING_STATE_ARRAY) return QSON_RESULT_INVALID_STATE;
	qson_run(_qson_skip_white_spaces(ctx));
	qson_run(_qson_detect_type(ctx, type));
	ctx->state = QSON_DESERIALIZING_STATE_ARRAY_VALUE;
	return QSON_RESULT_OK;
}

qson_result qson_get_array_entry_value_string(qson_deserialize_ctx_t *ctx, char *value, int *value_length, bool *has_next) {
	if (ctx->state != QSON_DESERIALIZING_STATE_ARRAY_VALUE) return QSON_RESULT_INVALID_STATE;
	qson_run(qson_read_string(ctx, value, value_length));
	qson_run(_qson_skip_white_spaces(ctx));
	qson_run(set_has_next(ctx, has_next));
	return QSON_RESULT_OK;
}

qson_result qson_get_array_entry_value_bool(qson_deserialize_ctx_t *ctx, bool *value, bool *has_next) {
	if (ctx->state != QSON_DESERIALIZING_STATE_ARRAY_VALUE) return QSON_RESULT_INVALID_STATE;
	qson_run(qson_read_bool(ctx, value));
	qson_run(_qson_skip_white_spaces(ctx));
	qson_run(set_has_next(ctx, has_next));
	return QSON_RESULT_OK;
}

qson_result qson_get_array_entry_value_null(qson_deserialize_ctx_t *ctx, bool *has_next) {
	if (ctx->state != QSON_DESERIALIZING_STATE_ARRAY_VALUE) return QSON_RESULT_INVALID_STATE;
	qson_run(qson_skip_null(ctx));
	qson_run(_qson_skip_white_spaces(ctx));
	qson_run(set_has_next(ctx, has_next));
	return QSON_RESULT_OK;
}

qson_result qson_get_array_entry_value_number(qson_deserialize_ctx_t *ctx, double *value, bool *has_next) {
	if (ctx->state != QSON_DESERIALIZING_STATE_ARRAY_VALUE) return QSON_RESULT_INVALID_STATE;
	qson_run(qson_read_number(ctx, value));
	qson_run(_qson_skip_white_spaces(ctx));
	qson_run(set_has_next(ctx, has_next));
	return QSON_RESULT_OK;
}

qson_result qson_get_array_entry_value_sub_ctx(qson_deserialize_ctx_t *ctx, qson_deserialize_ctx_t *sub_ctx, bool *has_next) {
	if (ctx->state != QSON_DESERIALIZING_STATE_ARRAY_VALUE) return QSON_RESULT_INVALID_STATE;
	qson_run(qson_create_sub_deserialize_ctx(ctx, sub_ctx));
	qson_run(_qson_skip_white_spaces(ctx));
	qson_run(set_has_next(ctx, has_next));
	return QSON_RESULT_OK;
}

