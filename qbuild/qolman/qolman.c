#include <qbuild/qbuild.internal.h>

static struct qolman_level level_all = { -2147483648, "ALL" };

qbuild_result_t qbuild_logman_create(qbuild_logman_t *m) {
	qolman_run(qolman_manager_create(m, &qolman_formatter_text));
	qolman_run(qolman_manager_level_set(*m, qbuild_debug() ? &level_all : qolman_level_get(0)));

	qolman_handler_t handlers[1];
	qolman_run(qolman_handler_stdout(&handlers[0]));
	qolman_run(qolman_manager_handlers_set(*m, handlers, 1));

	return QBUILD_RESULT_OK;
}

qbuild_result_t qbuild_logman_destroy(qbuild_logman_t m) {
	size_t handlers_len;
	qolman_handler_t *handlers = qolman_manager_handlers(m, &handlers_len);
	for (int i = 0; i < handlers_len; i++)
		qolman_run(qolman_handler_destroy(handlers[i]));
	qolman_run(qolman_manager_destroy(m));
	return QBUILD_RESULT_OK;
}

