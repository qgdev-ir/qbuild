#include <qbuild/qbuild.internal.h>

static struct qolman_level level_all = { -2147483648, "ALL" };

qbuild_result_t _qbuild_logman_create(qbuild_log_manager_t *m) {
	qolman_run(qolman_manager_create(m, &qolman_formatter_text));
	qolman_run(qolman_manager_level_set(*m, qbuild_debug() ? &level_all : qolman_level_get(0)));

	qolman_handler_t handlers[1];
	qolman_run(qolman_handler_stdout(&handlers[0]));
	qolman_run(qolman_manager_handlers_set(*m, handlers, 1));

	return QBUILD_RESULT_OK;
}

