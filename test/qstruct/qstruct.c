#include <test/test.h>

extern bool test_qstruct_arraylist();
extern bool test_qstruct_linkedlist();
extern bool test_qstruct_rbtree();
extern bool test_qstruct_hashmap();

bool test_qstruct() {
	bool success = 1;
	success &= test_qstruct_arraylist();
	success &= test_qstruct_linkedlist();
	success &= test_qstruct_rbtree();
	success &= test_qstruct_hashmap();
	return success;
}
