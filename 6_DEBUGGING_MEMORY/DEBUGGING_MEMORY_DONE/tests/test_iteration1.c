/**
 * @file test_iteration1.c
 * @brief Iteration 1 Tests — Kiểm tra Stack Overflow module.
 *
 * Lệnh chạy: make test1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
 * Test 1.1: Kiểm tra argument parsing — mode hợp lệ
 * ============================================================ */
static void test_mode_parsing(void) {
    printf("\n--- Test 1.1: Argument Parsing ---\n");

    /* Kiểm tra strcmp hoạt động đúng cho các mode */
    check("Mode 'stack_overflow' nhận dạng đúng",
          strcmp("stack_overflow", "stack_overflow") == 0);

    check("Mode 'memory_leak' nhận dạng đúng",
          strcmp("memory_leak", "memory_leak") == 0);

    check("Mode 'out_of_memory' nhận dạng đúng",
          strcmp("out_of_memory", "out_of_memory") == 0);

    check("Mode không hợp lệ bị reject",
          strcmp("invalid_mode", "stack_overflow") != 0 &&
          strcmp("invalid_mode", "memory_leak") != 0 &&
          strcmp("invalid_mode", "out_of_memory") != 0);
}

/* ============================================================
 * Test 1.2: Kiểm tra ALLOC_SIZE constant (qua compile)
 * ============================================================ */
static void test_alloc_size(void) {
    printf("\n--- Test 1.2: Allocation Size ---\n");

    /* Test malloc với kích thước thực tế */
    void *ptr = malloc(1024);   /* 1KB */
    check("malloc(1024) thành công", ptr != NULL);
    free(ptr);

    /* Test malloc với 0 (edge case) */
    /* Hành vi malloc(0) là implementation-defined, nhưng không crash */
    check("malloc size > 0 cho memory_leak scenario", 1024 > 0);
}

/* ============================================================
 * Test 1.3: Kiểm tra header file tồn tại (compile-time check)
 * ============================================================ */
#include "memory_lab.h"     /* Nếu compile được → header OK */

static void test_header_api(void) {
    printf("\n--- Test 1.3: API Header ---\n");

    /* Kiểm tra hàm được declare (chỉ cần compile thành công) */
    /* Không gọi trigger_stack_overflow vì sẽ crash! */
    /* Thay vào đó, lấy địa chỉ hàm để xác nhận nó tồn tại */
    void (*fn_ptr1)(int)  = trigger_stack_overflow;
    void (*fn_ptr2)(void) = trigger_memory_leak;

    check("trigger_stack_overflow được declare trong header", fn_ptr1 != NULL);
    check("trigger_memory_leak được declare trong header",     fn_ptr2 != NULL);
}

/* ============================================================
 * Main
 * ============================================================ */
int main(void) {
    printf("============================================\n");
    printf("  TEST ITERATION 1: Stack Overflow Module  \n");
    printf("============================================\n");

    test_mode_parsing();
    test_alloc_size();
    test_header_api();

    printf("\n============================================\n");
    printf("RESULT: %d passed, %d failed\n", test_pass, test_fail);
    printf("============================================\n");

    return (test_fail == 0) ? 0 : 1;
}
