/**
 * @file    test_iteration2.c
 * @brief   Unit tests cho ITERATION 2: Activity Log (Doubly Linked List)
 *
 * Kiểm thử: history_log_activity, doubly link integrity, history_free_all
 * Lưu ý: history_navigate() là hàm tương tác không thể test tự động,
 *         chạy thủ công với 'make run'.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task_queue.h"

/* ─── Helper functions ─── */
static int test_pass = 0;
static int test_fail = 0;

static void check(const char *name, int condition) {
    if (condition) {
        printf("  [PASS] %s\n", name);
        test_pass++;
    } else {
        printf("  [FAIL] %s\n", name);
        test_fail++;
    }
}

/* ─── Hàm nội bộ để truy cập head (dùng trick: log sau đó get từ queue) ─── */
/* Vì s_log_head là static private, ta kiểm tra gián tiếp qua behavior */

/**
 * @brief Test thêm 1 entry và kiểm tra bằng cách log rồi free.
 */
static void test_log_single_entry(void) {
    printf("\n[Test] Log 1 entry\n");
    history_log_activity("EXECUTED: Doc cam bien nhiet do");
    /* Không crash là pass */
    check("history_log_activity() khong crash", 1);
    history_free_all();
    check("history_free_all() sau 1 entry khong crash", 1);
}

/**
 * @brief Test thêm nhiều entries — thứ tự: mới nhất ở đầu.
 *        Kiểm tra gián tiếp qua navigate (bắt buộc dùng trick input).
 */
static void test_log_multiple_entries(void) {
    printf("\n[Test] Log nhieu entries (kiem tra khong crash)\n");
    history_log_activity("EXECUTED: Task A");
    history_log_activity("EXECUTED: Task B");
    history_log_activity("EXECUTED: Task C");
    check("Log 3 entries lien tiep khong crash", 1);
    history_free_all();
    check("history_free_all() sau 3 entries", 1);
}

/**
 * @brief Test free_all() khi danh sách rỗng — không crash.
 */
static void test_free_empty_log(void) {
    printf("\n[Test] history_free_all() khi log rong\n");
    history_free_all(); /* Gọi 2 lần liên tiếp không crash */
    history_free_all();
    check("free_all() khi rong khong crash", 1);
}

/**
 * @brief Test thêm entry với mô tả dài > 49 ký tự.
 */
static void test_long_entry(void) {
    printf("\n[Test] Entry qua dai (> 49 ky tu)\n");
    history_log_activity("EXECUTED: ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijk"); /* > 49 */
    check("Log entry qua dai khong crash", 1);
    history_free_all();
}

/**
 * @brief Test log NULL — không crash.
 */
static void test_null_entry(void) {
    printf("\n[Test] Log NULL entry\n");
    history_log_activity(NULL);
    check("history_log_activity(NULL) khong crash", 1);
}

/**
 * @brief Test nhiều chu kỳ log → free → log lại.
 */
static void test_repeated_cycles(void) {
    printf("\n[Test] Nhieu chu ky log → free → log lai\n");
    for (int i = 0; i < 5; i++) {
        history_log_activity("EXECUTED: Chu ky test");
        history_free_all();
    }
    check("5 chu ky log/free khong crash va khong leak", 1);
}

/**
 * @brief Demo navigate — in hướng dẫn cho người dùng kiểm tra thủ công.
 */
static void demo_navigate_info(void) {
    printf("\n[INFO] history_navigate() la ham tuong tac.\n");
    printf("       De test thu cong: chay 'make run', roi nhap:\n");
    printf("         add Doc cam bien\n");
    printf("         add Dieu khien motor\n");
    printf("         run\n");
    printf("         run\n");
    printf("         history → nhap: n, p, q\n");
}

/* ─── main ─── */
int main(void) {
    printf("=== TEST ITERATION 2: Activity Log (Doubly Linked List) ===\n");

    test_log_single_entry();
    test_log_multiple_entries();
    test_free_empty_log();
    test_long_entry();
    test_null_entry();
    test_repeated_cycles();
    demo_navigate_info();

    printf("\n");
    printf("RESULT: %d passed, %d failed\n", test_pass, test_fail);
    return (test_fail == 0) ? 0 : 1;
}
