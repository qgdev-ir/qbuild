#include "qson.h"
#include "_qson.h"

qson_result qson_start_object(qson_deserialize_ctx_t *ctx) {
	if (ctx->state != QSON_DESERIALIZING_STATE_NONE) return QSON_RESULT_INVALID_STATE;

	qson_result res = _qson_skip_white_spaces(ctx);
	if (res != QSON_RESULT_OK) return res;

	if (ctx->buffer[ctx->index] != QSON_BEGIN_OBJECT) return QSON_RESULT_INVALID_CHAR;
	ctx->state = QSON_DESERIALIZING_STATE_OBJECT;
	ctx->index++;
	return QSON_RESULT_OK;
}

qson_result qson_get_object_entry(qson_deserialize_ctx_t *ctx, char *key, int *key_length, qson_type *type) {
	if (ctx->state != QSON_DESERIALIZING_STATE_OBJECT) return QSON_RESULT_INVALID_STATE;
	_qson_skip_white_spaces(ctx);
	if (ctx->buffer[ctx->index] != QSON_QUOTATION_MARK) return QSON_RESULT_INVALID_CHAR;
	ctx->state = QSON_DESERIALIZING_STATE_OBJECT_VALUE;

	qson_result res = qson_read_string(ctx, key, key_length);
	if (res != QSON_RESULT_OK) return res;

	_qson_skip_white_spaces(ctx);
	if (ctx->buffer[ctx->index++] != QSON_NAME_SEPARATOR) return QSON_RESULT_INVALID_CHAR;
	_qson_skip_white_spaces(ctx);

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

	qson_result res = qson_read_string(ctx, value, value_length);
	if (res != QSON_RESULT_OK) return res;

	qson_result ress = _qson_skip_white_spaces(ctx);

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
	return QSON_RESULT_OK;
}
