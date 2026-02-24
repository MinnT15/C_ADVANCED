/**
 * @file    test_iteration3.c
 * @brief   Test Iteration 3 — led_fill() + led_clear()
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

static int all_pixels_equal(uint32_t expected) {
    const uint32_t *buf = led_get_buffer();
    size_t count = led_get_pixel_count();
    for (size_t i = 0; i < count; i++) {
        if (buf[i] != expected) return 0;
    }
    return 1;
}

/* --- Test Cases --- */

void test_fill_green(void) {
    printf("\n[Test] led_fill(0,255,0) → tất cả = 0x00FF0000 (Green)\n");
    led_init(10);
    led_fill(0, 255, 0);
    check("all 10 pixels = Green", all_pixels_equal(0x00FF0000));
    led_shutdown();
}

void test_fill_red(void) {
    printf("\n[Test] led_fill(255,0,0) → tất cả = 0x0000FF00 (Red)\n");
    led_init(10);
    led_fill(255, 0, 0);
    check("all 10 pixels = Red", all_pixels_equal(0x0000FF00));
    led_shutdown();
}

void test_fill_white(void) {
    printf("\n[Test] led_fill(255,255,255) → tất cả = 0x00FFFFFF (White)\n");
    led_init(10);
    led_fill(255, 255, 255);
    check("all 10 pixels = White", all_pixels_equal(0x00FFFFFF));
    led_shutdown();
}

void test_clear_after_fill(void) {
    printf("\n[Test] led_clear() sau fill → tất cả về 0\n");
    led_init(10);
    led_fill(255, 0, 0);
    led_clear();
    check("all pixels = 0 after clear", all_pixels_equal(0x00000000));
    led_shutdown();
}

void test_fill_overrides_individual(void) {
    printf("\n[Test] led_fill() ghi đè lên led_set_pixel_color()\n");
    led_init(10);
    led_set_pixel_color(0, 255, 0, 0);
    led_set_pixel_color(5, 0, 0, 255);
    led_fill(0, 255, 0);  /* Fill Green → ghi đè hết */
    check("pixel[0] is Green after fill", led_get_buffer()[0] == 0x00FF0000);
    check("pixel[5] is Green after fill", led_get_buffer()[5] == 0x00FF0000);
    led_shutdown();
}

void test_fill_large_strip(void) {
    printf("\n[Test] led_fill() với dải LED lớn (100 pixel)\n");
    led_init(100);
    led_fill(128, 64, 32);
    uint32_t expected = ((uint32_t)64 << 16) | ((uint32_t)128 << 8) | 32;
    check("all 100 pixels correctly filled", all_pixels_equal(expected));
    led_shutdown();
}

int main(void) {
    printf("╔════════════════════════════════════════╗\n");
    printf("║   ITERATION 3 — Fill & Clear            ║\n");
    printf("╚════════════════════════════════════════╝\n");

    test_fill_green();
    test_fill_red();
    test_fill_white();
    test_clear_after_fill();
    test_fill_overrides_individual();
    test_fill_large_strip();

    printf("\n══════════════════════════════════════════\n");
    printf("  RESULT: %d passed, %d failed\n", test_pass, test_fail);
    printf("══════════════════════════════════════════\n");
    return (test_fail == 0) ? 0 : 1;
}
