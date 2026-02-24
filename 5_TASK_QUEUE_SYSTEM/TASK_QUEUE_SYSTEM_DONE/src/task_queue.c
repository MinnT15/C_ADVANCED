/**
 * @file    task_queue.c
 * @brief   Implementation của Task Queue (singly linked list)
 *          và Activity Log (doubly linked list)
 *
 * ITERATION 1: Task Queue FIFO — queue_add_task, queue_get_next_task,
 *              print_task_queue, queue_free_all
 * ITERATION 2: Activity Log   — history_log_activity, history_navigate,
 *              history_free_all
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task_queue.h"

/* ─────────────────────────────────────────────────────────────
 * STATE RIÊNG CỦA MODULE (static — ẩn khỏi bên ngoài)
 * ───────────────────────────────────────────────────────────── */

/* Task Queue: singly linked list */
static TaskNode_t *s_head = NULL; /**< Đầu hàng đợi (lấy tác vụ từ đây) */
static TaskNode_t *s_tail = NULL; /**< Cuối hàng đợi (thêm tác vụ vào đây) */

/* Activity Log: doubly linked list */
static HistoryNode_t *s_log_head    = NULL; /**< Đầu danh sách nhật ký */
static HistoryNode_t *s_log_current = NULL; /**< Node đang xem hiện tại */

/* ─────────────────────────────────────────────────────────────
 * ITERATION 1: TASK QUEUE — SINGLY LINKED LIST
 * ───────────────────────────────────────────────────────────── */

/**
 * @brief Thêm tác vụ mới vào cuối hàng đợi.
 *        Trường hợp hàng đợi rỗng: head = tail = new_node.
 *        Trường hợp bình thường: tail->next = new_node, cập nhật tail.
 */
void queue_add_task(const char *description) {
    if (description == NULL) return;

    /* Cấp phát node mới */
    TaskNode_t *new_node = (TaskNode_t *)malloc(sizeof(TaskNode_t));
    if (new_node == NULL) {
        fprintf(stderr, "[LOI] malloc that bai!\n");
        return;
    }

    /* Sao chép mô tả, đảm bảo null-terminate */
    strncpy(new_node->task_description, description, 49);
    new_node->task_description[49] = '\0';
    new_node->next = NULL;

    /* Nối vào cuối danh sách */
    if (s_tail == NULL) {
        /* Hàng đợi đang rỗng */
        s_head = s_tail = new_node;
    } else {
        s_tail->next = new_node;
        s_tail       = new_node;
    }
}

/**
 * @brief Lấy tác vụ từ đầu hàng đợi (FIFO).
 *        Caller phải gọi free() sau khi xử lý xong node trả về.
 */
TaskNode_t *queue_get_next_task(void) {
    if (s_head == NULL) return NULL; /* Hàng đợi rỗng */

    TaskNode_t *task = s_head;
    s_head           = s_head->next;

    /* Nếu vừa lấy node cuối cùng, reset tail */
    if (s_head == NULL) s_tail = NULL;

    task->next = NULL; /* Tách khỏi danh sách */
    return task;
}

/**
 * @brief In tất cả các tác vụ đang chờ trong hàng đợi.
 */
void print_task_queue(void) {
    if (s_head == NULL) {
        printf("[Task Queue - RONG — Khong co tac vu nao dang cho]\n");
        return;
    }

    TaskNode_t *cur = s_head;
    int         i   = 1;
    printf("[Task Queue — Danh sach tac vu dang cho]\n");
    while (cur != NULL) {
        printf("  %d. %s\n", i++, cur->task_description);
        cur = cur->next;
    }
}

/**
 * @brief Giải phóng toàn bộ bộ nhớ còn lại trong hàng đợi.
 */
void queue_free_all(void) {
    TaskNode_t *cur = s_head;
    while (cur != NULL) {
        TaskNode_t *next = cur->next;
        free(cur);
        cur = next;
    }
    s_head = s_tail = NULL;
}

/* ─────────────────────────────────────────────────────────────
 * ITERATION 2: ACTIVITY LOG — DOUBLY LINKED LIST
 * ───────────────────────────────────────────────────────────── */

/**
 * @brief Ghi một mục mới vào đầu nhật ký (prepend).
 *        Mục mới nhất luôn ở đầu danh sách.
 */
void history_log_activity(const char *entry) {
    if (entry == NULL) return;

    HistoryNode_t *new_node = (HistoryNode_t *)malloc(sizeof(HistoryNode_t));
    if (new_node == NULL) {
        fprintf(stderr, "[LOI] malloc that bai!\n");
        return;
    }

    strncpy(new_node->log_entry, entry, 49);
    new_node->log_entry[49] = '\0';

    /* Nối vào đầu danh sách (prepend) */
    new_node->next = s_log_head;
    new_node->prev = NULL;

    if (s_log_head != NULL) {
        s_log_head->prev = new_node; /* Node cũ biết node trước của nó */
    }

    s_log_head    = new_node;
    s_log_current = s_log_head; /* Con trỏ duyệt reset về đầu */
}

/**
 * @brief Tương tác duyệt nhật ký: n=next, p=prev, q=quit.
 */
void history_navigate(void) {
    if (s_log_head == NULL) {
        printf("[Nhat ky trong — Chua co hoat dong nao duoc ghi lai]\n");
        return;
    }

    /* Bắt đầu từ đầu nhật ký */
    s_log_current = s_log_head;
    printf("\n=== DUYỆT NHẬT KÝ ===\n");
    printf("[Hien tai] %s\n", s_log_current->log_entry);

    char cmd[8];
    while (1) {
        printf("Lenh (n=tiep theo, p=truoc do, q=thoat): ");
        fflush(stdout);

        if (scanf("%7s", cmd) != 1) break;

        if (cmd[0] == 'q') {
            printf("[Thoat che do duy nhat ky]\n");
            break;
        } else if (cmd[0] == 'n') {
            if (s_log_current->next == NULL) {
                printf("[Da o cuoi lich su — Khong co muc nao sau day]\n");
            } else {
                s_log_current = s_log_current->next;
                printf("[Hien tai] %s\n", s_log_current->log_entry);
            }
        } else if (cmd[0] == 'p') {
            if (s_log_current->prev == NULL) {
                printf("[Da o dau lich su — Day la muc moi nhat]\n");
            } else {
                s_log_current = s_log_current->prev;
                printf("[Hien tai] %s\n", s_log_current->log_entry);
            }
        } else {
            printf("[Lenh khong hop le. Dung: n, p, hoac q]\n");
        }
    }
}

/**
 * @brief Giải phóng toàn bộ bộ nhớ nhật ký.
 */
void history_free_all(void) {
    HistoryNode_t *cur = s_log_head;
    while (cur != NULL) {
        HistoryNode_t *next = cur->next;
        free(cur);
        cur = next;
    }
    s_log_head = s_log_current = NULL;
}
