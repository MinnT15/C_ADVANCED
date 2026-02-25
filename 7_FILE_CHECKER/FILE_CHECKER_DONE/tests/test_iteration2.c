/*
 * test_iteration2.c — Unit test cho Iteration 2: Size + Last Modified
 *
 * Kiểm thử các hàm:
 *   - filestat_get_size() trả về kích thước đúng
 *   - filestat_format_time() format thời gian đúng
 *   - filestat_print_all() in đủ 4 trường không crash
 */

#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 600   /* mkstemp() */

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>   /* write(), close(), unlink() */
#include "filestat.h"

/* ============================================================
 * Helper test framework
 * ============================================================ */
static int test_pass = 0;
static int test_fail = 0;

static void check(const char *name, int condition) {
    if (condition) {
        printf("[PASS] %s\n", name);
        test_pass++;
    } else {
        printf("[FAIL] %s\n", name);
        test_fail++;
    }
}

/* ============================================================
 * Test 1: filestat_get_size() với file thực
 * ============================================================ */
static void test_get_size_regular_file(void) {
    struct stat info;

    /* Tạo file tạm với nội dung biết trước */
    char tmp_path[] = "/tmp/filestat_test_XXXXXX";
    int fd = mkstemp(tmp_path);
    if (fd == -1) {
        printf("[SKIP] Không thể tạo file tạm\n");
        return;
    }

    const char *content = "Hello filestat!"; /* 15 bytes */
    write(fd, content, 15);
    close(fd);

    if (filestat_get_info(tmp_path, &info) == 0) {
        long size = filestat_get_size(&info);
        check("get_size của file 15 bytes trả về 15", size == 15);
        check("get_size trả về giá trị > 0", size > 0);
    }

    unlink(tmp_path);
}

/* ============================================================
 * Test 2: filestat_get_size() với thư mục
 * ============================================================ */
static void test_get_size_directory(void) {
    struct stat info;
    if (filestat_get_info("/tmp", &info) == 0) {
        long size = filestat_get_size(&info);
        check("get_size của /tmp trả về giá trị >= 0", size >= 0);
    }
}

/* ============================================================
 * Test 3: filestat_get_size() với NULL
 * ============================================================ */
static void test_get_size_null(void) {
    long size = filestat_get_size(NULL);
    check("get_size với NULL trả về 0", size == 0);
}

/* ============================================================
 * Test 4: filestat_format_time() có format đúng
 * ============================================================ */
static void test_format_time_output(void) {
    struct stat info;
    if (filestat_get_info("/etc/hostname", &info) == 0) {
        char buf[64];
        filestat_format_time(&info, buf, sizeof(buf));

        /* Kiểm tra output không rỗng */
        check("format_time trả về chuỗi không rỗng", strlen(buf) > 0);

        /* Kiểm tra format có dấu '-' (YYYY-MM-DD) */
        check("format_time chứa dấu '-' (YYYY-MM-DD)", strchr(buf, '-') != NULL);

        /* Kiểm tra format có dấu ':' (HH:MM:SS) */
        check("format_time chứa dấu ':' (HH:MM:SS)", strchr(buf, ':') != NULL);

        /* Kiểm tra độ dài tối thiểu (YYYY-MM-DD HH:MM:SS = 19 chars) */
        check("format_time có độ dài >= 19", (int)strlen(buf) >= 19);

        printf("[INFO] Thời gian format: \"%s\"\n", buf);
    }
}

/* ============================================================
 * Test 5: filestat_format_time() với NULL/zero buffer
 * ============================================================ */
static void test_format_time_edge_cases(void) {
    struct stat info;
    filestat_get_info("/etc/hostname", &info);

    /* Không crash với NULL buf */
    filestat_format_time(&info, NULL, 0);
    check("format_time với NULL buf không crash", 1);

    /* Không crash với NULL info */
    char buf[64];
    filestat_format_time(NULL, buf, sizeof(buf));
    check("format_time với NULL info không crash", 1);
}

/* ============================================================
 * Test 6: filestat_print_all() — in đủ 4 trường
 * ============================================================ */
static void test_print_all_no_crash(void) {
    struct stat info;
    if (filestat_get_info("/etc/hostname", &info) == 0) {
        printf("[TEST] filestat_print_all() output:\n");
        filestat_print_all("/etc/hostname", &info);
        check("print_all() không crash với file thực", 1);
    }
}

/* ============================================================
 * Test 7: filestat_print_all() với thư mục
 * ============================================================ */
static void test_print_all_directory(void) {
    struct stat info;
    if (filestat_get_info("/tmp", &info) == 0) {
        printf("[TEST] filestat_print_all() cho /tmp:\n");
        filestat_print_all("/tmp", &info);
        check("print_all() không crash với directory", 1);
    }
}

/* ============================================================
 * Main test runner
 * ============================================================ */
int main(void) {
    printf("=== Test Iteration 2: Size + Last Modified ===\n\n");

    test_get_size_regular_file();
    test_get_size_directory();
    test_get_size_null();
    test_format_time_output();
    test_format_time_edge_cases();
    test_print_all_no_crash();
    test_print_all_directory();

    printf("\nRESULT: %d passed, %d failed\n", test_pass, test_fail);
    return (test_fail == 0) ? 0 : 1;
}
