#include <test/test.h>

extern bool test_qson_deserialize();

bool test_qson() {
	bool success = 1;
	success &= test_qson_deserialize();
	return success;
}
