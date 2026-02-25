/**
 * @file memory_lab.c
 * @brief TODO: Tự implement các hàm theo hướng dẫn trong STEP_BY_STEP_GUIDE.md
 *
 * ITERATION 1: Implement trigger_stack_overflow()
 * ITERATION 2: Implement trigger_memory_leak()
 */

#include "memory_lab.h"
#include <stdio.h>
#include <stdlib.h>

/* ==========================================================================
 * ITERATION 1: Stack Overflow
 * TODO: Viết hàm đệ quy vô tận ở đây
 * Gợi ý: In "Stack depth: %d\n" trước mỗi lần gọi đệ quy
 * ========================================================================== */
void trigger_stack_overflow(int depth) {
    /* TODO: Implement tại đây */
    (void)depth;    /* Xóa dòng này khi implement */
}

/* ==========================================================================
 * ITERATION 2: Memory Leak + Out of Memory
 * TODO: Viết vòng lặp while(1) + malloc(1024) + kiểm tra NULL
 * Gợi ý: Đừng quên KHÔNG gọi free() — đây là mục đích của bài!
 * ========================================================================== */
void trigger_memory_leak(void) {
    /* TODO: Implement tại đây */
}
