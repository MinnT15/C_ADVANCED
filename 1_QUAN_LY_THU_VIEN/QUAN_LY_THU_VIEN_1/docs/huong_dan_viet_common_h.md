# Hướng Dẫn Viết File `common.h` Từng Bước

## Mục Đích File `common.h`

File này chứa **tất cả định nghĩa chung** mà các module khác sẽ dùng:
- Constants (hằng số)
- Error codes (mã lỗi)
- Data structures (cấu trúc dữ liệu)
- Include các thư viện chuẩn

---

## Bước 1: Mở File Để Chỉnh Sửa

```bash
nano include/common.h
# Hoặc: vim include/common.h
# Hoặc: code include/common.h (VSCode)
```

---

## Bước 2: Header Guards (Bảo vệ Header)

**Mục đích**: Tránh include file nhiều lần gây lỗi.

**Viết:**
```c
#ifndef COMMON_H
#define COMMON_H

// Nội dung file sẽ ở đây

#endif /* COMMON_H */
```

**Giải thích:**
- `#ifndef COMMON_H` - Nếu COMMON_H chưa được định nghĩa
- `#define COMMON_H` - Định nghĩa COMMON_H
- `#endif` - Kết thúc điều kiện
- Khi file được include lần 2, `COMMON_H` đã tồn tại → bỏ qua nội dung

---

## Bước 3: Include Thư Viện Chuẩn

**Viết ngay sau `#define COMMON_H`:**
```c
#include <stdio.h>      // printf, scanf, FILE
#include <stdlib.h>     // malloc, free, exit
#include <string.h>     // strcpy, strcmp, strlen
#include <stdbool.h>    // bool, true, false
#include <ctype.h>      // isdigit, isalpha
```

**Giải thích:**
- `stdio.h` - Input/output (printf, scanf)
- `stdlib.h` - Standard library (memory, exit)
- `string.h` - String operations
- `stdbool.h` - Boolean type (true/false)
- `ctype.h` - Character checking (isdigit...)

---

## Bước 4: Định Nghĩa Constants (Hằng Số)

### 4.1. Maximum Limits (Giới hạn tối đa)

```c
/* ========== CONSTANTS ========== */

/* Maximum limits */
#define MAX_BOOKS 100
#define MAX_USERS 50
#define MAX_BORROWED 5
```

**Giải thích:**
- `MAX_BOOKS 100` - Thư viện tối đa 100 cuốn sách
- `MAX_USERS 50` - Hệ thống tối đa 50 người dùng
- `MAX_BORROWED 5` - Mỗi người mượn tối đa 5 cuốn

**Lợi ích**: Dễ thay đổi sau này, không hardcode số trong code.

### 4.2. String Lengths (Độ dài chuỗi)

```c
/* String lengths */
#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 50
#define MAX_NAME_LENGTH 50
```

**Giải thích:**
- `MAX_TITLE_LENGTH` - Tiêu đề sách tối đa 100 ký tự
- `MAX_AUTHOR_LENGTH` - Tên tác giả tối đa 50 ký tự
- `MAX_NAME_LENGTH` - Tên người dùng tối đa 50 ký tự

### 4.3. File Paths (Đường dẫn file)

```c
/* File paths */
#define BOOKS_FILE "data/books.txt"
#define USERS_FILE "data/users.txt"
```

**Giải thích:**
- Đường dẫn đến file lưu dữ liệu sách và người dùng
- Dùng constant để dễ thay đổi vị trí file sau này

---

## Bước 5: Định Nghĩa Error Codes (Mã Lỗi)

```c
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
```

**Giải thích từng mã lỗi:**

| Mã Lỗi | Giá Trị | Ý Nghĩa |
|---------|---------|---------|
| `SUCCESS` | 0 | Thành công |
| `ERROR_INVALID_INPUT` | -1 | Dữ liệu đầu vào không hợp lệ |
| `ERROR_NOT_FOUND` | -2 | Không tìm thấy (sách/user) |
| `ERROR_ALREADY_EXISTS` | -3 | Đã tồn tại (ID trùng) |
| `ERROR_FULL` | -4 | Đầy (thư viện/danh sách) |
| `ERROR_BOOK_BORROWED` | -5 | Sách đã được mượn |
| `ERROR_BOOK_NOT_BORROWED` | -6 | Sách chưa được mượn |
| `ERROR_MAX_BORROWED_REACHED` | -7 | Đã mượn tối đa |
| `ERROR_FILE_IO` | -8 | Lỗi đọc/ghi file |
| `ERROR_NULL_POINTER` | -9 | Con trỏ NULL |

**Cách dùng:**
```c
int result = add_book(...);
if (result == ERROR_ALREADY_EXISTS) {
    printf("Lỗi: ID sách đã tồn tại!\n");
}
```

---

## Bước 6: Định Nghĩa Data Structures (Cấu Trúc Dữ Liệu)

### 6.1. Book Structure (Cấu trúc Sách)

```c
/* ========== DATA STRUCTURES ========== */

/**
 * @brief Book structure
 */
typedef struct {
    int id;
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    bool is_borrowed;
} Book;
```

