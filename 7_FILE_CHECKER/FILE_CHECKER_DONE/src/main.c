/*
 * main.c — Entry point cho chương trình filestat
 *
 * Demo: đọc metadata của file/thư mục qua lstat() và in ra stdout
 * Kịch bản: /etc/hostname, /tmp, /etc, symlink
 */

#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "filestat.h"

/* Helper: in metadata của một đường dẫn bất kỳ */
static void show_file(const char *path) {
    struct stat info;
    printf("--- %s ---\n", path);
    if (filestat_get_info(path, &info) == 0) {
        filestat_print_all(path, &info);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    /* Yêu cầu đề bài: nhận đúng 1 tham số từ dòng lệnh */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        fprintf(stderr, "Ví dụ: %s /etc/hostname\n", argv[0]);
        return 1;
    }

    /* Chế độ demo: chạy với nhiều tham số */
    if (argc == 2) {
        struct stat info;
        if (filestat_get_info(argv[1], &info) == -1) {
            return 1;
        }
        filestat_print_all(argv[1], &info);
        return 0;
    }

    /* Chạy multi-path demo khi có cờ --demo */
    printf("=== filestat Demo ===\n\n");
    for (int i = 1; i < argc; i++) {
        show_file(argv[i]);
    }

    return 0;
}
