#ifndef _qson_object_h_
#define _qson_object_h_
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Start deserializing an object and set context state to OBJECT
 * Requires state NONE
 */
qson_result qson_start_object(qson_deserialize_ctx_t *ctx);

/*
 * Start deserializing a entry of an object and set context state to OBJECT_VALUE
 * Requires state OBJECT
 */
qson_result qson_get_object_entry(qson_deserialize_ctx_t *ctx, char *key, int *key_length, qson_type *type);

#ifdef __cplusplus
}
#endif
#endif
