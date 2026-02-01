# Hướng Dẫn Giai Đoạn 1: Thiết Lập Cấu Trúc Dự Án

## Mục Tiêu
Tạo cấu trúc thư mục và các file cơ bản cho dự án quản lý thư viện.

---

## Bước 1: Tạo Cấu Trúc Thư Mục

### 1.1. Di chuyển vào thư mục làm việc
```bash
cd /home/minhtri/Working_space/C_ADVANCED/BUOI_1
```

### 1.2. Tạo thư mục dự án và các thư mục con
```bash
mkdir -p library_management/{src,include,data,obj,bin}
```

**Giải thích:**
- `library_management/` - Thư mục gốc của dự án
- `src/` - Chứa các file source code (.c)
- `include/` - Chứa các file header (.h)
- `data/` - Chứa file dữ liệu (books.txt, users.txt)
- `obj/` - Chứa các file object (.o) khi compile
- `bin/` - Chứa file thực thi (executable)

### 1.3. Kiểm tra cấu trúc đã tạo
```bash
cd library_management
tree
# Hoặc nếu không có tree:
ls -R
```

---

## Bước 2: Tạo File `common.h`

### 2.1. Tạo file
```bash
touch include/common.h
```

### 2.2. Mở file và viết nội dung
```bash
nano include/common.h
# Hoặc dùng editor bạn thích: vim, code, gedit...
```

### 2.3. Nội dung cần viết vào `common.h`

```c
/**
 * @file common.h
 * @brief Common definitions, constants, and error codes
 */

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/* ========== CONSTANTS ========== */

/* Maximum limits */
#define MAX_BOOKS 100
#define MAX_USERS 50
#define MAX_BORROWED 5

/* String lengths */
#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 50
#define MAX_NAME_LENGTH 50

/* File paths */
#define BOOKS_FILE "data/books.txt"
#define USERS_FILE "data/users.txt"

/* ========== ERROR CODES ========== */

typedef enum {
    SUCCESS = 0,
    ERROR_INVALID_INPUT = -1,
    ERROR_NOT_FOUND = -2,
    ERROR_ALREADY_EXISTS = -3,
    ERROR_FULL = -4,
    ERROR_BOOK_BORROWED = -5,
    ERROR_BOOK_NOT_BORROWED = -6,
    ERROR_MAX_BORROWED_REACHED = -7,
    ERROR_FILE_IO = -8,
    ERROR_NULL_POINTER = -9
} ErrorCode;

/* ========== DATA STRUCTURES ========== */

typedef struct {
    int id;
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    bool is_borrowed;
} Book;

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int borrowed_books[MAX_BORROWED];
    int borrowed_count;
} User;

typedef struct {
    Book books[MAX_BOOKS];
    int book_count;
    User users[MAX_USERS];
    int user_count;
} Library;

#endif /* COMMON_H */
```

**Giải thích các phần:**
- **Header guards** (`#ifndef`, `#define`, `#endif`): Tránh include file nhiều lần
- **Constants**: Định nghĩa các giá trị cố định
- **ErrorCode enum**: Mã lỗi để xử lý lỗi dễ dàng
- **Structs**: Cấu trúc dữ liệu cho Book, User, Library

---

## Bước 3: Tạo Makefile

### 3.1. Tạo file
```bash
touch Makefile
```

### 3.2. Nội dung Makefile

```makefile
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -I./include
LDFLAGS = 

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin
DATA_DIR = data

# Target executable
TARGET = $(BIN_DIR)/library_app

# Source files (sẽ thêm sau khi tạo các file .c)
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "Build successful! Executable: $(TARGET)"

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Create directories if they don't exist
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Cleaned build artifacts"

# Run the program
run: $(TARGET)
	./$(TARGET)

# Rebuild everything
rebuild: clean all

# Help
help:
	@echo "Available targets:"
	@echo "  all     - Build the project (default)"
	@echo "  clean   - Remove build artifacts"
	@echo "  run     - Build and run the program"
	@echo "  rebuild - Clean and build"
	@echo "  help    - Show this help message"

.PHONY: all clean run rebuild help
```

**Giải thích Makefile:**
- `CC`: Compiler (gcc)
- `CFLAGS`: Compiler flags
  - `-Wall -Wextra -Werror`: Bật tất cả warnings và treat warnings as errors
  - `-std=c11`: Sử dụng C11 standard
  - `-I./include`: Thêm thư mục include vào search path
- `SRCS`: Tự động tìm tất cả file .c trong src/
- `OBJS`: Chuyển đổi danh sách .c thành .o
- **Targets**:
  - `make` hoặc `make all`: Build project
  - `make clean`: Xóa file build
  - `make run`: Build và chạy
  - `make rebuild`: Clean rồi build lại

---

## Bước 4: Tạo README.md

