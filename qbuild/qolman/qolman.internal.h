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

#ifdef __cplusplus
}
#endif

#endif

