---
description: Tự động phân tích đề bài C, tạo tài liệu, cấu trúc thư mục và code hoàn chỉnh theo quy trình chuyên nghiệp
---

# WORKFLOW: C PROJECT BUILDER

Workflow này được kích hoạt khi user đưa đề bài (PDF, text, hoặc @mention file) và muốn AI tự động xử lý toàn bộ theo mô hình đã làm với dự án `4_LED_RGB`.

---

## BƯỚC 1 — NHẬN ĐỀ BÀI VÀ XÁC ĐỊNH NGỮ CẢNH

- Đọc file đề bài (PDF dùng `pdftotext`, text đọc trực tiếp)
- Xác định:
  - Tên dự án (PROJECT_NAME) — viết HOA, dùng gạch dưới, ví dụ: `LED_RGB`, `SMART_METER`
  - Ngôn ngữ: C (std=c99)
  - Thư mục làm việc: chỉ trong thư mục hiện tại của user (không ra ngoài)
- Hỏi user nếu thiếu thông tin về tên dự án hoặc thư mục đích

---

## BƯỚC 2 — TẠO CẤU TRÚC THƯ MỤC

Tạo 2 thư mục trong thư mục dự án:

```
<PROJECT_NAME>/           ← Bản luyện tập (files rỗng)
<PROJECT_NAME>_DONE/      ← Bản hoàn chỉnh (có code)
```

Mỗi thư mục có cấu trúc chuẩn:
```
├── include/              ← Header files (.h)
├── src/                  ← Source files (.c): module.c + main.c
├── tests/                ← test_iteration1.c ... test_iterationN.c
├── build/                ← Output (tự tạo khi build)
├── logs/                 ← Log files
├── docs/                 ← Toàn bộ tài liệu .md
└── Makefile              ← Build system cho Linux/GCC
```

Tạo thư mục và file rỗng trước, sau đó điền code vào `_DONE`.

---

## BƯỚC 3 — TẠO TÀI LIỆU (trong cả 2 thư mục /docs)

// turbo
Tạo 3 file markdown trong `docs/`:

### 3.1 `docs/PHAN_TICH_DE_BAI.md`
Gồm:
- Tổng quan bối cảnh kỹ thuật
- Bảng API cần implement (tên hàm, input, output, mô tả)
- Định dạng dữ liệu (struct, bit layout nếu có)
- Kịch bản kiểm thử theo đề bài (các bước cụ thể)
- Bảng giá trị kỳ vọng
- Lưu ý quan trọng

### 3.2 `docs/KE_HOACH_THUC_THI.md`
Gồm (áp dụng quy trình SDLC chuẩn):
- **Phase 1 — Requirements**: Bảng 5W1H, Functional Requirements (FR-001..N), Non-Functional Requirements, Technical Constraints
- **Phase 2 — Design**: 7 bước (Entities → Structs → Operations → Function Signatures → Modules → Project Structure → System Diagram)
- **Phase 3 — Implementation Plan**: Danh sách iterations, mỗi iteration = 1-2 hàm + mục tiêu
- **Phase 4 — Testing Strategy**: Test cases quan trọng, lệnh chạy
- **Phase 5 — Git Workflow**: Branch strategy, commit convention
- Checklist tổng thể

### 3.3 `docs/STEP_BY_STEP_GUIDE.md`
Gồm (hướng dẫn tự code từng bước):
- Triết lý Incremental Development (sai vs đúng)
- Mỗi Iteration bao gồm:
  - Mục tiêu rõ ràng
  - Giải thích lý thuyết trước khi code
  - Code mẫu đầy đủ (header, implementation, test)
  - Lệnh build và chạy: `make testN`
  - Output mong đợi
  - Checklist pass/fail
  - Lệnh git commit
- Tổng kết và Master Checklist

---

## BƯỚC 4 — TẠO MAKEFILE

// turbo
Tạo `Makefile` chuẩn cho Linux/GCC với các targets:

