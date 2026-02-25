/**
 * @file memory_lab.c
 * @brief Tái hiện 3 lỗi bộ nhớ kinh điển để thực hành gỡ lỗi với GDB.
 *
 * Bài học:
 *   - Stack Overflow: đệ quy vô tận → stack frame tích lũy → SIGSEGV
 *   - Memory Leak: malloc không free → heap tích lũy → cạn RAM
 *   - Out of Memory: malloc trả NULL → cần xử lý an toàn, không crash
 */

#include "memory_lab.h"
#include <stdio.h>
#include <stdlib.h>

/* Kích thước mỗi block cấp phát trong memory_leak scenario */
#define ALLOC_SIZE_BYTES    1024        /* 1 KB */
#define LOG_INTERVAL_BLOCKS 10000       /* In thông báo mỗi 10000 blocks */

/* ==========================================================================
 * ITERATION 1: Stack Overflow
 * ========================================================================== */

/**
 * @brief Hàm đệ quy vô tận — gây Stack Overflow có chủ đích.
 *
 * PHÂN TÍCH GDB:
 *   (gdb) backtrace  → thấy trigger_stack_overflow lặp lại hàng nghìn lần
 *   (gdb) frame 0    → xem frame tại điểm SIGSEGV
 *   (gdb) info frame → chi tiết stack pointer, frame pointer
 */
void trigger_stack_overflow(int depth) {
    /* In độ sâu để quan sát quá trình tích lũy stack frames */
    printf("Stack depth: %d\n", depth);
    fflush(stdout);     /* Đảm bảo flush trước khi crash */

    /* Đệ quy VÔ ĐIỀU KIỆN — không có base case → Stack Overflow */
    trigger_stack_overflow(depth + 1);
}

/* ==========================================================================
 * ITERATION 2: Memory Leak + Out of Memory
 * ========================================================================== */

/**
 * @brief Vòng lặp malloc vô tận — gây Memory Leak có chủ đích.
 *
 * Logic:
 *   while(1) {
 *       ptr = malloc(1KB);   ← Cấp phát từ heap
 *       if (ptr == NULL) → exit(1)  ← Xử lý OOM an toàn
 *       // KHÔNG gọi free(ptr) → đây là Memory Leak
 *   }
 *
 * PHÂN TÍCH GDB:
 *   (gdb) break memory_lab.c:LINE_OF_NULL_CHECK
 *   (gdb) continue   → chờ đến khi OOM
 *   (gdb) backtrace  → xác nhận đang trong trigger_memory_leak
 *   (gdb) print count → số blocks đã cấp phát
 *   (gdb) print ptr   → xác nhận ptr == 0x0 (NULL)
 */
void trigger_memory_leak(void) {
    long long count = 0;    /* Đếm số lần malloc thành công */
    void *ptr = NULL;       /* Con trỏ tới block vừa cấp phát */

    printf("[INFO] Bắt đầu cấp phát liên tục %d bytes/block...\n", ALLOC_SIZE_BYTES);
    printf("[INFO] KHÔNG gọi free() → đây là Memory Leak có chủ đích.\n\n");
    fflush(stdout);

    while (1) {
        /* Cấp phát 1KB từ heap */
        ptr = malloc(ALLOC_SIZE_BYTES);

        /* ----------------------------------------------------------------
         * KIỂM TRA OUT OF MEMORY: malloc thất bại → ptr == NULL
         * Đây là điểm đặt breakpoint trong GDB để phân tích:
         *   (gdb) break memory_lab.c:LINE_BELOW if ptr == 0
         * ---------------------------------------------------------------- */
        if (ptr == NULL) {
            fprintf(stderr,
                "\n[ERROR] Out of Memory! malloc trả về NULL.\n"
                "[INFO]  Số blocks đã cấp phát thành công: %lld\n"
                "[INFO]  Tổng bộ nhớ đã tiêu thụ: ~%lld KB (~%lld MB)\n"
                "[INFO]  Nguyên nhân: malloc() gọi %lld lần mà không có free()\n"
                "[INFO]  Đây chính là Memory Leak dẫn đến Out of Memory.\n"
                "[INFO]  Thoát an toàn với exit(1).\n",
                count,
                count * ALLOC_SIZE_BYTES / 1024,
                count * ALLOC_SIZE_BYTES / 1024 / 1024,
                count);
            exit(1);    /* Thoát an toàn — không crash */
        }

        /* KHÔNG gọi free(ptr) — đây là bug cố ý (Memory Leak) */
        count++;

        /* In tiến độ định kỳ để quan sát */
        if (count % LOG_INTERVAL_BLOCKS == 0) {
            printf("[ALLOC] Block #%lld | Tổng: ~%lld MB\n",
                   count,
                   count * ALLOC_SIZE_BYTES / 1024 / 1024);
            fflush(stdout);
        }
    }
}
