#include <string.h>
#include "test.h"

bool test_qson_start_object() {
	test_run_log("qson_start_object");
	char buffer[] = "{";
	qson_deserialize_ctx_t ctx;

	bool success = 1;
	success &= qson_create_deserialize_ctx(&ctx, buffer, array_len(buffer)) == QSON_RESULT_OK;
	success &= qson_start_object(&ctx) == QSON_RESULT_OK;
	success &= ctx.state == QSON_DESERIALIZING_STATE_OBJECT;
	test_result_log(success);
	return success;
}

bool test_qson_get_object_entry() {
	test_run_log("qson_get_object_entry");
	char buffer[] = "{ \"key\\u2764\" : \"string value\"  }";
	qson_deserialize_ctx_t ctx;
	char key[10];
	int key_size = 10;
	qson_type value_type = QSON_TYPE_AUTO;

	bool success = 1;
	success &= qson_create_deserialize_ctx(&ctx, buffer, array_len(buffer)) == QSON_RESULT_OK;
	success &= qson_start_object(&ctx) == QSON_RESULT_OK;
	success &= qson_get_object_entry(&ctx, key, &key_size, &value_type) == QSON_RESULT_OK;
	success &= key_size == 7;
	success &= strcmp(key, "key\u2764") == 0;
	success &= value_type == QSON_TYPE_STRING;
	test_result_log(success);
	return success;
}

bool test_object() {
	bool success = 1;
	success &= test_qson_start_object();
	success &= test_qson_get_object_entry();
	return success;
}

