#include <test/test.h>
#include <qstruct/qstruct.h>

static int8_t _int32_comparator(char *xp, char *yp) {
	int x = *(int *) xp;
	int y = *(int *) yp;
	return x - y;
}

bool test_qstruct_rbtree_add_get() {
	test_run_log("qstruct_rbtree_add_get");
	qstruct_rbtree_t tree;
	int values[] = { 41, 38, 31, 12, 19, 8, 9, 24, 25, 45 };
	size_t value_size = sizeof(int);
	int res_value;

	bool success = 1;
	success &= qstruct_rbtree_create(&tree, &_int32_comparator) == QSTRUCT_RESULT_OK;
	for (int i = 0; i < array_len(values); i++) {
		success &= qstruct_rbtree_add(tree, values + i, value_size) == QSTRUCT_RESULT_OK;
	}
	for (int i = 0; i < array_len(values); i++) {
		res_value = values[i];
		success &= qstruct_rbtree_get(tree, &res_value, &value_size) == QSTRUCT_RESULT_OK;
		success &= res_value == values[i];
	}
	res_value = 0; // A value that dosent exists
	success &= qstruct_rbtree_get(tree, &res_value, &value_size) == QSTRUCT_RESULT_VALUE_NOT_FOUND;
	test_result_log(success);
	return success;
}

bool test_qstruct_rbtree_has() {
	test_run_log("qstruct_rbtree_has");
	qstruct_rbtree_t tree;
	int value = 1;
	size_t value_size = sizeof(int);

	bool success = 1;
	success &= qstruct_rbtree_create(&tree, &_int32_comparator) == QSTRUCT_RESULT_OK;
	success &= !qstruct_rbtree_has(tree, &value);
	success &= qstruct_rbtree_add(tree, &value, value_size) == QSTRUCT_RESULT_OK;
	success &= qstruct_rbtree_has(tree, &value);
	test_result_log(success);
	return success;
}

bool test_qstruct_rbtree() {
	bool success = 1;
	success &= test_qstruct_rbtree_add_get();
	success &= test_qstruct_rbtree_has();
	return success;
}

