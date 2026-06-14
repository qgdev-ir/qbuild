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

/*
 * Start deserializing an entry of an array and set context state to ARRAY_VALUE
 * Requires state ARRAY
 */
qson_result qson_get_array_entry(qson_deserialize_ctx_t *ctx, qson_type *type);

/*
 * Read value of entry as a string
 * set context state to ARRAY if has next entry and set to NONE if not
 * Requires state ARRAY_VALUE
 */
qson_result qson_get_array_entry_value_string(qson_deserialize_ctx_t *ctx, char *value, int *value_length, bool *has_next);

/*
 * Read value of entry as boolean
 * set context state to ARRAY if has next entry and set to NONE if not
 * Requires state ARRAY_VALUE
 */
qson_result qson_get_array_entry_value_bool(qson_deserialize_ctx_t *ctx, bool *value, bool *has_next);

/*
 * Just skip the null value
 * set context state to ARRAY if has next entry and set to NONE if not
 * Requires state ARRAY_VALUE
 */
qson_result qson_get_array_entry_value_null(qson_deserialize_ctx_t *ctx, bool *has_next);

/*
 * Read value of entry as double
 * set context state to ARRAY if has next entry and set to NONE if not
 * Requires state ARRAY_VALUE
 */
qson_result qson_get_array_entry_value_number(qson_deserialize_ctx_t *ctx, double *value, bool *has_next);

#ifdef __cplusplus
}
#endif
#endif
