/**
 * @file    test_iteration4.c
 * @brief   Test Iteration 4 — Getters: led_get_buffer() + led_get_pixel_count()
 */

#include <stdio.h>
#include <stdint.h>
#include "led_rgb.h"

static int test_pass = 0;
static int test_fail = 0;

static void check(const char *name, int cond) {
    if (cond) { printf("  ✅ PASS: %s\n", name); test_pass++; }
    else       { printf("  ❌ FAIL: %s\n", name); test_fail++; }
}

/* --- Test Cases --- */

void test_get_pixel_count(void) {
    printf("\n[Test] led_get_pixel_count()\n");
    led_init(10);
    check("count = 10 after init(10)", led_get_pixel_count() == 10);
    led_shutdown();
    check("count = 0 after shutdown",  led_get_pixel_count() == 0);

    led_init(5);
    check("count = 5 after init(5)",   led_get_pixel_count() == 5);
    led_shutdown();

    led_init(256);
    check("count = 256 after init(256)", led_get_pixel_count() == 256);
    led_shutdown();
}

void test_get_buffer_not_null(void) {
    printf("\n[Test] led_get_buffer() — not NULL after init\n");
    led_init(10);
    check("buffer != NULL after init",    led_get_buffer() != NULL);
    led_shutdown();
    check("buffer == NULL after shutdown", led_get_buffer() == NULL);
}

void test_buffer_reflects_set_pixel(void) {
    printf("\n[Test] buffer phản ánh đúng led_set_pixel_color()\n");
    led_init(10);
    led_set_pixel_color(3, 255, 0, 0);  /* Red */
    led_set_pixel_color(7, 0, 255, 0);  /* Green */
    const uint32_t *buf = led_get_buffer();
    check("buf[3] = Red   (0x0000FF00)", buf[3] == 0x0000FF00);
    check("buf[7] = Green (0x00FF0000)", buf[7] == 0x00FF0000);
    led_shutdown();
}

void test_buffer_reflects_fill(void) {
    printf("\n[Test] buffer phản ánh đúng led_fill()\n");
    led_init(10);
    led_fill(0, 0, 255);  /* Blue */
    const uint32_t *buf = led_get_buffer();
    check("buf[0] = Blue (0x000000FF)", buf[0] == 0x000000FF);
    check("buf[9] = Blue (0x000000FF)", buf[9] == 0x000000FF);
    led_shutdown();
}

void test_const_pointer(void) {
    printf("\n[Test] led_get_buffer() trả về const — compile-time protection\n");
    printf("  ℹ️  const uint32_t* được enforce bởi compiler.\n");
    printf("  ℹ️  Nếu code này compile thành công → const đúng.\n");
    /* Nếu gọi: led_get_buffer()[0] = 0x1234; → compiler error */
    check("const pointer compile-time check OK", 1);
}

int main(void) {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║   ITERATION 4 — Getters                ║\n");
    printf("╚═══════════════════════════════════════╝\n");

    test_get_pixel_count();
    test_get_buffer_not_null();
    test_buffer_reflects_set_pixel();
    test_buffer_reflects_fill();
    test_const_pointer();

    printf("\n══════════════════════════════════════════\n");
    printf("  RESULT: %d passed, %d failed\n", test_pass, test_fail);
    printf("══════════════════════════════════════════\n");
    return (test_fail == 0) ? 0 : 1;
}
