#include <test/test.h>

bool test_qson_skip_white_spaces() {
	test_run_log("qson_skip_white_spaces");
	char buffer[] = "\t\n\r test";
	qson_deserialize_ctx_t ctx;

	bool success = 1;
	success &= qson_create_deserialize_ctx(&ctx, buffer, array_len(buffer)) == QSON_RESULT_OK;
	success &= qson_skip_white_spaces(&ctx) == QSON_RESULT_OK;
	success &= ctx.index == 4;
	test_result_log(success);
	return success;
}

bool test_qson_skip_white_spacesـunexpected_eof() {
	test_run_log("qson_skip_white_spaces_unexpected_eof");
	char buffer[] = "\t\n\r ";
	qson_deserialize_ctx_t ctx;

	bool success = 1;
	success &= qson_create_deserialize_ctx(&ctx, buffer, array_len(buffer)) == QSON_RESULT_OK;
	success &= qson_skip_white_spaces(&ctx) == QSON_RESULT_UNEXPECTED_EOF;
	test_result_log(success);
	return success;
}

extern bool test_qson_deserialize_array();
extern bool test_qson_deserialize_object();

bool test_qson_deserialize() {
	bool success = 1;
	success &= test_qson_skip_white_spaces();
	success &= test_qson_skip_white_spacesـunexpected_eof();
	success &= test_qson_deserialize_array();
	success &= test_qson_deserialize_object();
	return success;
}

