#include "test.h"
#include <stdlib.h>

extern bool test_qbuild();

int main() {
	setenv("QBUILD_DEBUG", "", true); // Set qbuild debug mode
	bool success = 1;
	success &= test_qbuild();
	return !success;
}

