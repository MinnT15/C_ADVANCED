/*
 * test_iteration1.c — Unit test cho Iteration 1: lstat() + File Type Detection
 *
 * Kiểm thử các hàm:
 *   - filestat_get_info() với file thực, thư mục thực
 *   - filestat_get_type() cho Regular File, Directory, Symbolic Link
 *   - filestat_print_basic() không crash
 */

#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>   /* symlink(), unlink() */
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
 * Test 1: filestat_get_info() với file thường
 * ============================================================ */
static void test_get_info_regular_file(void) {
    struct stat info;
    int result = filestat_get_info("/etc/hostname", &info);
    check("get_info trả về 0 với /etc/hostname", result == 0);
}

/* ============================================================
 * Test 2: filestat_get_info() với thư mục
 * ============================================================ */
static void test_get_info_directory(void) {
    struct stat info;
    int result = filestat_get_info("/tmp", &info);
    check("get_info trả về 0 với /tmp", result == 0);
}

/* ============================================================
 * Test 3: filestat_get_info() với path không tồn tại
 * ============================================================ */
static void test_get_info_nonexistent(void) {
    struct stat info;
    int result = filestat_get_info("/nonexistent_path_xyz_123", &info);
    check("get_info trả về -1 với path không tồn tại", result == -1);
}

/* ============================================================
 * Test 4: filestat_get_info() với NULL pointer
 * ============================================================ */
static void test_get_info_null(void) {
    struct stat info;
    int r1 = filestat_get_info(NULL, &info);
    int r2 = filestat_get_info("/etc/hostname", NULL);
    check("get_info trả về -1 khi path là NULL", r1 == -1);
    check("get_info trả về -1 khi out là NULL", r2 == -1);
}

/* ============================================================
 * Test 5: filestat_get_type() → Regular File
 * ============================================================ */
static void test_type_regular_file(void) {
    struct stat info;
    if (filestat_get_info("/etc/hostname", &info) == 0) {
        const char *type = filestat_get_type(&info);
        check("type của /etc/hostname là \"Regular File\"",
              strcmp(type, "Regular File") == 0);
    } else {
        printf("[SKIP] /etc/hostname không tồn tại\n");
    }
}

/* ============================================================
 * Test 6: filestat_get_type() → Directory
 * ============================================================ */
static void test_type_directory(void) {
    struct stat info;
    if (filestat_get_info("/tmp", &info) == 0) {
        const char *type = filestat_get_type(&info);
        check("type của /tmp là \"Directory\"",
              strcmp(type, "Directory") == 0);
    }
}

/* ============================================================
 * Test 7: filestat_get_type() → Symbolic Link
 * ============================================================ */
static void test_type_symlink(void) {
    const char *link_path = "/tmp/filestat_test_link_iter1";

    /* Tạo symlink tạm */
    unlink(link_path); /* xoá nếu tồn tại */
    if (symlink("/etc/hostname", link_path) == -1) {
        printf("[SKIP] Không thể tạo symlink để test\n");
        return;
    }

    struct stat info;
    if (filestat_get_info(link_path, &info) == 0) {
        const char *type = filestat_get_type(&info);
        check("type của symlink là \"Symbolic Link\"",
              strcmp(type, "Symbolic Link") == 0);
    }

    /* Dọn dẹp */
    unlink(link_path);
}

/* ============================================================
 * Test 8: filestat_get_type() với NULL
 * ============================================================ */
static void test_type_null(void) {
    const char *type = filestat_get_type(NULL);
    check("get_type với NULL trả về \"Unknown\"",
          strcmp(type, "Unknown") == 0);
}

/* ============================================================
 * Test 9: filestat_print_basic() không crash
 * ============================================================ */
static void test_print_basic_no_crash(void) {
    struct stat info;
    if (filestat_get_info("/etc/hostname", &info) == 0) {
        printf("[TEST] filestat_print_basic() output:\n");
        filestat_print_basic("/etc/hostname", &info);
        check("print_basic() không crash", 1);
    }
}

/* ============================================================
 * Main test runner
 * ============================================================ */
int main(void) {
    printf("=== Test Iteration 1: lstat() + File Type Detection ===\n\n");

    test_get_info_regular_file();
    test_get_info_directory();
    test_get_info_nonexistent();
    test_get_info_null();
    test_type_regular_file();
    test_type_directory();
    test_type_symlink();
    test_type_null();
    test_print_basic_no_crash();

    printf("\nRESULT: %d passed, %d failed\n", test_pass, test_fail);
    return (test_fail == 0) ? 0 : 1;
}
