#include <test/test.h>

extern bool test_qstruct_arraylist();
extern bool test_qstruct_linkedlist();

bool test_qstruct() {
	bool success = 1;
	success &= test_qstruct_arraylist();
	success &= test_qstruct_linkedlist();
	return success;
}
