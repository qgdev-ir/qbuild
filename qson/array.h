#ifndef _qson_array_h_
#define _qson_array_h_
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Start deserializing an array and set context state to ARRAY
 * Requires state NONE
 */
qson_result qson_start_array(qson_deserialize_ctx_t *ctx);

#ifdef __cplusplus
}
#endif
#endif
