#include <string.h>
#include <test/test.h>

bool test_qson_write_object() {
	test_run_log("qson_write_object");
	char buffer[2];
	qson_serialize_ctx_t ctx;

	bool success = 1;
	success &= qson_create_serialize_ctx(&ctx, buffer, array_len(buffer)) == QSON_RESULT_OK;
	success &= qson_write_object(&ctx) == QSON_RESULT_OK;
	ctx.state = QSON_SERIALIZE_STATE_NONE; // Faking none state
	success &= qson_end_serialize_ctx(&ctx) == QSON_RESULT_OK;
	success &= strcmp(buffer, "{\0") == 0;
	test_result_log(success);
	return success;
}

bool test_qson_serialize_object() {
	bool success = 1;
	success &= test_qson_write_object();
	return success;
}

