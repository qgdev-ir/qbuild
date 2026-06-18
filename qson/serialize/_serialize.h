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

#ifdef __cplusplus
}
#endif
#endif
