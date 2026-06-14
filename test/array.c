#include <string.h>
#include "test.h"

bool test_qson_start_array() {
	test_run_log("qson_start_array");
	char buffer[] = "[";
	qson_deserialize_ctx_t ctx;

	bool success = 1;
	success &= qson_create_deserialize_ctx(&ctx, buffer, array_len(buffer)) == QSON_RESULT_OK;
	success &= qson_start_array(&ctx) == QSON_RESULT_OK;
	success &= ctx.state == QSON_DESERIALIZING_STATE_ARRAY;
	test_result_log(success);
	return success;
}

bool test_qson_get_array_entry() {
	test_run_log("qson_get_array_entry");
	char buffer[] = "[ \"value\" ]";
	qson_deserialize_ctx_t ctx;
	char key[6];
	int key_size = 6;
	qson_type value_type = QSON_TYPE_STRING;

	bool success = 1;
	success &= qson_create_deserialize_ctx(&ctx, buffer, array_len(buffer)) == QSON_RESULT_OK;
	success &= qson_start_array(&ctx) == QSON_RESULT_OK;
	success &= qson_get_array_entry(&ctx, &value_type) == QSON_RESULT_OK;
	test_result_log(success);
	return success;
}

bool test_qson_get_array_entry_value_string() {
	test_run_log("qson_get_array_entry_value_string");
	char buffer[] = "[ \"string value\"  ]";
	qson_deserialize_ctx_t ctx;
	qson_type value_type = QSON_TYPE_STRING;
	char value[13];
	int value_size = 13;
	bool has_next;

	bool success = 1;
	success &= qson_create_deserialize_ctx(&ctx, buffer, array_len(buffer)) == QSON_RESULT_OK;
	success &= qson_start_array(&ctx) == QSON_RESULT_OK;
	success &= qson_get_array_entry(&ctx, &value_type) == QSON_RESULT_OK;
	success &= qson_get_array_entry_value_string(&ctx, value, &value_size, &has_next) == QSON_RESULT_OK;
	success &= value_size == 13;
	success &= strcmp(value, "string value") == 0;
	success &= !has_next;
	test_result_log(success);
	return success;
}

bool test_qson_get_array_entry_value_bool() {
	test_run_log("qson_get_array_entry_value_bool");
	char buffer[] = "[ true , false ]";
	qson_deserialize_ctx_t ctx;
	qson_type value_type = QSON_TYPE_BOOL;
	bool value;
	bool has_next;

	bool success = 1;
	success &= qson_create_deserialize_ctx(&ctx, buffer, array_len(buffer)) == QSON_RESULT_OK;
	success &= qson_start_array(&ctx) == QSON_RESULT_OK;

	// First entry
	success &= qson_get_array_entry(&ctx, &value_type) == QSON_RESULT_OK;
	success &= qson_get_array_entry_value_bool(&ctx, &value, &has_next) == QSON_RESULT_OK;
	success &= value;
	success &= has_next;

	// Second entry
	success &= qson_get_array_entry(&ctx, &value_type) == QSON_RESULT_OK;
	success &= qson_get_array_entry_value_bool(&ctx, &value, &has_next) == QSON_RESULT_OK;
	success &= !value;
	success &= !has_next;

	test_result_log(success);
	return success;
}

bool test_qson_get_array_entry_value_null() {
	test_run_log("qson_get_array_entry_value_null");
	char buffer[] = "[ null ]";
	qson_deserialize_ctx_t ctx;
	qson_type value_type = QSON_TYPE_NULL;
	bool has_next;

	bool success = 1;
	success &= qson_create_deserialize_ctx(&ctx, buffer, array_len(buffer)) == QSON_RESULT_OK;
	success &= qson_start_array(&ctx) == QSON_RESULT_OK;
	success &= qson_get_array_entry(&ctx, &value_type) == QSON_RESULT_OK;
	success &= qson_get_array_entry_value_null(&ctx, &has_next) == QSON_RESULT_OK;
	success &= !has_next;
	test_result_log(success);
	return success;
}

bool test_array() {
	bool success = 1;
	success &= test_qson_start_array();
	success &= test_qson_get_array_entry();
	success &= test_qson_get_array_entry_value_string();
	success &= test_qson_get_array_entry_value_bool();
	success &= test_qson_get_array_entry_value_null();
	return success;	
}
