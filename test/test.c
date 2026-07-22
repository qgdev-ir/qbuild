#include "test.h"

extern bool test_qbuild();

int main() {
	bool success = 1;
	success &= test_qbuild();
	return !success;
}

