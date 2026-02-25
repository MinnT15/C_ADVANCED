/**
 * @file test_iteration1.c
 * @brief TODO: Viết tests cho Iteration 1 (Stack Overflow module)
 * Tham khảo STEP_BY_STEP_GUIDE.md để biết cần test gì.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory_lab.h"

static int test_pass = 0;
static int test_fail = 0;

static void check(const char *name, int condition) {
    if (condition) { printf("[PASS] %s\n", name); test_pass++; }
    else           { printf("[FAIL] %s\n", name); test_fail++; }
}

int main(void) {
    printf("=== TEST ITERATION 1 ===\n\n");

    /* TODO: Thêm tests tại đây */
    /* Gợi ý: test argument parsing, alloc size, API availability */
    check("Placeholder test (xóa dòng này khi thêm tests thật)", 1);

    printf("\nRESULT: %d passed, %d failed\n", test_pass, test_fail);
    return (test_fail == 0) ? 0 : 1;
}
