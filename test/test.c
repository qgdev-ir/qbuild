#include "test.h"

extern bool test_qstruct();

int main() {
	bool success = 1;
  success &= test_qstruct();
	return !success;
}

