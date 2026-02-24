#ifndef LED_RGB_H
#define LED_RGB_H

/**
 * @file    led_rgb.h
 * @brief   LED RGB Strip Driver — Public API
 *
 * Mô phỏng driver điều khiển dải LED RGB (chuẩn WS2812B).
 * Định dạng màu: G-R-B (Green-Red-Blue) trong uint32_t 24-bit.
 *
 * Cấu trúc bit:
 *   [31..24]   [23..16]   [15..8]   [7..0]
 *   Unused     Green      Red       Blue
 *
 * Ví dụ:
 *   Red   (255,0,0)     → 0x0000FF00
 *   Green (0,255,0)     → 0x00FF0000
 *   Blue  (0,0,255)     → 0x000000FF
 *   White (255,255,255) → 0x00FFFFFF
 */

#include <stdint.h>   /* uint32_t, uint8_t */
#include <stddef.h>   /* size_t            */

/* ============================================================
 * LIFECYCLE
 * ============================================================ */

/**
 * @brief  Khởi tạo buffer cho dải LED.
 * @param  num_pixels  Số lượng pixel (phải > 0).
 * @return 0 nếu thành công, -1 nếu thất bại.
 * @note   Toàn bộ buffer được khởi tạo về 0 (màu đen).
 */
int led_init(size_t num_pixels);

/**
 * @brief  Giải phóng bộ nhớ đã cấp phát.
 * @note   An toàn khi gọi nhiều lần.
 */
void led_shutdown(void);

/* ============================================================
 * WRITE OPERATIONS
 * ============================================================ */

/**
 * @brief  Đặt màu cho một pixel tại vị trí index.
 * @param  index  Vị trí pixel [0, num_pixels-1]. Bỏ qua nếu invalid.
 * @param  r      Giá trị Red   [0, 255].
 * @param  g      Giá trị Green [0, 255].
 * @param  b      Giá trị Blue  [0, 255].
 */
void led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief  Tô toàn bộ dải LED với một màu duy nhất.
 * @param  r, g, b  Giá trị màu RGB [0, 255].
 */
void led_fill(uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief  Tắt toàn bộ dải LED (đặt màu về đen).
 */
void led_clear(void);

/* ============================================================
 * READ OPERATIONS (for testing)
 * ============================================================ */

/**
 * @brief  Lấy con trỏ read-only tới buffer dữ liệu.
 * @return Pointer hằng tới buffer, hoặc NULL nếu chưa init.
 */
const uint32_t *led_get_buffer(void);

/**
 * @brief  Lấy số lượng pixel của dải LED.
 * @return Số pixel, hoặc 0 nếu chưa init.
 */
size_t led_get_pixel_count(void);

#endif /* LED_RGB_H */
