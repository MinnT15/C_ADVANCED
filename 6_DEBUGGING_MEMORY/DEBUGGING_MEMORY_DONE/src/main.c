/**
 * @file main.c
 * @brief Entry point — nhận tham số dòng lệnh và dispatch đến scenario tương ứng.
 *
 * Cách chạy:
 *   ./build/memory_lab_main stack_overflow  → trigger_stack_overflow(0)
 *   ./build/memory_lab_main memory_leak     → trigger_memory_leak()
 *   ./build/memory_lab_main out_of_memory   → trigger_memory_leak() (cùng hành vi)
 */

#include "memory_lab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Định nghĩa các tham số hợp lệ */
#define MODE_STACK_OVERFLOW  "stack_overflow"
#define MODE_MEMORY_LEAK     "memory_leak"
#define MODE_OUT_OF_MEMORY   "out_of_memory"

/**
 * @brief In hướng dẫn sử dụng.
 */
static void print_usage(const char *program_name) {
    fprintf(stderr, "Cách dùng: %s <mode>\n", program_name);
    fprintf(stderr, "  mode:\n");
    fprintf(stderr, "    %-20s → Gây lỗi Stack Overflow (Segfault)\n",
            MODE_STACK_OVERFLOW);
    fprintf(stderr, "    %-20s → Gây lỗi Memory Leak đến khi Out of Memory\n",
            MODE_MEMORY_LEAK);
    fprintf(stderr, "    %-20s → Cấp phát đến khi cạn RAM, thoát an toàn\n",
            MODE_OUT_OF_MEMORY);
}

int main(int argc, char *argv[]) {
    /* Kiểm tra số lượng tham số */
    if (argc < 2) {
        fprintf(stderr, "[ERROR] Thiếu tham số!\n\n");
        print_usage(argv[0]);
        return 1;
    }

    const char *mode = argv[1];

    /* In header */
    printf("==============================================\n");
    printf("   Memory Lab — Gỡ lỗi bộ nhớ với GDB\n");
    printf("   Mode: %s\n", mode);
    printf("==============================================\n\n");

    /* Dispatch theo mode */
    if (strcmp(mode, MODE_STACK_OVERFLOW) == 0) {
        printf("[INFO] Bắt đầu Stack Overflow (đệ quy vô tận)...\n");
        printf("[INFO] Dùng GDB: run stack_overflow → backtrace\n\n");
        fflush(stdout);
        trigger_stack_overflow(0);  /* Bắt đầu đệ quy từ depth = 0 */

    } else if (strcmp(mode, MODE_MEMORY_LEAK) == 0) {
        printf("[INFO] Bắt đầu Memory Leak scenario...\n");
        printf("[INFO] Malloc liên tục 1KB, không free() → accumulated leak\n\n");
        fflush(stdout);
        trigger_memory_leak();

    } else if (strcmp(mode, MODE_OUT_OF_MEMORY) == 0) {
        printf("[INFO] Bắt đầu Out of Memory scenario...\n");
        printf("[INFO] Cùng hành vi như memory_leak, chờ đến khi RAM cạn\n\n");
        fflush(stdout);
        trigger_memory_leak();  /* Cùng hàm — đều dẫn đến OOM */

    } else {
        fprintf(stderr, "[ERROR] Mode không hợp lệ: '%s'\n\n", mode);
        print_usage(argv[0]);
        return 1;
    }

    /* Không bao giờ đến đây (hoặc do Segfault, hoặc do exit(1)) */
    return 0;
}
