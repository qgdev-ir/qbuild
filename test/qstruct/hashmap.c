#include <test/test.h>
#include <qstruct/qstruct.h>
#include <xxhash.h>
#include <string.h>

static int8_t _comparator(char *x, char *y) {
	return strcmp(x, y);
}

static long _hasher(char *x, size_t size, long seed) {
	return XXH64(x, size, seed);
}


bool test_qstruct_hashmap_add_get() {
	test_run_log("qstruct_hashmap_add_get");
	qstruct_hashmap_t map;
	char res[2];
	size_t res_size = array_len(res);

	bool success = 1;
	success &= qstruct_hashmap_create(&map, &_comparator, 0, 0, &_hasher, 0) == QSTRUCT_RESULT_OK;
	success &= qstruct_hashmap_add(map, "sik", 4, "k", 2) == QSTRUCT_RESULT_OK;
	success &= qstruct_hashmap_add(map, "kir", 4, "s", 2) == QSTRUCT_RESULT_OK;
	success &= qstruct_hashmap_get(map, "sik", 4, res, &res_size) == QSTRUCT_RESULT_OK;
	success &= strcmp(res, "k") == 0;
	success &= qstruct_hashmap_get(map, "kir", 4, res, &res_size) == QSTRUCT_RESULT_OK;
	success &= strcmp(res, "s") == 0;
	success &= qstruct_hashmap_destroy(map) == QSTRUCT_RESULT_OK;
	test_result_log(success);
	return success;
}

bool test_qstruct_hashmap_has() {
	test_run_log("qstruct_hashmap_has");
	qstruct_hashmap_t map;

	bool success = 1;
	success &= qstruct_hashmap_create(&map, &_comparator, 0, 0, &_hasher, 0) == QSTRUCT_RESULT_OK;
	success &= qstruct_hashmap_add(map, "sik", 4, "k", 2) == QSTRUCT_RESULT_OK;
	success &= qstruct_hashmap_has(map, "sik", 4);
	success &= !qstruct_hashmap_has(map, "kir", 4);
	success &= qstruct_hashmap_destroy(map) == QSTRUCT_RESULT_OK;
	test_result_log(success);
	return success;
}

bool test_qstruct_hashmap() {
	bool success = 1;
	success &= test_qstruct_hashmap_add_get();
	success &= test_qstruct_hashmap_has();
	return success;
}
