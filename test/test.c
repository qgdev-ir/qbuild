#include <stdio.h>
#include <qson/qson.h>

#define test_run_log(m) printf("[*] Running test %s: ", m)
#define test_result_log(s) printf("%s\n", s ? "passed" : "failed")

bool test_qson_skip_white_spaces() {
	test_run_log("qson_skip_white_spaces");
	char *buffer = "\t\n\r test";
	qson_deserialize_ctx_t ctx;

	bool success = 1;
	success &= qson_create_deserialize_ctx(&ctx, buffer, sizeof(buffer)) == OK;
	success &= qson_skip_white_spaces(&ctx) == OK;
	success &= ctx.index == 4;
	test_result_log(success);
	return success;
}

bool test_qson_skip_white_spacesـunexpected_eof() {
	test_run_log("qson_skip_white_spaces");
	char *buffer = "\t\n\r ";
	qson_deserialize_ctx_t ctx;

	bool success = 1;
	success &= qson_create_deserialize_ctx(&ctx, buffer, sizeof(buffer)) == OK;
	success &= qson_skip_white_spaces(&ctx) == UNEXPECTED_EOF;
	test_result_log(success);
	return success;
}

int main() {
	bool success = 1;
	success &= test_qson_skip_white_spaces();
	success &= test_qson_skip_white_spacesـunexpected_eof();
	return !success;
}

