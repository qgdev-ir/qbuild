#include <qbuild/qbuild.internal.h>
#include <xxhash.h>

int8_t _qstruct_comparator_string(char *x, char *y) {
	return strcmp(x, y);
}

long _qstruct_hasher(char *x, size_t size, long seed) {
	return XXH64(x, size, seed);
}

