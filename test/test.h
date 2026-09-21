#ifndef _test_test_h_
#define _test_test_h_

#include <stdbool.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define array_len(a) (sizeof(a) / sizeof(a[0]))
#define test_run_log() printf("[*] Running %s\n", __func__)
#define test_result_log(s) printf("[%c] %s\n",  s ? '+' : '-', s ? "passed" : "failed")

#ifdef __cplusplus
}
#endif
#endif
