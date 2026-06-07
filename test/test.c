#include <stdio.h>
#include <qson/qson.h>

#define test_run_log(m) printf("[*] Running test %s: ", m)
#define test_result_log(s) printf("%s\n", s ? "passed" : "failed")

int test_qson_skip_white_spaces() {
	test_run_log("qson_skip_white_spaces");
	char *buffer = "\t\n\r test";
	qson_deserialize_ctx_t ctx;

	qson_create_deserialize_ctx(&ctx, buffer, sizeof(buffer));
	qson_skip_white_spaces(&ctx);

	bool success = ctx.index == 4;
	test_result_log(success);
	return success;
}

int main() {
	bool success = 1;
	success &= test_qson_skip_white_spaces();
	return !success;
}

