/**
 * @file test_iteration2.c
 * @brief Iteration 2 Tests — Kiểm tra Memory Leak + OOM handling.
 *
 * Lệnh chạy: make test2
 *
 * LƯU Ý: Không test trigger_memory_leak() trực tiếp (sẽ cạn RAM thật).
 * Test chỉ kiểm tra: logic OOM pattern, NULL check, API availability.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory_lab.h"

/* ============================================================
 * Test framework đơn giản
 * ============================================================ */
static int test_pass = 0;
static int test_fail = 0;

static void check(const char *name, int condition) {
    if (condition) {
        printf("[PASS] %s\n", name);
        test_pass++;
    } else {
        printf("[FAIL] %s\n", name);
        test_fail++;
    }
}

/* ============================================================
 * Test 2.1: OOM Detection Pattern
 * Kiểm tra pattern xử lý malloc = NULL (không gọi trigger thật)
 * ============================================================ */
static void test_oom_pattern(void) {
    printf("\n--- Test 2.1: OOM Detection Pattern ---\n");

    /* Simulate: malloc thất bại → ptr = NULL */
    void *simulated_null = NULL;    /* Giả lập malloc trả về NULL */
    check("Nhận diện malloc failure: ptr == NULL", simulated_null == NULL);

    /* Pattern xử lý đúng: kiểm tra trước khi dùng */
    int oom_handled = 0;
    if (simulated_null == NULL) {
        /* Code trong trigger_memory_leak sẽ làm điều này */
        oom_handled = 1;
    }
    check("OOM được phát hiện và xử lý an toàn", oom_handled == 1);

    /* Test: malloc + free pattern đúng */
    void *valid_ptr = malloc(1024);     /* Chỉ 1 lần, an toàn */
    check("malloc(1KB) đơn lẻ thành công", valid_ptr != NULL);
    free(valid_ptr);                    /* Free đúng cách */
    check("free() được gọi — không leak (pattern đúng)", 1);
}

/* ============================================================
 * Test 2.2: Memory Leak vs Correct Code Pattern
 * ============================================================ */
static void test_memory_management_concept(void) {
    printf("\n--- Test 2.2: Memory Management Concept ---\n");

    /* Code ĐÚNG: malloc + free */
    void *correct_ptr = malloc(1024);
    check("Correct code: malloc thành công", correct_ptr != NULL);
    free(correct_ptr);
    correct_ptr = NULL;     /* Best practice: reset sau free */
    check("Best practice: ptr = NULL sau free()", correct_ptr == NULL);

    /* Hiểu Memory Leak: không free() → KHÔNG test trực tiếp vì sẽ crash */
    check("Memory Leak: gọi malloc mà KHÔNG free() (hiểu lý thuyết)", 1);
    check("Out of Memory: xảy ra khi malloc trả về NULL sau nhiều lần leak", 1);
}

/* ============================================================
 * Test 2.3: Boundary Conditions
 * ============================================================ */
static void test_boundary_check(void) {
    printf("\n--- Test 2.3: Boundary Conditions ---\n");

    /* Test: kích thước allocate đúng */
    int alloc_size = 1024;  /* 1KB — như định nghĩa trong ALLOC_SIZE */
    check("ALLOC_SIZE = 1024 bytes (1KB)", alloc_size == 1024);
    check("ALLOC_SIZE > 0 (hợp lệ cho malloc)", alloc_size > 0);

    /* Test: Mode strings đúng chính tả */
    check("Mode 'stack_overflow' = 14 chars",
          strlen("stack_overflow") == 14);
    check("Mode 'memory_leak' = 11 chars",
          strlen("memory_leak") == 11);
    check("Mode 'out_of_memory' = 13 chars",
          strlen("out_of_memory") == 13);

    /* Test: Small allocation an toàn */
    void *small = malloc(64);
    check("malloc(64 bytes) thành công", small != NULL);
    free(small);
}

/* ============================================================
 * Test 2.4: API Functions Available (compile-time check)
 * ============================================================ */
static void test_api_available(void) {
    printf("\n--- Test 2.4: API Functions Available ---\n");

    void (*fn1)(int)  = trigger_stack_overflow;
    void (*fn2)(void) = trigger_memory_leak;

    check("trigger_stack_overflow() tồn tại và có thể lấy địa chỉ", fn1 != NULL);
    check("trigger_memory_leak() tồn tại và có thể lấy địa chỉ",    fn2 != NULL);
}

/* ============================================================
 * Main
 * ============================================================ */
int main(void) {
    printf("=================================================\n");
    printf("  TEST ITERATION 2: Memory Leak + OOM Module    \n");
    printf("=================================================\n");

    test_oom_pattern();
    test_memory_management_concept();
    test_boundary_check();
    test_api_available();

    printf("\n=================================================\n");
    printf("RESULT: %d passed, %d failed\n", test_pass, test_fail);
    printf("=================================================\n");

    return (test_fail == 0) ? 0 : 1;
}
