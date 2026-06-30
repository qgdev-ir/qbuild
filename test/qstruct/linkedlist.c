#include <test/test.h>
#include <qstruct/qstruct.h>

bool test_qstruct_linkedlist_add_get() {
	test_run_log("qstruct_linkedlist_add_get");

	qstruct_linkedlist_t list;
	int value = 858585;
	int value2 = 696969;
	int res_value;

	bool success = 1;
	success &= qstruct_linkedlist_create(&list, sizeof(int)) == QSTRUCT_RESULT_OK;
	success &= qstruct_linkedlist_add(list, &value) == QSTRUCT_RESULT_OK;
	success &= qstruct_linkedlist_add(list, &value2) == QSTRUCT_RESULT_OK;
	success &= qstruct_linkedlist_get(list, 0, &res_value) == QSTRUCT_RESULT_OK;
	success &= res_value == value;
	success &= qstruct_linkedlist_get(list, 1, &res_value) == QSTRUCT_RESULT_OK;
	success &= res_value == value2;
	success &= qstruct_linkedlist_get(list, 2, &res_value) == QSTRUCT_RESULT_INDEX_OUTOF_BOUND;
	success &= qstruct_linkedlist_destroy(list) == QSTRUCT_RESULT_OK;
	test_result_log(success);
	return success;
}

bool test_qstruct_linkedlist() {
	bool success = 1;
	success &= test_qstruct_linkedlist_add_get();
	return success;
}

