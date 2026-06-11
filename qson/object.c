#include "qson.h"
#include "_qson.h"

inline static qson_result set_has_next(qson_deserialize_ctx_t *ctx, bool *has_next) {
	char current_val = ctx->buffer[ctx->index];
	switch (current_val) {
	case QSON_VALUE_SEPARATOR:
		ctx->state = QSON_DESERIALIZING_STATE_OBJECT;
		*has_next = true;
		break;
	case QSON_END_OBJECT:
		ctx->state = QSON_DESERIALIZING_STATE_NONE;
		*has_next = false;
		break;
	default:
		return QSON_RESULT_INVALID_CHAR;
	}
	ctx->index++;
	return QSON_RESULT_OK;
}

qson_result qson_start_object(qson_deserialize_ctx_t *ctx) {
	if (ctx->state != QSON_DESERIALIZING_STATE_NONE) return QSON_RESULT_INVALID_STATE;

	qson_run(_qson_skip_white_spaces(ctx));

	if (ctx->buffer[ctx->index] != QSON_BEGIN_OBJECT) return QSON_RESULT_INVALID_CHAR;
	ctx->state = QSON_DESERIALIZING_STATE_OBJECT;
	ctx->index++;
	return QSON_RESULT_OK;
}

qson_result qson_get_object_entry(qson_deserialize_ctx_t *ctx, char *key, int *key_length, qson_type *type) {
	if (ctx->state != QSON_DESERIALIZING_STATE_OBJECT) return QSON_RESULT_INVALID_STATE;

	qson_run(_qson_skip_white_spaces(ctx));

	if (ctx->buffer[ctx->index] != QSON_QUOTATION_MARK) return QSON_RESULT_INVALID_CHAR;
	ctx->state = QSON_DESERIALIZING_STATE_OBJECT_VALUE;

	qson_run(qson_read_string(ctx, key, key_length));
	qson_run(_qson_skip_white_spaces(ctx));

	if (ctx->buffer[ctx->index++] != QSON_NAME_SEPARATOR) return QSON_RESULT_INVALID_CHAR;

	qson_run(_qson_skip_white_spaces(ctx));

	if (*type == QSON_TYPE_AUTO) {
		char chr = ctx->buffer[ctx->index];
		switch (chr) {
		case QSON_QUOTATION_MARK: *type = QSON_TYPE_STRING; break;
		case QSON_BEGIN_OBJECT: *type = QSON_TYPE_OBJECT; break;
		case QSON_BEGIN_ARRAY: *type = QSON_TYPE_ARRAY; break;
		case 't':
		case 'f': *type = QSON_TYPE_BOOL; break;
		case 'n': *type = QSON_TYPE_NULL; break;
		default:
			if (('0' <= chr && chr <= '9' ) || chr == '-' || chr == '+')
				*type = QSON_TYPE_STRING;
			else
				return QSON_RESULT_INVALID_CHAR;
		}
	}

	return QSON_RESULT_OK;
}

qson_result qson_get_object_entry_value_string(qson_deserialize_ctx_t *ctx, char *value, int *value_length, bool *has_next) {
	if (ctx->state != QSON_DESERIALIZING_STATE_OBJECT_VALUE) return QSON_RESULT_INVALID_STATE;
	if (ctx->buffer[ctx->index] != QSON_QUOTATION_MARK) return QSON_RESULT_INVALID_CHAR;

	qson_run(qson_read_string(ctx, value, value_length));
	qson_run(_qson_skip_white_spaces(ctx));
	qson_run(set_has_next(ctx, has_next));

	return QSON_RESULT_OK;
}

qson_result qson_get_object_entry_value_bool(qson_deserialize_ctx_t *ctx, bool *value, bool *has_next) {
	if (ctx->state != QSON_DESERIALIZING_STATE_OBJECT_VALUE) return QSON_RESULT_INVALID_STATE;

	qson_run(qson_read_bool(ctx, value));
	qson_run(_qson_skip_white_spaces(ctx));
	qson_run(set_has_next(ctx, has_next));

	return QSON_RESULT_OK;
}

