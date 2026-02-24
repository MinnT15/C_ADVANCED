/**
 * @file    main.c
 * @brief   Chương trình CLI tương tác cho Task Queue System
 *
 * Lệnh hỗ trợ:
 *   add <mô tả>  — Thêm tác vụ vào hàng đợi
 *   run          — Thực thi tác vụ tiếp theo, ghi vào nhật ký
 *   list         — In danh sách tác vụ đang chờ
 *   history      — Duyệt nhật ký hoạt động
 *   quit / exit  — Thoát chương trình
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task_queue.h"

/* Độ dài tối đa của một dòng lệnh nhập vào */
#define MAX_LINE 128

/**
 * @brief In hướng dẫn sử dụng khi khởi động.
 */
static void print_help(void) {
    printf("╔══════════════════════════════════════════════╗\n");
    printf("║     TASK QUEUE SYSTEM — Bo dieu khien       ║\n");
    printf("╠══════════════════════════════════════════════╣\n");
    printf("║  add <mo ta>  — Them tac vu vao hang doi    ║\n");
    printf("║  run          — Thuc thi tac vu tiep theo   ║\n");
    printf("║  list         — Xem danh sach tac vu        ║\n");
    printf("║  history      — Duyet nhat ky hoat dong     ║\n");
    printf("║  help         — Hien thi huong dan          ║\n");
    printf("║  quit / exit  — Thoat                       ║\n");
    printf("╚══════════════════════════════════════════════╝\n");
}

int main(void) {
    char line[MAX_LINE];

    print_help();
    printf("\n");

    /* ── Vòng lặp chính nhận lệnh từ stdin ── */
    while (1) {
        printf("> ");
        fflush(stdout);

        /* Đọc dòng lệnh */
        if (fgets(line, sizeof(line), stdin) == NULL) {
            /* EOF (Ctrl+D) */
            printf("\n[EOF — Thoat chuong trinh]\n");
            break;
        }

        /* Loại bỏ ký tự newline ở cuối */
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') line[len - 1] = '\0';

        /* Bỏ qua dòng rỗng */
        if (line[0] == '\0') continue;

        /* ── Phân tích lệnh ── */

        /* Lệnh: quit / exit */
        if (strcmp(line, "quit") == 0 || strcmp(line, "exit") == 0) {
            printf("[Giai phong bo nho va thoat...]\n");
            break;
        }

        /* Lệnh: list */
        else if (strcmp(line, "list") == 0) {
            print_task_queue();
        }

        /* Lệnh: run */
        else if (strcmp(line, "run") == 0) {
            TaskNode_t *task = queue_get_next_task();
            if (task == NULL) {
                printf("[CANH BAO] Hang doi rong! Khong co tac vu nao de thuc thi.\n");
            } else {
                printf("[THUC THI] >> %s\n", task->task_description);

                /* Ghi nhật ký: "EXECUTED: <mô tả>" */
                char log_buf[60];
                snprintf(log_buf, sizeof(log_buf), "EXECUTED: %s", task->task_description);
                history_log_activity(log_buf);
                printf("[LOG] Da ghi nhat ky: %s\n", log_buf);

                /* Giải phóng bộ nhớ của node tác vụ */
                free(task);
            }
        }

        /* Lệnh: history */
        else if (strcmp(line, "history") == 0) {
            history_navigate();
        }

        /* Lệnh: help */
        else if (strcmp(line, "help") == 0) {
            print_help();
        }

        /* Lệnh: add <mô tả> */
        else if (strncmp(line, "add ", 4) == 0) {
            const char *desc = line + 4; /* Bỏ qua "add " */
            if (strlen(desc) == 0) {
                printf("[LOI] Dung: add <mo ta tac vu>\n");
            } else {
                queue_add_task(desc);
                printf("[DA THEM] Tac vu: \"%s\"\n", desc);
            }
        }

        /* Lệnh không nhận dạng được */
        else {
            printf("[LOI] Lenh khong hop le: \"%s\"\n", line);
            printf("      Nhap 'help' de xem danh sach lenh.\n");
        }
    }

    /* ── Dọn dẹp bộ nhớ trước khi thoát ── */
    queue_free_all();
    history_free_all();

    printf("[OK] Chuong trinh da thoat sach se.\n");
    return 0;
}
