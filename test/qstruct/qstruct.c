#include <test/test.h>

extern bool test_qstruct_arraylist();

bool test_qstruct() {
	bool success = 1;
	success &= test_qstruct_arraylist();
	return success;
}
