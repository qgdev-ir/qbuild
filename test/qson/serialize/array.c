#include <string.h>
#include <test/test.h>

bool test_qson_write_array() {
	test_run_log("qson_write_array");
	char buffer[2];
	qson_serialize_ctx_t ctx;

	bool success = 1;
	success &= qson_create_serialize_ctx(&ctx, buffer, array_len(buffer)) == QSON_RESULT_OK;
	success &= qson_write_array(&ctx) == QSON_RESULT_OK;
	ctx.state = QSON_SERIALIZE_STATE_NONE; // Faking none state
	success &= qson_end_serialize_ctx(&ctx) == QSON_RESULT_OK;
	success &= strcmp(buffer, "[\0") == 0;
	test_result_log(success);
	return success;
}

bool test_qson_write_array_entry_string() {
	test_run_log("qson_write_array_entry_string");
	qson_serialize_ctx_t ctx;
	char buffer[30];
	char *value = "value";

	bool success = 1;
	success &= qson_create_serialize_ctx(&ctx, buffer, array_len(buffer)) == QSON_RESULT_OK;
	success &= qson_write_array(&ctx) == QSON_RESULT_OK;
	success &= qson_write_array_entry_string(&ctx, value, true) == QSON_RESULT_OK;
	success &= qson_write_array_entry_string(&ctx, value, false) == QSON_RESULT_OK;
	success &= qson_end_serialize_ctx(&ctx) == QSON_RESULT_OK;
	success &= strcmp("[\"value\",\"value\"]", buffer) == 0;
	test_result_log(success);
	return success;
}

bool test_qson_write_array_entry_null() {
	test_run_log("qson_write_array_entry_null");
	qson_serialize_ctx_t ctx;
	char buffer[7];

	bool success = 1;
	success &= qson_create_serialize_ctx(&ctx, buffer, array_len(buffer)) == QSON_RESULT_OK;
	success &= qson_write_array(&ctx) == QSON_RESULT_OK;
	success &= qson_write_array_entry_null(&ctx, false) == QSON_RESULT_OK;
	success &= qson_end_serialize_ctx(&ctx) == QSON_RESULT_OK;
	success &= strcmp("[null]", buffer) == 0;
	test_result_log(success);
	return success;
}

bool test_qson_write_array_entry_bool() {
	test_run_log("qson_write_array_entry_bool");
	qson_serialize_ctx_t ctx;
	char buffer[13];

	bool success = 1;
	success &= qson_create_serialize_ctx(&ctx, buffer, array_len(buffer)) == QSON_RESULT_OK;
	success &= qson_write_array(&ctx) == QSON_RESULT_OK;
	success &= qson_write_array_entry_bool(&ctx, true, true) == QSON_RESULT_OK;
	success &= qson_write_array_entry_bool(&ctx, false, false) == QSON_RESULT_OK;
	success &= qson_end_serialize_ctx(&ctx) == QSON_RESULT_OK;
	success &= strcmp("[true,false]", buffer) == 0;
	test_result_log(success);
	return success;
}

bool test_qson_serialize_array() {
	bool success = 1;
	success &= test_qson_write_array();
	success &= test_qson_write_array_entry_string();
	success &= test_qson_write_array_entry_null();
	success &= test_qson_write_array_entry_bool();
	return success;
}