**Giải thích từng field:**
- `int id` - ID duy nhất của sách (VD: 1, 2, 3...)
- `char title[100]` - Tiêu đề sách (VD: "Clean Code")
- `char author[50]` - Tác giả (VD: "Robert Martin")
- `bool is_borrowed` - Trạng thái: `true` = đã mượn, `false` = còn

**Ví dụ sử dụng:**
```c
Book book1;
book1.id = 1;
strcpy(book1.title, "Clean Code");
strcpy(book1.author, "Robert Martin");
book1.is_borrowed = false;
```

### 6.2. User Structure (Cấu trúc Người Dùng)

```c
/**
 * @brief User structure
 */
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int borrowed_books[MAX_BORROWED];
    int borrowed_count;
} User;
```

**Giải thích từng field:**
- `int id` - ID người dùng (VD: 1, 2, 3...)
- `char name[50]` - Tên người dùng (VD: "Nguyen Van A")
- `int borrowed_books[5]` - Mảng chứa **ID các sách đã mượn**
  - VD: `[2, 5, 7, 0, 0]` = đã mượn sách ID 2, 5, 7
- `int borrowed_count` - Số sách đã mượn (VD: 3)

**Ví dụ sử dụng:**
```c
User user1;
user1.id = 1;
strcpy(user1.name, "Nguyen Van A");
user1.borrowed_books[0] = 2;  // Mượn sách ID 2
user1.borrowed_books[1] = 5;  // Mượn sách ID 5
user1.borrowed_count = 2;     // Đã mượn 2 cuốn
```

### 6.3. Library Structure (Cấu trúc Thư Viện)

```c
/**
 * @brief Library structure - manages all books and users
 */
typedef struct {
    Book books[MAX_BOOKS];
    int book_count;
    User users[MAX_USERS];
    int user_count;
} Library;
```

**Giải thích từng field:**
- `Book books[100]` - Mảng chứa tất cả sách trong thư viện
- `int book_count` - Số sách hiện có (VD: 25)
- `User users[50]` - Mảng chứa tất cả người dùng
- `int user_count` - Số người dùng hiện có (VD: 10)

**Ví dụ sử dụng:**
```c
Library library;
library.book_count = 0;   // Ban đầu chưa có sách
library.user_count = 0;   // Ban đầu chưa có user

// Thêm sách đầu tiên
library.books[0].id = 1;
strcpy(library.books[0].title, "Clean Code");
library.book_count = 1;
```

---

## Bước 7: Hoàn Thiện File

**File hoàn chỉnh sẽ trông như thế này:**

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

---

## Bước 8: Lưu File

**Trong nano:**
- `Ctrl + O` - Lưu file
- `Enter` - Xác nhận tên file
- `Ctrl + X` - Thoát

**Trong vim:**
- `:wq` - Lưu và thoát

---

## Kiểm Tra File

```bash
# Xem nội dung file
cat include/common.h

# Hoặc
less include/common.h
```

---

## Tóm Tắt Cấu Trúc File

```
common.h
├── Header Guards (#ifndef, #define, #endif)
├── Include Libraries (stdio, stdlib, string, stdbool, ctype)
├── Constants
│   ├── Maximum limits (MAX_BOOKS, MAX_USERS, MAX_BORROWED)
│   ├── String lengths (MAX_TITLE_LENGTH, MAX_AUTHOR_LENGTH, MAX_NAME_LENGTH)
│   └── File paths (BOOKS_FILE, USERS_FILE)
├── Error Codes (enum ErrorCode)
└── Data Structures
    ├── Book struct
    ├── User struct
    └── Library struct
```

---

## Câu Hỏi Thường Gặp

**Q: Tại sao cần header guards?**
A: Tránh lỗi khi file được include nhiều lần trong các file khác nhau.

**Q: Tại sao dùng `typedef struct`?**
A: Để có thể viết `Book book1;` thay vì `struct Book book1;` (ngắn gọn hơn).

**Q: Có thể thay đổi MAX_BOOKS sau này không?**
A: Có! Chỉ cần sửa 1 chỗ trong common.h, tất cả code sẽ tự động cập nhật.

**Q: `bool` là kiểu dữ liệu gì?**
A: Boolean (true/false), cần include `<stdbool.h>`.

---

## Checklist Hoàn Thành

- [ ] Mở file `include/common.h`
- [ ] Viết header guards
- [ ] Include các thư viện chuẩn
- [ ] Định nghĩa constants (MAX_BOOKS, MAX_USERS...)
- [ ] Định nghĩa error codes (enum ErrorCode)
- [ ] Định nghĩa Book struct
- [ ] Định nghĩa User struct
- [ ] Định nghĩa Library struct
- [ ] Lưu file
- [ ] Kiểm tra bằng `cat include/common.h`

---

## Tiếp Theo

Sau khi hoàn thành `common.h`, chuyển sang **Bước 3: Tạo Makefile** trong hướng dẫn Giai đoạn 1! 🚀
