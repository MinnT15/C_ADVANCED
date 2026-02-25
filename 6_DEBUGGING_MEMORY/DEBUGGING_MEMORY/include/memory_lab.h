#ifndef MEMORY_LAB_H
#define MEMORY_LAB_H

/**
 * @file memory_lab.h
 * @brief Public API cho Memory Lab — tái hiện 3 lỗi bộ nhớ kinh điển.
 *
 * TODO: Đọc STEP_BY_STEP_GUIDE.md và tự implement từng hàm.
 */

/**
 * @brief Gây lỗi Stack Overflow bằng kỹ thuật đệ quy vô tận.
 * @param depth Độ sâu đệ quy hiện tại (gọi ban đầu với 0).
 */
void trigger_stack_overflow(int depth);

/**
 * @brief Gây lỗi Memory Leak và cuối cùng là Out of Memory.
 *        Khi malloc trả về NULL: in thông báo và exit(1).
 */
void trigger_memory_leak(void);

#endif /* MEMORY_LAB_H */
