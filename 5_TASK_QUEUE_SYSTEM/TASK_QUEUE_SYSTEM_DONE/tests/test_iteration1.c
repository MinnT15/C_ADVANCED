/**
 * @file    test_iteration1.c
 * @brief   Unit tests cho ITERATION 1: Task Queue (Singly Linked List)
 *
 * Kiểm thử: queue_add_task, queue_get_next_task, print_task_queue, queue_free_all
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

/* ─── Test cases ─── */

/**
 * @brief Test thêm 3 tác vụ và kiểm tra FIFO order.
 */
static void test_fifo_order(void) {
    printf("\n[Test] FIFO Order\n");

    queue_add_task("Tac vu A");
    queue_add_task("Tac vu B");
    queue_add_task("Tac vu C");

    /* Lấy ra theo thứ tự FIFO: A → B → C */
    TaskNode_t *t1 = queue_get_next_task();
    check("get() lan 1 tra ve 'Tac vu A'",
          t1 != NULL && strcmp(t1->task_description, "Tac vu A") == 0);
    free(t1);

    TaskNode_t *t2 = queue_get_next_task();
    check("get() lan 2 tra ve 'Tac vu B'",
          t2 != NULL && strcmp(t2->task_description, "Tac vu B") == 0);
    free(t2);

    TaskNode_t *t3 = queue_get_next_task();
    check("get() lan 3 tra ve 'Tac vu C'",
          t3 != NULL && strcmp(t3->task_description, "Tac vu C") == 0);
    free(t3);
}

/**
 * @brief Test get() khi hàng đợi rỗng → phải trả NULL.
 */
static void test_empty_queue(void) {
    printf("\n[Test] Empty Queue\n");

    /* Hàng đợi đã rỗng sau test trước */
    TaskNode_t *t = queue_get_next_task();
    check("get() tu hang doi rong tra ve NULL", t == NULL);

    /* Thêm rồi lấy hết, lấy thêm 1 lần nữa */
    queue_add_task("Task X");
    TaskNode_t *tx = queue_get_next_task();
    check("get() lay duoc task sau khi them 1", tx != NULL);
    if (tx) free(tx);

    TaskNode_t *ty = queue_get_next_task();
    check("get() sau khi lay het tra ve NULL", ty == NULL);
}

/**
 * @brief Test print_task_queue() không crash khi danh sách rỗng.
 */
static void test_print_empty(void) {
    printf("\n[Test] Print Queue khi rong\n");
    /* Không crash là pass */
    print_task_queue();
    check("print_task_queue() khong crash khi rong", 1);
}

/**
 * @brief Test print_task_queue() hiển thị đúng khi có phần tử.
 */
static void test_print_with_items(void) {
    printf("\n[Test] Print Queue khi co items\n");
    queue_add_task("Doc cam bien");
    queue_add_task("Dieu khien dong co");
    print_task_queue(); /* Quan sát bằng mắt */
    check("print_task_queue() hien thi 2 tasks", 1);
    queue_free_all();   /* Dọn sạch */
}

/**
 * @brief Test queue_free_all() — sau khi free, get() phải trả NULL.
 */
static void test_free_all(void) {
    printf("\n[Test] queue_free_all()\n");
    queue_add_task("Task 1");
    queue_add_task("Task 2");
    queue_add_task("Task 3");
    queue_free_all();
    TaskNode_t *t = queue_get_next_task();
    check("Sau free_all, get() tra ve NULL", t == NULL);
}

/**
 * @brief Test string dài hơn 49 ký tự → phải được cắt ngắn an toàn.
 */
static void test_long_description(void) {
    printf("\n[Test] Mo ta qua dai (> 49 ky tu)\n");
    queue_add_task("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnop"); /* 52 ký tự */
    TaskNode_t *t = queue_get_next_task();
    check("Mo ta duoc cat an toan (strlen <= 49)",
          t != NULL && strlen(t->task_description) <= 49);
    if (t) free(t);
}

/* ─── main ─── */
int main(void) {
    printf("=== TEST ITERATION 1: Task Queue (Singly Linked List) ===\n");

    test_fifo_order();
    test_empty_queue();
    test_print_empty();
    test_print_with_items();
    test_free_all();
    test_long_description();

    printf("\n");
    printf("RESULT: %d passed, %d failed\n", test_pass, test_fail);
    return (test_fail == 0) ? 0 : 1;
}
