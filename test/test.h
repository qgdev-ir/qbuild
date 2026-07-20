#ifndef _test_test_h_
#define _test_test_h_

#include <stdbool.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define array_len(a) (sizeof(a) / sizeof(a[0]))
#define test_run_log(m) printf("[*] Running test %s: ", m)
#define test_result_log(s) printf("%s\n", s ? "passed" : "failed")

#ifdef __cplusplus
}
#endif
#endif
