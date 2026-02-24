/**
 * @file    test_iteration3.c
 * @brief   Integration tests: mô phỏng luồng hoạt động toàn hệ thống
 *
 * Kiểm thử: add tasks → run (log) → verify state → cleanup
 * Đây là bài thử nghiệm tích hợp, không test từng hàm riêng lẻ.
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

/* ─── Integration Test Cases ─── */

/**
 * @brief Test 1: Luồng cơ bản — add → run → verify.
 *        Sau khi run 1 task, queue phải bớt 1 phần tử.
 */
static void test_basic_flow(void) {
    printf("\n[Test] Luong co ban: add → run → queue con lai\n");

    /* Thêm 3 tasks */
    queue_add_task("Doc cam bien nhiet do");
    queue_add_task("Dieu khien dong co buoc");
    queue_add_task("Kiem tra trang thai nguon");

    /* Run task 1: lấy ra, ghi log, free */
    TaskNode_t *t1 = queue_get_next_task();
    check("Run task 1: get() tra ve non-NULL", t1 != NULL);
    if (t1) {
        char buf[60];
        snprintf(buf, sizeof(buf), "EXECUTED: %s", t1->task_description);
        history_log_activity(buf);
        check("Run task 1: description dung",
              strcmp(t1->task_description, "Doc cam bien nhiet do") == 0);
        free(t1);
    }

    /* Run task 2 */
    TaskNode_t *t2 = queue_get_next_task();
    check("Run task 2: get() tra ve non-NULL", t2 != NULL);
    if (t2) {
        char buf[60];
        snprintf(buf, sizeof(buf), "EXECUTED: %s", t2->task_description);
        history_log_activity(buf);
        free(t2);
    }

    /* Còn lại 1 task trong queue */
    TaskNode_t *t3 = queue_get_next_task();
    check("Queue con lai 1 task sau 2 lan run", t3 != NULL);
    if (t3) {
        check("Task cuoi la 'Kiem tra trang thai nguon'",
              strcmp(t3->task_description, "Kiem tra trang thai nguon") == 0);
        free(t3);
    }

    /* Queue phải rỗng */
    TaskNode_t *empty = queue_get_next_task();
    check("Queue rong sau khi run het", empty == NULL);

    /* Dọn sạch */
    history_free_all();
}

/**
 * @brief Test 2: Run khi queue rỗng — không crash, trả NULL.
 */
static void test_run_empty_queue(void) {
    printf("\n[Test] Run khi queue rong\n");
    /* Queue đang rỗng sau test trước */
    TaskNode_t *t = queue_get_next_task();
    check("get() khi queue rong tra NULL (khong crash)", t == NULL);
}

/**
 * @brief Test 3: Nhiều chu kỳ add/run liên tiếp.
 */
static void test_multiple_cycles(void) {
    printf("\n[Test] Nhieu chu ky add/run\n");
    const char *tasks[] = {
        "Task Alpha", "Task Beta", "Task Gamma",
        "Task Delta", "Task Epsilon"
    };
    const int N = 5;

    /* Thêm N tasks */
    for (int i = 0; i < N; i++) queue_add_task(tasks[i]);

    /* Run hết N tasks, ghi log */
    int all_ok = 1;
    for (int i = 0; i < N; i++) {
        TaskNode_t *t = queue_get_next_task();
        if (t == NULL || strcmp(t->task_description, tasks[i]) != 0) {
            all_ok = 0;
        }
        if (t) {
            char buf[60];
            snprintf(buf, sizeof(buf), "EXECUTED: %s", t->task_description);
            history_log_activity(buf);
            free(t);
        }
    }
    check("5 tasks duoc run dung FIFO order", all_ok);

    /* Queue rỗng */
    check("Queue rong sau 5 lan run", queue_get_next_task() == NULL);

    /* Dọn sạch */
    history_free_all();
}

/**
 * @brief Test 4: add NULL task — không crash hệ thống.
 */
static void test_add_null_task(void) {
    printf("\n[Test] add NULL task\n");
    queue_add_task(NULL);
    check("queue_add_task(NULL) khong crash", 1);
    queue_free_all(); /* Dọn sạch nếu có */
}

/**
 * @brief Test 5: Cleanup toàn diện — gọi free_all ngay cả khi đã rỗng.
 */
static void test_cleanup(void) {
    printf("\n[Test] Cleanup toan dien\n");
    queue_add_task("Task 1");
    queue_add_task("Task 2");
    history_log_activity("Entry 1");
    history_log_activity("Entry 2");

    queue_free_all();
    history_free_all();

    /* Gọi free lần 2 khi đã rỗng — không crash */
    queue_free_all();
    history_free_all();
    check("Double free_all() khong crash", 1);
}

/* ─── main ─── */
int main(void) {
    printf("=== TEST ITERATION 3: Integration ===\n");

    test_basic_flow();
    test_run_empty_queue();
    test_multiple_cycles();
    test_add_null_task();
    test_cleanup();

    printf("\n");
    printf("RESULT: %d passed, %d failed\n", test_pass, test_fail);
    return (test_fail == 0) ? 0 : 1;
}
