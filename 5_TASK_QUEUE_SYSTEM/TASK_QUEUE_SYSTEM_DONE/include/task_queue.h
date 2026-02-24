/**
 * @file    task_queue.h
 * @brief   Public API cho hệ thống Quản lý Hàng đợi Tác vụ và Nhật ký Hoạt động
 *
 * Module này cung cấp:
 *  - Task Queue : Hàng đợi FIFO dùng singly linked list
 *  - Activity Log: Nhật ký dùng doubly linked list (duyệt tiến/lùi)
 */

#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

/* ─────────────────────────────────────────────────────────────
 * CẤU TRÚC DỮ LIỆU
 * ───────────────────────────────────────────────────────────── */

/**
 * @brief Node của Singly Linked List cho Task Queue.
 *        Hàng đợi FIFO: thêm vào tail, lấy từ head.
 */
typedef struct TaskNode {
    char            task_description[50]; /**< Mô tả tác vụ */
    struct TaskNode *next;                /**< Con trỏ tới node kế tiếp */
} TaskNode_t;

/**
 * @brief Node của Doubly Linked List cho Activity Log.
 *        Cho phép duyệt cả tiến lẫn lùi trong lịch sử.
 */
typedef struct HistoryNode {
    char                log_entry[50]; /**< Nội dung nhật ký */
    struct HistoryNode *next;          /**< Con trỏ tới node kế */
    struct HistoryNode *prev;          /**< Con trỏ tới node trước */
} HistoryNode_t;

/* ─────────────────────────────────────────────────────────────
 * TASK QUEUE API — Singly Linked List
 * ───────────────────────────────────────────────────────────── */

/**
 * @brief  Thêm một tác vụ mới vào cuối hàng đợi.
 * @param  description  Mô tả tác vụ (tối đa 49 ký tự)
 */
void queue_add_task(const char *description);

/**
 * @brief  Lấy tác vụ đầu tiên ra khỏi hàng đợi (FIFO).
 * @return Con trỏ tới TaskNode (caller chịu trách nhiệm free()).
 *         NULL nếu hàng đợi rỗng.
 */
TaskNode_t *queue_get_next_task(void);

/**
 * @brief  In tất cả các tác vụ đang chờ trong hàng đợi.
 */
void print_task_queue(void);

/**
 * @brief  Giải phóng toàn bộ bộ nhớ còn lại trong hàng đợi.
 */
void queue_free_all(void);

/* ─────────────────────────────────────────────────────────────
 * ACTIVITY LOG API — Doubly Linked List
 * ───────────────────────────────────────────────────────────── */

/**
 * @brief  Ghi một mục vào đầu nhật ký (mới nhất ở trước).
 * @param  entry  Nội dung nhật ký (tối đa 49 ký tự)
 */
void history_log_activity(const char *entry);

/**
 * @brief  Tương tác duyệt nhật ký từ console.
 *         n = next, p = previous, q = quit
 */
void history_navigate(void);

/**
 * @brief  Giải phóng toàn bộ bộ nhớ nhật ký.
 */
void history_free_all(void);

#endif /* TASK_QUEUE_H */
