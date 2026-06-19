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

/*
 * Add an object entry with value type of string
 * if "has_next" writes chars needed for next entry
 * and if not writes chars needed for object end and sets state to NONE
 * Requires state OBJECT
 */
qson_result qson_write_object_entry_string(qson_serialize_ctx_t *ctx, char *key, char *value, bool has_next);

#ifdef __cplusplus
}
#endif
#endif

