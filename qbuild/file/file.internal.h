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

/*
 * Reads file
 * Creates buffer and writes file content to it
 * Sets size to buffer size
 * NOTE: caller should free buffer after use
 */
qbuild_result_t qbuild_file_read_all(char *file, char **buffer, size_t *size);

#ifdef __cplusplus
}
#endif

#endif

