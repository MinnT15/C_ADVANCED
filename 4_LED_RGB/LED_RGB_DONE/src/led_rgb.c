/**
 * @file    led_rgb.c
 * @brief   LED RGB Strip Driver — Implementation
 *
 * Triển khai đầy đủ driver điều khiển dải LED RGB.
 * Định dạng G-R-B: color = (g << 16) | (r << 8) | b
 */

#include "led_rgb.h"

#include <stdlib.h>   /* malloc, free       */
#include <string.h>   /* memset             */
#include <stdio.h>    /* fprintf (for error)*/

/* ============================================================
 * PRIVATE STATE — chỉ file này truy cập được (static)
 * ============================================================ */
static uint32_t *g_pixel_buffer = NULL;
static size_t    g_pixel_count  = 0;

/* ============================================================
 * PRIVATE HELPER
 * ============================================================ */

/**
 * @brief  Đóng gói R, G, B thành uint32_t theo định dạng G-R-B.
 *
 * Định dạng:
 *   Bit [23..16] = Green
 *   Bit [15..8]  = Red
 *   Bit [7..0]   = Blue
 *
 * @return Giá trị màu 32-bit đóng gói.
 */
static uint32_t pack_color(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)g << 16) | ((uint32_t)r << 8) | (uint32_t)b;
}

/* ============================================================
 * LIFECYCLE
 * ============================================================ */

int led_init(size_t num_pixels) {
    /* Kiểm tra input */
    if (num_pixels == 0) {
        fprintf(stderr, "[led_rgb] Error: num_pixels must be > 0\n");
        return -1;
    }

    /* Nếu đã init trước đó → cleanup trước */
    if (g_pixel_buffer != NULL) {
        led_shutdown();
    }

    /* Cấp phát bộ nhớ động */
    g_pixel_buffer = (uint32_t *)malloc(num_pixels * sizeof(uint32_t));
    if (g_pixel_buffer == NULL) {
        fprintf(stderr, "[led_rgb] Error: malloc failed for %zu pixels\n",
                num_pixels);
        return -1;
    }

    /* Khởi tạo tất cả pixel = 0x00000000 (màu đen / tắt) */
    memset(g_pixel_buffer, 0, num_pixels * sizeof(uint32_t));

    /* Lưu số lượng pixel */
    g_pixel_count = num_pixels;

    return 0;  /* Thành công */
}

void led_shutdown(void) {
    if (g_pixel_buffer != NULL) {
        free(g_pixel_buffer);
        g_pixel_buffer = NULL;  /* Tránh dangling pointer */
    }
    g_pixel_count = 0;
}

/* ============================================================
 * WRITE OPERATIONS
 * ============================================================ */

void led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b) {
    /* Boundary check: bỏ qua lặng lẽ nếu không hợp lệ */
    if (g_pixel_buffer == NULL || index >= g_pixel_count) {
        return;
    }
    g_pixel_buffer[index] = pack_color(r, g, b);
}

void led_fill(uint8_t r, uint8_t g, uint8_t b) {
    if (g_pixel_buffer == NULL) return;

    /* Tính màu 1 lần duy nhất — tránh lặp tính lại trong loop */
    uint32_t color = pack_color(r, g, b);

    for (size_t i = 0; i < g_pixel_count; i++) {
        g_pixel_buffer[i] = color;
    }
}

void led_clear(void) {
    /* led_clear = led_fill với màu đen */
    led_fill(0, 0, 0);
}

/* ============================================================
 * READ OPERATIONS
 * ============================================================ */

const uint32_t *led_get_buffer(void) {
    return g_pixel_buffer;  /* const: caller chỉ đọc, không sửa */
}

size_t led_get_pixel_count(void) {
    return g_pixel_count;
}
