/**
 * @file    test_iteration1.c
 * @brief   Test Iteration 1 — Memory Management
 *          led_init() + led_shutdown()
 */

#include <stdio.h>
#include <stdint.h>
#include "led_rgb.h"

static int test_pass = 0;
static int test_fail = 0;

static void check(const char *name, int condition) {
    if (condition) { printf("  ✅ PASS: %s\n", name); test_pass++; }
    else           { printf("  ❌ FAIL: %s\n", name); test_fail++; }
}

/* --- Test Cases --- */

void test_init_normal(void) {
    printf("\n[Test] led_init(10) — normal case\n");
    int ret = led_init(10);
    check("led_init returns 0", ret == 0);
    check("pixel count = 10",   led_get_pixel_count() == 10);
    check("buffer not NULL",    led_get_buffer() != NULL);

    const uint32_t *buf = led_get_buffer();
    int all_zero = 1;
    for (size_t i = 0; i < 10; i++) {
        if (buf[i] != 0) { all_zero = 0; break; }
    }
    check("all pixels initialized to 0", all_zero);
    led_shutdown();
}

void test_init_zero(void) {
    printf("\n[Test] led_init(0) — should fail\n");
    int ret = led_init(0);
    check("led_init(0) returns -1", ret == -1);
    check("buffer is NULL after failed init", led_get_buffer() == NULL);
    check("count = 0 after failed init",      led_get_pixel_count() == 0);
}

void test_shutdown(void) {
    printf("\n[Test] led_shutdown() — memory cleanup\n");
    led_init(5);
    led_shutdown();
    check("buffer = NULL after shutdown", led_get_buffer() == NULL);
    check("count  = 0 after shutdown",    led_get_pixel_count() == 0);
}

void test_double_shutdown(void) {
    printf("\n[Test] led_shutdown() gọi 2 lần — must not crash\n");
    led_init(5);
    led_shutdown();
    led_shutdown();
    check("double shutdown does not crash", 1);
}

void test_reinit(void) {
    printf("\n[Test] led_init() gọi 2 lần — reinit\n");
    led_init(5);
    int ret = led_init(10);
    check("reinit returns 0",              ret == 0);
    check("pixel count updated to 10",    led_get_pixel_count() == 10);
    led_shutdown();
}

int main(void) {
    printf("╔══════════════════════════════════════════╗\n");
    printf("║   ITERATION 1 — Memory Management        ║\n");
    printf("╚══════════════════════════════════════════╝\n");

    test_init_normal();
    test_init_zero();
    test_shutdown();
    test_double_shutdown();
    test_reinit();

    printf("\n══════════════════════════════════════════\n");
    printf("  RESULT: %d passed, %d failed\n", test_pass, test_fail);
    printf("══════════════════════════════════════════\n");
    return (test_fail == 0) ? 0 : 1;
}
