#include <test/test.h>

extern bool test_qson_serialize_object();

bool test_qson_serialize() {
	bool success = 1;
	success &= test_qson_serialize_object();
	return success;
}

