/**
 * @file    test_iteration5.c
 * @brief   Test Iteration 5 — Full Integration Test
 *          Kiểm thử toàn bộ driver theo đúng 10 bước đề bài
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

static int all_equal(uint32_t expected) {
    const uint32_t *buf = led_get_buffer();
    for (size_t i = 0; i < led_get_pixel_count(); i++)
        if (buf[i] != expected) return 0;
    return 1;
}

/* --- Main Integration Test --- */

void test_full_10_steps(void) {
    printf("\n[Test] 10 bước kịch bản theo đề bài\n");

    /* Bước 1 */
    check("Step 1: led_init(10) returns 0", led_init(10) == 0);

    /* Bước 2 */
    check("Step 2: buffer initialized to 0 (Black)", all_equal(0x00000000));

    /* Bước 3 */
    led_set_pixel_color(0, 255, 0, 0);
    /* Bước 4 */
    led_set_pixel_color(9, 0, 0, 255);
    /* Bước 5 */
    led_set_pixel_color(4, 255, 255, 255);

    /* Bước 6-7 */
    const uint32_t *buf = led_get_buffer();
    check("Step 7: buffer[0] = 0x0000FF00 (Red)",   buf[0] == 0x0000FF00);
    check("Step 7: buffer[4] = 0x00FFFFFF (White)", buf[4] == 0x00FFFFFF);
    check("Step 7: buffer[9] = 0x000000FF (Blue)",  buf[9] == 0x000000FF);

    /* Bước 8-9 */
    led_fill(0, 255, 0);
    check("Step 9: all pixels = 0x00FF0000 (Green)", all_equal(0x00FF0000));

    /* Bước 10 */
    led_shutdown();
    check("Step 10: buffer = NULL after shutdown", led_get_buffer() == NULL);
    check("Step 10: count  = 0 after shutdown",    led_get_pixel_count() == 0);
}

/* --- Edge Cases --- */

void test_boundary_check(void) {
    printf("\n[Test] Boundary check toàn diện\n");
    led_init(10);
    /* Các index không hợp lệ */
    led_set_pixel_color(10,  255, 0, 0);
    led_set_pixel_color(100, 255, 0, 0);
    check("no crash on out-of-bounds", 1);
    check("buffer[9] untouched", led_get_buffer()[9] == 0);
    led_shutdown();
}

void test_reinit_scenario(void) {
    printf("\n[Test] Reinit scenario — dùng lại driver với size khác\n");
    led_init(5);
    led_fill(255, 0, 0);
    led_init(20);  /* Reinit với size lớn hơn */
    check("new count = 20", led_get_pixel_count() == 20);
    check("buffer zeroed after reinit", led_get_buffer()[0] == 0);
    led_shutdown();
}

void test_clear_is_fill_zero(void) {
    printf("\n[Test] led_clear() = led_fill(0,0,0)\n");
    led_init(10);
    led_fill(255, 128, 64);
    led_clear();
    const uint32_t *buf = led_get_buffer();
    int all_zero = (buf[0] == 0 && buf[5] == 0 && buf[9] == 0);
    check("clear sets all pixels to 0", all_zero);
    led_shutdown();
}

int main(void) {
    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║   ITERATION 5 — Full Integration Test             ║\n");
    printf("╚══════════════════════════════════════════════════╝\n");

    test_full_10_steps();
    test_boundary_check();
    test_reinit_scenario();
    test_clear_is_fill_zero();

    printf("\n══════════════════════════════════════════\n");
    printf("  RESULT: %d passed, %d failed\n", test_pass, test_fail);
    printf("══════════════════════════════════════════\n");
    return (test_fail == 0) ? 0 : 1;
}
