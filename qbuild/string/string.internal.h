/*
 * QBuild string helper
 * Built to help operations on strings
 */

#ifndef _qbuild_string_string_internal_h_
#define _qbuild_string_string_internal_h_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Converts all upper-cased chars to lower-case
 */
void qbuild_string_lower(char *buf);

/*
 * Format given format string with given paramether and returns a buffer
 * WARGNING: buffer should be freed by caller!
 */
char *qbuild_string_format(const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif

