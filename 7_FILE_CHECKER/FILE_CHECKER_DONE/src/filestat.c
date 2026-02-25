/*
 * filestat.c — Implementation của module kiểm tra siêu dữ liệu file
 *
 * Cung cấp 6 hàm công khai để:
 *   - Lấy metadata qua lstat() (Iteration 1)
 *   - Detect loại file bằng macro S_IS*() (Iteration 1)
 *   - Trả về kích thước và format thời gian (Iteration 2)
 */

#define _POSIX_C_SOURCE 200112L

#include "filestat.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>

/* ============================================================
 * ITERATION 1: lstat() + File Type Detection
 * ============================================================ */

int filestat_get_info(const char *path, struct stat *out) {
    /* Kiểm tra đầu vào hợp lệ */
    if (path == NULL || out == NULL) {
        fprintf(stderr, "Error: filestat_get_info() nhận NULL pointer\n");
        return -1;
    }

    /* Gọi lstat() — không follow symlink */
    if (lstat(path, out) == -1) {
        fprintf(stderr, "Error: lstat() thất bại với \"%s\": %s\n",
                path, strerror(errno));
        return -1;
    }

    return 0;
}

const char *filestat_get_type(const struct stat *info) {
    if (info == NULL) return "Unknown";

    if (S_ISREG(info->st_mode))  return "Regular File";
    if (S_ISDIR(info->st_mode))  return "Directory";
    if (S_ISLNK(info->st_mode))  return "Symbolic Link";

    /* Các loại khác: socket, FIFO, char/block device */
    return "Unknown";
}

void filestat_print_basic(const char *path, const struct stat *info) {
    printf("File Path  : %s\n", path);
    printf("File Type  : %s\n", filestat_get_type(info));
}

/* ============================================================
 * ITERATION 2: Size + Last Modified
 * ============================================================ */

long filestat_get_size(const struct stat *info) {
    if (info == NULL) return 0;
    return (long)info->st_size;
}

void filestat_format_time(const struct stat *info, char *buf, size_t buf_size) {
    if (info == NULL || buf == NULL || buf_size == 0) return;

    /* Chuyển time_t thành struct tm (giờ địa phương) */
    struct tm *tm_info = localtime(&info->st_mtime);

    if (tm_info == NULL) {
        /* Fallback nếu localtime thất bại */
        snprintf(buf, buf_size, "Unknown");
        return;
    }

    /* Format: YYYY-MM-DD HH:MM:SS */
    strftime(buf, buf_size, "%Y-%m-%d %H:%M:%S", tm_info);
}

void filestat_print_all(const char *path, const struct stat *info) {
    char time_buf[64];
    filestat_format_time(info, time_buf, sizeof(time_buf));

    printf("File Path     : %s\n",     path);
    printf("File Type     : %s\n",     filestat_get_type(info));
    printf("Size          : %ld bytes\n", filestat_get_size(info));
    printf("Last Modified : %s\n",     time_buf);
}
