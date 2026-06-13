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

bool test_array() {
	bool success = 1;
	success &= test_qson_start_array();
	success &= test_qson_get_array_entry();
	return success;	
}