```makefile
CC     = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -g
BUILD_DIR = build
LOG_DIR   = logs

# Targets bắt buộc:
all      → Build chương trình chính
run      → Build và chạy main.c
testN    → Build và chạy từng iteration test (N = 1..số iterations)
clean    → Xoá build/
cleanall → Xoá build/ và logs/
help     → Hiển thị danh sách lệnh
```

Mỗi `testN` phải:
1. Compile `src/<module>.c`
2. Link với `tests/test_iterationN.c`
3. Chạy ngay lập tức và in output

---

## BƯỚC 5 — VIẾT CODE VÀO `<PROJECT_NAME>_DONE`

// turbo
Thứ tự viết code:

1. **`include/<module>.h`** — Viết trước tiên (public API contract)
   - Header guard `#ifndef`
   - Include cần thiết (`stdint.h`, `stddef.h`, v.v.)
   - Khai báo đầy đủ các hàm với comment Doxygen
   - Không chứa implementation

2. **`src/<module>.c`** — Implementation
   - Static private state (global variables ẩn)
   - Static helper functions (không expose ra .h)
   - Implement từng nhóm hàm theo iteration
   - Boundary check đầy đủ
   - Placeholder `(void)param` cho hàm chưa implement

3. **`src/main.c`** — Demo theo kịch bản đề bài
   - Chạy đúng N bước như đề bài yêu cầu
   - In kết quả hex/giá trị có xác nhận ✅/❌
   - Gọi helper function kiểm tra toàn bộ buffer

4. **`tests/test_iteration1..N.c`** — Unit tests
   - Mỗi file test một nhóm chức năng
   - Helper `check(name, condition)` và `check_hex(name, actual, expected)`
   - In `RESULT: X passed, Y failed`
   - `return (test_fail == 0) ? 0 : 1`

---

## BƯỚC 6 — BUILD VÀ VERIFY

// turbo
Sau khi viết code, bắt buộc chạy:

```bash
cd <PROJECT_NAME>_DONE
mkdir -p build logs
make test1
make test2
# ... tất cả testN
make run
```

- Nếu có lỗi compile/test FAIL → fix ngay trước khi tiếp tục
- Mục tiêu: tất cả tests = `0 failed`
- Chạy valgrind nếu có memory allocation: `valgrind --leak-check=full ./build/...`

---

## BƯỚC 7 — GIT COMMIT

```bash
cd <workspace_root>
git add <PROJECT_FOLDER>/
git commit -m "feat(<project>): add <PROJECT_NAME> and <PROJECT_NAME>_DONE

- <PROJECT_NAME>: empty skeleton with Makefile and docs for self-practice
- <PROJECT_NAME>_DONE: full implementation, N tests passing, 0 failed
  - <module>.h: public API
  - <module>.c: implementation
  - main.c: integration demo
  - tests/: unit tests for each iteration"
```

---

## QUY TẮC BẮT BUỘC

1. **Ngôn ngữ giao tiếp**: Tiếng Việt cho tất cả comment và tài liệu
2. **Phạm vi**: Chỉ làm việc trong thư mục dự án được chỉ định
3. **Không code hết một lần**: Chia thành iterations có thể test riêng lẻ
4. **Luôn verify**: Phải chạy build + test thực tế, không chỉ viết code
5. **Tên file**: Dùng tên từ đề bài nếu có, ví dụ `led_driver.h` thay vì đặt tên tùy ý
6. **Placeholder pattern**: Khi có hàm chưa implement, dùng `(void)param;` để tránh warning
7. **Static cho private state**: Biến toàn cục nội bộ phải là `static`
8. **Makefile tabs**: Dùng TAB (không phải space) trong Makefile recipes

---

## VÍ DỤ KÍCH HOẠT WORKFLOW

User nhắn:
```
dự án LED_RGB
```
hoặc:
```
@[/path/to/assignment.pdf] phân tích đề bài và tạo dự án
```

→ AI thực hiện từ Bước 1 đến Bước 7 tự động.
