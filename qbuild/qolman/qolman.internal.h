/*
 * QBuild internal helper for qolman
 */

#ifndef _qbuild_qolman_internal_h_
#define _qbuild_qolman_internal_h_

#include <qolman/qolman.h>

#ifdef __cplusplus
extern "C" {
#endif

#define qolman_run(call) if (call != QOLMAN_RESULT_OK) return QBUILD_RESULT_LOGGING_FAILED;

/*
 * Use qolman manager as qbuild log manager
 */
typedef qolman_manager_t qbuild_logman_t;

/*
 * Creates a log manager
 */
qbuild_result_t qbuild_logman_create(qbuild_logman_t *m);

/*
 * Destroys the given log manager
 */
qbuild_result_t qbuild_logman_destroy(qbuild_logman_t m);

#ifdef __cplusplus
}
#endif

#endif

