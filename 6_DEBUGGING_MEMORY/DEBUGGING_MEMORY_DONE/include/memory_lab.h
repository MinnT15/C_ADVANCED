#ifndef MEMORY_LAB_H
#define MEMORY_LAB_H

/**
 * @file memory_lab.h
 * @brief Public API cho Memory Lab — tái hiện 3 lỗi bộ nhớ kinh điển.
 *
 * Sử dụng:
 *   ./memory_lab_main stack_overflow  → gây SIGSEGV qua đệ quy vô tận
 *   ./memory_lab_main memory_leak     → vòng lặp malloc không free → OOM
 *   ./memory_lab_main out_of_memory   → tương tự memory_leak
 */

/**
 * @brief Gây lỗi Stack Overflow bằng kỹ thuật đệ quy vô tận.
 *
 * Hàm tự gọi lại chính mình không có điều kiện dừng.
 * Mỗi lần gọi in ra độ sâu hiện tại để quan sát.
 * Kết thúc bằng Segmentation Fault khi stack bị tràn.
 *
 * @param depth Độ sâu đệ quy hiện tại (gọi ban đầu với 0).
 */
void trigger_stack_overflow(int depth);

/**
 * @brief Gây lỗi Memory Leak và cuối cùng là Out of Memory.
 *
 * Vòng lặp vô tận malloc 1KB mỗi lần, KHÔNG gọi free() → Memory Leak.
 * Khi malloc trả về NULL (Out of Memory), in thông báo lỗi và exit(1).
 */
void trigger_memory_leak(void);

#endif /* MEMORY_LAB_H */
