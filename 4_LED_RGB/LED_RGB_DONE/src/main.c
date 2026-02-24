/**
 * @file    main.c
 * @brief   LED RGB Strip Driver — Demo & Integration Test
 *
 * Thực hiện đầy đủ 10 bước kịch bản theo đề bài:
 *   1.  led_init(10)
 *   2.  Kiểm tra buffer = 0
 *   3.  led_set_pixel_color(0, 255, 0, 0)   → Đỏ
 *   4.  led_set_pixel_color(9, 0, 0, 255)   → Xanh dương
 *   5.  led_set_pixel_color(4, 255, 255, 255)→ Trắng
 *   6.  led_get_buffer()
 *   7.  In hex buffer[0]=0x0000FF00, [4]=0x00FFFFFF, [9]=0x000000FF
 *   8.  led_fill(0, 255, 0)
 *   9.  Kiểm tra tất cả pixel = 0x00FF0000
 *   10. led_shutdown()
 */

#include <stdio.h>
#include <stdint.h>
#include "led_rgb.h"

/* ============================================================
 * Helper utilities
 * ============================================================ */
static void print_pixel(size_t index, const uint32_t *buf) {
    printf("  buffer[%zu] = 0x%08X\n", index, buf[index]);
}

static void check_all_equal(const char *label, uint32_t expected) {
    const uint32_t *buf = led_get_buffer();
    size_t count        = led_get_pixel_count();
    int all_ok = 1;
    for (size_t i = 0; i < count; i++) {
        if (buf[i] != expected) { all_ok = 0; break; }
    }
    printf("  %-45s %s (expected 0x%08X)\n",
           label, all_ok ? "✅ OK" : "❌ FAIL", expected);
}

/* ============================================================
 * Main
 * ============================================================ */
int main(void) {
    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║    LED RGB Strip Driver — Integration Demo        ║\n");
    printf("╚══════════════════════════════════════════════════╝\n\n");

    /* --- Bước 1: Khởi tạo 10 pixel --- */
    printf("── Bước 1: led_init(10)\n");
    int ret = led_init(10);
    printf("   return = %d %s\n\n", ret, ret == 0 ? "✅" : "❌");

    /* --- Bước 2: buffer = 0 --- */
    printf("── Bước 2: Kiểm tra buffer khởi tạo = 0\n");
    check_all_equal("all 10 pixels = 0x00000000 (Black)", 0x00000000);
    printf("\n");

    /* --- Bước 3: Pixel 0 = Đỏ --- */
    printf("── Bước 3: led_set_pixel_color(0, 255, 0, 0) → Red\n");
    led_set_pixel_color(0, 255, 0, 0);
    printf("   done\n\n");

    /* --- Bước 4: Pixel 9 = Xanh dương --- */
    printf("── Bước 4: led_set_pixel_color(9, 0, 0, 255) → Blue\n");
    led_set_pixel_color(9, 0, 0, 255);
    printf("   done\n\n");

    /* --- Bước 5: Pixel 4 = Trắng --- */
    printf("── Bước 5: led_set_pixel_color(4, 255, 255, 255) → White\n");
    led_set_pixel_color(4, 255, 255, 255);
    printf("   done\n\n");

    /* --- Bước 6: Lấy buffer --- */
    printf("── Bước 6: led_get_buffer()\n");
    const uint32_t *buf = led_get_buffer();
    printf("   pointer = %p\n\n", (const void *)buf);

    /* --- Bước 7: In hex --- */
    printf("── Bước 7: In giá trị hex tại index 0, 4, 9\n");
    print_pixel(0, buf);
    print_pixel(4, buf);
    print_pixel(9, buf);
    printf("\n");
    printf("   Xác nhận:\n");
    printf("   buffer[0] = 0x%08X  %s (expect 0x0000FF00 = Red)\n",
           buf[0], buf[0] == 0x0000FF00 ? "✅" : "❌");
    printf("   buffer[4] = 0x%08X  %s (expect 0x00FFFFFF = White)\n",
           buf[4], buf[4] == 0x00FFFFFF ? "✅" : "❌");
    printf("   buffer[9] = 0x%08X  %s (expect 0x000000FF = Blue)\n",
           buf[9], buf[9] == 0x000000FF ? "✅" : "❌");
    printf("\n");

    /* --- Bước 8: Fill Green --- */
    printf("── Bước 8: led_fill(0, 255, 0) → Green all\n");
    led_fill(0, 255, 0);
    printf("   done\n\n");

    /* --- Bước 9: Kiểm tra toàn buffer = Green --- */
    printf("── Bước 9: Kiểm tra tất cả pixel = 0x00FF0000\n");
    check_all_equal("all 10 pixels = 0x00FF0000 (Green)", 0x00FF0000);
    printf("\n");

    /* --- Bước 10: Shutdown --- */
    printf("── Bước 10: led_shutdown()\n");
    led_shutdown();
    printf("   buffer after shutdown = %p  %s\n",
           (const void *)led_get_buffer(),
           led_get_buffer() == NULL ? "✅ NULL (OK)" : "❌ Not NULL!");
    printf("   count  after shutdown = %zu  %s\n",
           led_get_pixel_count(),
           led_get_pixel_count() == 0 ? "✅ 0 (OK)" : "❌ Not 0!");

    printf("\n╔══════════════════════════════════════════════════╗\n");
    printf("║   Demo complete!                                  ║\n");
    printf("╚══════════════════════════════════════════════════╝\n");

    return 0;
}
