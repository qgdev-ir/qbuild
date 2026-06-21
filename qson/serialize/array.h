#ifndef _qson_serialize_array_h_
#define _qson_serialize_array_h_
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Start writing an array and set context state to ARRAY
 * Requires state NONE
 */
qson_result qson_write_array(qson_serialize_ctx_t *ctx);

#ifdef __cplusplus
}
#endif
#endif

