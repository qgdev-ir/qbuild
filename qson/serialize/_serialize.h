/*
 * Its not part of qson API its for internal use only
 */

#ifndef _qson_serialize__serialize_h_
#define _qson_serialize__serialize_h_

#include <qson/_qson.h>

#ifdef __cplusplus
extern "C" {
#endif

#define qson_ctx_has_size(ctx, required_size) (ctx->size - ctx->index - 1) < required_size
#define qson_ctx_size_check(ctx, required_size) \
	do { \
		if (qson_ctx_has_size(ctx, required_size)) \
			return QSON_RESULT_BUFFER_TOO_SMALL; \
	} while (0)
#define qson_ctx_write(ctx, chr) qson_ctx_size_check(ctx, 1); ctx->buffer[ctx->index++] = chr;
#define qson_ctx_write_buffer(ctx, buffer) \
	for (int i = 0; buffer[i] != '\0'; i++) { \
		qson_ctx_write(ctx, buffer[i]); \
	}

#ifdef __cplusplus
}
#endif
#endif
