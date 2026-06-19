#ifndef _qson_serialize_object_h_
#define _qson_serialize_object_h_
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Start writing an object and set context state to OBJECT
 * Requires state NONE
 */
qson_result qson_write_object(qson_serialize_ctx_t *ctx);

#ifdef __cplusplus
}
#endif
#endif

