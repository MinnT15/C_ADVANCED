/**
 * @file    test_iteration2.c
 * @brief   Test Iteration 2 — Bit Packing + led_set_pixel_color()
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

static void check_hex(const char *name, uint32_t actual, uint32_t expected) {
    if (actual == expected) {
        printf("  ✅ PASS: %s = 0x%08X\n", name, actual);
        test_pass++;
    } else {
        printf("  ❌ FAIL: %s — got 0x%08X, expected 0x%08X\n",
               name, actual, expected);
        test_fail++;
    }
}

/* --- Test Cases --- */

void test_pixel_red(void) {
    printf("\n[Test] Red (255, 0, 0) → 0x0000FF00\n");
    led_init(10);
    led_set_pixel_color(0, 255, 0, 0);
    check_hex("pixel[0]", led_get_buffer()[0], 0x0000FF00);
    led_shutdown();
}

void test_pixel_green(void) {
    printf("\n[Test] Green (0, 255, 0) → 0x00FF0000\n");
    led_init(10);
    led_set_pixel_color(0, 0, 255, 0);
    check_hex("pixel[0]", led_get_buffer()[0], 0x00FF0000);
    led_shutdown();
}

void test_pixel_blue(void) {
    printf("\n[Test] Blue (0, 0, 255) → 0x000000FF\n");
    led_init(10);
    led_set_pixel_color(9, 0, 0, 255);
    check_hex("pixel[9]", led_get_buffer()[9], 0x000000FF);
    led_shutdown();
}

void test_pixel_white(void) {
    printf("\n[Test] White (255, 255, 255) → 0x00FFFFFF\n");
    led_init(10);
    led_set_pixel_color(4, 255, 255, 255);
    check_hex("pixel[4]", led_get_buffer()[4], 0x00FFFFFF);
    led_shutdown();
}

void test_pixel_black(void) {
    printf("\n[Test] Black (0, 0, 0) → 0x00000000\n");
    led_init(10);
    led_set_pixel_color(0, 255, 0, 0);      /* Tô đỏ trước */
    led_set_pixel_color(0, 0, 0, 0);        /* Tắt */
    check_hex("pixel[0]", led_get_buffer()[0], 0x00000000);
    led_shutdown();
}

void test_other_pixels_unchanged(void) {
    printf("\n[Test] Pixel khác không bị ảnh hưởng khi set một pixel\n");
    led_init(10);
    led_set_pixel_color(0, 255, 0, 0);
    const uint32_t *buf = led_get_buffer();
    check("pixel[1] still 0", buf[1] == 0);
    check("pixel[5] still 0", buf[5] == 0);
    check("pixel[9] still 0", buf[9] == 0);
    led_shutdown();
}

void test_out_of_bounds(void) {
    printf("\n[Test] Out-of-bounds index — must not crash, must not write\n");
    led_init(10);
    led_set_pixel_color(10,  255, 0, 0);
    led_set_pixel_color(99,  255, 0, 0);
    led_set_pixel_color(255, 255, 0, 0);
    check("out-of-bounds does not crash", 1);
    check("buffer[9] untouched", led_get_buffer()[9] == 0);
    led_shutdown();
}

void test_multiple_pixels(void) {
    printf("\n[Test] Multiple set_pixel — kịch bản đề bài\n");
    led_init(10);
    led_set_pixel_color(0, 255, 0, 0);
    led_set_pixel_color(9, 0, 0, 255);
    led_set_pixel_color(4, 255, 255, 255);
    const uint32_t *buf = led_get_buffer();
    check_hex("pixel[0] Red",   buf[0], 0x0000FF00);
    check_hex("pixel[9] Blue",  buf[9], 0x000000FF);
    check_hex("pixel[4] White", buf[4], 0x00FFFFFF);
    led_shutdown();
}

int main(void) {
    printf("╔═══════════════════════════════════════════════╗\n");
    printf("║   ITERATION 2 — Bit Packing / Set Pixel       ║\n");
    printf("╚═══════════════════════════════════════════════╝\n");

    test_pixel_red();
    test_pixel_green();
    test_pixel_blue();
    test_pixel_white();
    test_pixel_black();
    test_other_pixels_unchanged();
    test_out_of_bounds();
    test_multiple_pixels();

    printf("\n══════════════════════════════════════════\n");
    printf("  RESULT: %d passed, %d failed\n", test_pass, test_fail);
    printf("══════════════════════════════════════════\n");
    return (test_fail == 0) ? 0 : 1;
}