### 4.1. Tạo file
```bash
touch README.md
```

### 4.2. Nội dung README.md

```markdown
# Library Management System

Ứng dụng quản lý thư viện đơn giản được viết bằng C, tuân thủ Clean Code và C Coding Convention.

## Tính Năng

- ✅ Quản lý sách (thêm, sửa, xóa, tìm kiếm)
- ✅ Quản lý người dùng (thêm, sửa, xóa)
- ✅ Quản lý mượn/trả sách
- ✅ Tìm kiếm sách theo tiêu đề, tác giả
- ✅ Hiển thị thông tin sách và người dùng
- ✅ Xử lý lỗi và validation

## Cấu Trúc Dự Án

```
library_management/
├── src/          # Source files (.c)
├── include/      # Header files (.h)
├── obj/          # Object files (generated)
├── bin/          # Executable (generated)
├── data/         # Data files
├── Makefile      # Build configuration
└── README.md     # This file
```

## Yêu Cầu Hệ Thống

- GCC compiler (hỗ trợ C11)
- Make
- Linux/Unix environment

## Cách Sử Dụng

### Build dự án
```bash
make
```

### Chạy chương trình
```bash
make run
```

### Xóa build artifacts
```bash
make clean
```

### Rebuild toàn bộ
```bash
make rebuild
```

## Tác Giả

[Tên của bạn]

## Ngày Tạo

2026-01-17
```

---

## Bước 5: Tạo File Dữ Liệu Mẫu (Optional)

### 5.1. Tạo file books.txt
```bash
touch data/books.txt
```

Nội dung mẫu (có thể để trống):
```
# Format: ID|Title|Author|IsBorrowed
# Example:
# 1|Clean Code|Robert Martin|0
```

### 5.2. Tạo file users.txt
```bash
touch data/users.txt
```

Nội dung mẫu (có thể để trống):
```
# Format: ID|Name|BorrowedBooks|BorrowedCount
# Example:
# 1|Nguyen Van A|2,5,7|3
```

---

## Bước 6: Kiểm Tra Kết Quả

### 6.1. Xem cấu trúc thư mục
```bash
tree
```

Kết quả mong đợi:
```
library_management/
├── bin/
├── data/
│   ├── books.txt
│   └── users.txt
├── include/
│   └── common.h
├── obj/
├── src/
├── Makefile
└── README.md
```

### 6.2. Kiểm tra Makefile
```bash
make help
```

Nên hiển thị danh sách các targets có sẵn.

---

## Checklist Hoàn Thành Giai Đoạn 1

- [ ] Tạo thư mục `library_management/`
- [ ] Tạo các thư mục con: `src/`, `include/`, `data/`, `obj/`, `bin/`
- [ ] Tạo file `include/common.h` với đầy đủ nội dung
- [ ] Tạo `Makefile` với các targets cơ bản
- [ ] Tạo `README.md` với thông tin dự án
- [ ] Tạo file dữ liệu mẫu `data/books.txt` và `data/users.txt`
- [ ] Kiểm tra cấu trúc thư mục bằng `tree` hoặc `ls -R`
- [ ] Test Makefile bằng `make help`

---

## Lưu Ý Quan Trọng

> [!TIP]
> **Editor**: Bạn có thể dùng bất kỳ editor nào: `nano`, `vim`, `VSCode`, `gedit`...

> [!IMPORTANT]
> **Header Guards**: Luôn nhớ thêm header guards trong file .h để tránh lỗi include nhiều lần.

> [!WARNING]
> **Makefile**: Trong Makefile, các dòng lệnh PHẢI bắt đầu bằng TAB, không phải spaces!

> [!NOTE]
> **Thư mục obj/ và bin/**: Sẽ được tạo tự động khi bạn chạy `make`, không cần tạo thủ công.

---

## Sau Khi Hoàn Thành

Khi đã hoàn thành Giai đoạn 1, bạn sẽ có:
- ✅ Cấu trúc dự án hoàn chỉnh
- ✅ File `common.h` với tất cả định nghĩa cần thiết
- ✅ Makefile để build dự án
- ✅ README.md để document

**Tiếp theo**: Chuyển sang **Giai đoạn 2 - Module Utils** để xây dựng các hàm tiện ích.

---

## Câu Hỏi Thường Gặp

**Q: Tại sao cần thư mục obj/ và bin/?**
A: Để tách biệt source code, object files và executable, giúp dự án gọn gàng và dễ quản lý.

**Q: Có thể dùng IDE thay vì Makefile không?**
A: Được, nhưng Makefile giúp bạn hiểu rõ quá trình build và portable hơn.

**Q: File .gitignore cần không?**
A: Nên có để ignore obj/ và bin/. Tạo file `.gitignore`:
```
obj/
bin/
*.o
*.out
```
