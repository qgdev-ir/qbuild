/*
 * QBuild file helper
 * Built to help reading and writing to files
 */

#ifndef _qbuild_file_file_internal_h_
#define _qbuild_file_file_internal_h_

#include <qbuild/qbuild.internal.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Concatenate given paths
 * For example input is (2, "test", "file.txt") output will be "test/file.txt"
 * NOTE: Caller should free the returned buffer
 */
char *qbuild_file_pathcat(int count, ...);

#ifdef __cplusplus
}
#endif

#endif

