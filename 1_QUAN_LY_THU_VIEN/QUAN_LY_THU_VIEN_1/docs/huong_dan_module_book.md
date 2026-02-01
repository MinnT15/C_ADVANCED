# Hướng Dẫn Xây Dựng Module Book - Đầy Đủ

> Tài liệu này hướng dẫn chi tiết cách xây dựng module Book từ đầu, bao gồm cả file `.h` và `.c`

---

## 📚 Tổng Quan Module Book

### **Module Book là gì?**

Module quản lý **sách** trong thư viện, cung cấp các chức năng CRUD (Create, Read, Update, Delete), tìm kiếm và hiển thị.

### **Chức năng chính:**
- ✅ Thêm sách mới (add_book)
- ✅ Tìm sách theo ID (find_book_by_id)
- ✅ Cập nhật thông tin sách (update_book)
- ✅ Xóa sách (delete_book)
- ✅ Tìm kiếm theo tiêu đề/tác giả
- ✅ Hiển thị danh sách sách

### **Danh sách 10 hàm:**

| # | Hàm | Nhóm | Độ khó |
|---|-----|------|--------|
| 1 | `get_book_count()` | Helper | ⭐ Dễ |
| 2 | `find_book_index_by_id()` | Helper | ⭐⭐ TB |
| 3 | `display_book()` | Display | ⭐ Dễ |
| 4 | `display_all_books()` | Display | ⭐ Dễ |
| 5 | `find_book_by_id()` | CRUD | ⭐⭐ TB |
| 6 | `add_book()` | CRUD | ⭐⭐⭐ Khó |
| 7 | `update_book()` | CRUD | ⭐⭐ TB |
| 8 | `delete_book()` | CRUD | ⭐⭐⭐ Khó |
| 9 | `search_books_by_title()` | Search | ⭐⭐ TB |
| 10 | `search_books_by_author()` | Search | ⭐⭐ TB |

---

# PHẦN 1: Tạo File `book.h`

## Bước 1: Tạo file và header guards

**Tạo file:** `include/book.h`

**Gõ vào:**

```c
/**
 * @file book.h
 * @brief Book management functions
 * @author Minh Tri
 * @date 2026-01-20
 */

#ifndef BOOK_H
#define BOOK_H
```

**Giải thích:**
- `#ifndef BOOK_H` - Kiểm tra chưa được define
- `#define BOOK_H` - Define để tránh include trùng lặp
- Tránh lỗi "multiple definition"

---

## Bước 2: Include các header cần thiết

**Gõ tiếp:**

```c
#include "common.h"
#include "utils.h"
```

**Giải thích:**
- `common.h` - Chứa struct Book, Library, ErrorCode, constants
- `utils.h` - Sử dụng các hàm validation (validate_id, validate_string...)

---

## Bước 3: Khai báo CRUD Operations

**Gõ tiếp:**

```c
/* ========== CRUD OPERATIONS ========== */

/**
 * @brief Add a new book to the library
 * @param lib Pointer to library
 * @param book Book to add
 * @return ErrorCode (SUCCESS or error)
 */
ErrorCode add_book(Library *lib, Book book);

/**
 * @brief Find book by ID
 * @param lib Pointer to library
 * @param id Book ID to find
 * @return Pointer to book if found, NULL otherwise
 */
Book* find_book_by_id(Library *lib, int id);

/**
 * @brief Find book index by ID (helper function)
 * @param lib Pointer to library
 * @param id Book ID to find
 * @return Index if found, -1 otherwise
 */
int find_book_index_by_id(Library *lib, int id);

/**
 * @brief Update book information
 * @param lib Pointer to library
 * @param id Book ID to update
 * @param new_book New book information
 * @return ErrorCode (SUCCESS or error)
 */
ErrorCode update_book(Library *lib, int id, Book new_book);

/**
 * @brief Delete book from library
 * @param lib Pointer to library
 * @param id Book ID to delete
 * @return ErrorCode (SUCCESS or error)
 */
ErrorCode delete_book(Library *lib, int id);
```

---

## Bước 4: Khai báo Search Functions

**Gõ tiếp:**

```c
/* ========== SEARCH FUNCTIONS ========== */

/**
 * @brief Search books by title (partial match)
 * @param lib Pointer to library
 * @param title Title to search for
 */
void search_books_by_title(Library *lib, const char *title);

/**
 * @brief Search books by author (partial match)
 * @param lib Pointer to library
 * @param author Author to search for
 */
void search_books_by_author(Library *lib, const char *author);
```

---

## Bước 5: Khai báo Display Functions

**Gõ tiếp:**

```c
/* ========== DISPLAY FUNCTIONS ========== */

/**
 * @brief Display single book information
 * @param book Pointer to book
 */
void display_book(const Book *book);

/**
 * @brief Display all books in library
 * @param lib Pointer to library
 */
void display_all_books(Library *lib);
```

---

## Bước 6: Khai báo Helper Functions

**Gõ tiếp:**

```c
/* ========== HELPER FUNCTIONS ========== */

/**
 * @brief Get total number of books
 * @param lib Pointer to library
 * @return Number of books
 */
int get_book_count(Library *lib);
```

---

## Bước 7: Đóng header guard

**Gõ tiếp:**

```c
#endif /* BOOK_H */
```

---

## ✅ File `book.h` Hoàn Chỉnh

```c
/**
 * @file book.h
 * @brief Book management functions
 * @author Minh Tri
 * @date 2026-01-20
 */

#ifndef BOOK_H
#define BOOK_H

#include "common.h"
#include "utils.h"

/* ========== CRUD OPERATIONS ========== */

ErrorCode add_book(Library *lib, Book book);
Book* find_book_by_id(Library *lib, int id);
int find_book_index_by_id(Library *lib, int id);
ErrorCode update_book(Library *lib, int id, Book new_book);
ErrorCode delete_book(Library *lib, int id);

/* ========== SEARCH FUNCTIONS ========== */

void search_books_by_title(Library *lib, const char *title);
void search_books_by_author(Library *lib, const char *author);

/* ========== DISPLAY FUNCTIONS ========== */

void display_book(const Book *book);
void display_all_books(Library *lib);

/* ========== HELPER FUNCTIONS ========== */

int get_book_count(Library *lib);

#endif /* BOOK_H */
```

---

# PHẦN 2: Implement File `book.c`

## Bước 1: Tạo file và include header

**Tạo file:** `src/book.c`

**Gõ vào:**

```c
/**
 * @file book.c
 * @brief Implementation of book management functions
 * @author Minh Tri
 * @date 2026-01-20
 */

#include "book.h"
```

---

## Bước 2: Implement Helper Functions

### **Hàm 1: `get_book_count()`**

**Gõ tiếp:**

```c
/* ========== HELPER FUNCTIONS ========== */

/**
 * @brief Get total number of books in library
 */
int get_book_count(Library *lib) {
    // Kiểm tra library pointer
    if (lib == NULL) {
        return 0;
    }
    
    // Return số lượng sách
    return lib->book_count;
}
```

**Giải thích:**
- Kiểm tra `lib != NULL` để tránh lỗi
- Return `book_count` - số sách hiện có

**Test:**
```c
Library lib = {0};
printf("Số sách: %d\n", get_book_count(&lib));  // 0
```

---

### **Hàm 2: `find_book_index_by_id()`**

**Gõ tiếp:**

```c
/**
 * @brief Find book index by ID (helper function)
 */
int find_book_index_by_id(Library *lib, int id) {
    // Bước 1: Validate library pointer
    if (lib == NULL) {
        return -1;
    }
    
    // Bước 2: Validate ID
    if (!validate_id(id)) {
        return -1;
    }
    
    // Bước 3: Tìm kiếm trong mảng books
    for (int i = 0; i < lib->book_count; i++) {
        if (lib->books[i].id == id) {
            return i;  // Tìm thấy, return index
        }
    }
    
    // Bước 4: Không tìm thấy
    return -1;
}
```

**Giải thích từng bước:**

**Bước 1:** Validate library
```c
if (lib == NULL) {
    return -1;
}
```
- Tránh segmentation fault

**Bước 2:** Validate ID
```c
if (!validate_id(id)) {
    return -1;
}
```
- ID phải > 0

**Bước 3:** Tìm kiếm
```c
for (int i = 0; i < lib->book_count; i++) {
    if (lib->books[i].id == id) {
        return i;
    }
}
```
- Duyệt mảng `books`
- So sánh `id`
- Return index nếu tìm thấy

---

## Bước 3: Implement Display Functions

### **Hàm 3: `display_book()`**

**Gõ tiếp:**

```c
/* ========== DISPLAY FUNCTIONS ========== */

/**
 * @brief Display single book information with formatted output
 */
void display_book(const Book *book) {
    // Kiểm tra NULL pointer
    if (book == NULL) {
        print_error(ERROR_NULL_POINTER);
        return;
    }
    
    // Hiển thị thông tin sách với format đẹp
    printf("┌─────────────────────────────────────────┐\n");
    printf("│ ID: %-3d                                │\n", book->id);
    printf("│ Title: %-32s │\n", book->title);
    printf("│ Author: %-31s │\n", book->author);
    printf("│ Status: %-31s │\n", 
           book->is_borrowed ? "Borrowed" : "Available");
    printf("└─────────────────────────────────────────┘\n");
}
```

**Giải thích:**
- Dùng box drawing characters (┌─┐│└┘)
- `%-3d` - Căn trái, rộng 3 ký tự
- `%-32s` - Căn trái, rộng 32 ký tự
- Ternary operator: `is_borrowed ? "Borrowed" : "Available"`

---

### **Hàm 4: `display_all_books()`**

**Gõ tiếp:**

```c
/**
 * @brief Display all books in library
 */
void display_all_books(Library *lib) {
    // Bước 1: Validate library pointer
    if (lib == NULL) {
        print_error(ERROR_NULL_POINTER);
        return;
    }
    
    // Bước 2: Kiểm tra thư viện rỗng
    if (lib->book_count == 0) {
        printf("\n📚 Library is empty!\n\n");
        return;
    }
    
    // Bước 3: Hiển thị header
    printf("\n📚 LIBRARY BOOKS (Total: %d)\n", lib->book_count);
    printf("═══════════════════════════════════════════════\n\n");
    
    // Bước 4: Hiển thị từng sách
    for (int i = 0; i < lib->book_count; i++) {
        display_book(&lib->books[i]);
        printf("\n");
    }
}
```

---

## Bước 4: Implement CRUD Operations

### **Hàm 5: `find_book_by_id()`**

**Gõ tiếp:**

```c
/* ========== CRUD OPERATIONS ========== */

/**
 * @brief Find book by ID
 * @return Pointer to book if found, NULL otherwise
 */
Book* find_book_by_id(Library *lib, int id) {
    // Bước 1: Validate library pointer
    if (lib == NULL) {
        return NULL;
    }
    
    // Bước 2: Validate ID
    if (!validate_id(id)) {
        return NULL;
    }
    
    // Bước 3: Tìm kiếm sách
    for (int i = 0; i < lib->book_count; i++) {
        if (lib->books[i].id == id) {
            return &lib->books[i];  // Return pointer
        }
    }
    
    // Bước 4: Không tìm thấy
    return NULL;
}
```

**Giải thích:**
- Return `Book*` (con trỏ đến sách)
- `&lib->books[i]` - Địa chỉ của sách trong mảng
- Khác với `find_book_index_by_id()` return index

---

### **Hàm 6: `add_book()` - Hàm phức tạp nhất**

**Gõ tiếp:**

```c
/**
 * @brief Add a new book to the library
 * Validates all inputs and checks for duplicates
 */
ErrorCode add_book(Library *lib, Book book) {
    // Bước 1: Validate library pointer
    if (lib == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    // Bước 2: Validate book ID
    if (!validate_id(book.id)) {
        return ERROR_INVALID_INPUT;
    }
    
    // Bước 3: Validate book title
    if (!validate_string(book.title)) {
        return ERROR_INVALID_INPUT;
    }
    
    if (!validate_string_length(book.title, MAX_TITLE_LENGTH)) {
        return ERROR_INVALID_INPUT;
    }
    
    // Bước 4: Validate book author
    if (!validate_string(book.author)) {
        return ERROR_INVALID_INPUT;
    }
    
    if (!validate_string_length(book.author, MAX_AUTHOR_LENGTH)) {
        return ERROR_INVALID_INPUT;
    }
    
    // Bước 5: Kiểm tra thư viện đầy
    if (lib->book_count >= MAX_BOOKS) {
        return ERROR_FULL;
    }
    
    // Bước 6: Kiểm tra ID đã tồn tại
    if (find_book_by_id(lib, book.id) != NULL) {
        return ERROR_ALREADY_EXISTS;
    }
    
    // Bước 7: Thêm sách vào thư viện
    lib->books[lib->book_count] = book;
    lib->book_count++;
    
    return SUCCESS;
}
```

**Giải thích từng bước:**

**Bước 1-2:** Validate cơ bản
```c
if (lib == NULL) return ERROR_NULL_POINTER;
if (!validate_id(book.id)) return ERROR_INVALID_INPUT;
```

**Bước 3:** Validate title
```c
if (!validate_string(book.title)) return ERROR_INVALID_INPUT;
if (!validate_string_length(book.title, MAX_TITLE_LENGTH)) return ERROR_INVALID_INPUT;
```
- Không rỗng
- Không quá dài

**Bước 5:** Kiểm tra đầy
```c
if (lib->book_count >= MAX_BOOKS) return ERROR_FULL;
```

**Bước 6:** Kiểm tra trùng
```c
if (find_book_by_id(lib, book.id) != NULL) return ERROR_ALREADY_EXISTS;
```

**Bước 7:** Thêm sách
```c
lib->books[lib->book_count] = book;
lib->book_count++;
```

---

### **Hàm 7: `update_book()`**

**Gõ tiếp:**

```c
/**
 * @brief Update book information
 * Keeps ID and borrowed status unchanged
 */
ErrorCode update_book(Library *lib, int id, Book new_book) {
    // Bước 1: Tìm sách theo ID
    Book *book = find_book_by_id(lib, id);
    if (book == NULL) {
        return ERROR_NOT_FOUND;
    }
    
    // Bước 2: Validate new book title
    if (!validate_string(new_book.title) || 
        !validate_string_length(new_book.title, MAX_TITLE_LENGTH)) {
        return ERROR_INVALID_INPUT;
    }
    
    // Bước 3: Validate new book author
    if (!validate_string(new_book.author) || 
        !validate_string_length(new_book.author, MAX_AUTHOR_LENGTH)) {
        return ERROR_INVALID_INPUT;
    }
    
    // Bước 4: Cập nhật thông tin (giữ nguyên ID và is_borrowed)
    safe_string_copy(book->title, new_book.title, MAX_TITLE_LENGTH);
    safe_string_copy(book->author, new_book.author, MAX_AUTHOR_LENGTH);
    
    return SUCCESS;
}
```

**Lưu ý:**
- Không thay đổi `id`
- Không thay đổi `is_borrowed`
- Chỉ update `title` và `author`

---

### **Hàm 8: `delete_book()` - Hàm khó nhất**

**Gõ tiếp:**

```c
/**
 * @brief Delete book from library
 * Cannot delete borrowed books, shifts remaining books
 */
ErrorCode delete_book(Library *lib, int id) {
    // Bước 1: Tìm index của sách
    int index = find_book_index_by_id(lib, id);
    if (index == -1) {
        return ERROR_NOT_FOUND;
    }
    
    // Bước 2: Kiểm tra sách có đang được mượn không
    if (lib->books[index].is_borrowed) {
        return ERROR_BOOK_BORROWED;
    }
    
    // Bước 3: Dịch các sách phía sau lên
    for (int i = index; i < lib->book_count - 1; i++) {
        lib->books[i] = lib->books[i + 1];
    }
    
    // Bước 4: Giảm book_count
    lib->book_count--;
    
    return SUCCESS;
}
```

**Giải thích Bước 3 - Shift array:**

```
Before delete (index = 1):
[Book0][Book1][Book2][Book3]
        ↑ Xóa sách này

Shift process:
i=1: books[1] = books[2]  → [Book0][Book2][Book2][Book3]
i=2: books[2] = books[3]  → [Book0][Book2][Book3][Book3]

After (book_count = 3):
[Book0][Book2][Book3]
```

---

## Bước 5: Implement Search Functions

### **Hàm 9: `search_books_by_title()`**

**Gõ tiếp:**

```c
/* ========== SEARCH FUNCTIONS ========== */

/**
 * @brief Search books by title (partial match, case-sensitive)
 * Uses strstr() for substring matching
 */
void search_books_by_title(Library *lib, const char *title) {
    // Bước 1: Validate inputs
    if (lib == NULL || !validate_string(title)) {
        print_error(ERROR_INVALID_INPUT);
        return;
    }
    
    int found_count = 0;
    
    // Bước 2: Hiển thị header
    printf("\n🔍 Searching for title: \"%s\"\n", title);
    printf("═══════════════════════════════════════════════\n\n");
    
    // Bước 3: Tìm kiếm trong tất cả sách
    for (int i = 0; i < lib->book_count; i++) {
        // Sử dụng strstr() để tìm chuỗi con (partial match)
        if (strstr(lib->books[i].title, title) != NULL) {
            display_book(&lib->books[i]);
            printf("\n");
            found_count++;
        }
    }
    
    // Bước 4: Hiển thị kết quả
    if (found_count == 0) {
        printf("No books found with title containing \"%s\"\n", title);
    } else {
        printf("Found %d book(s)\n", found_count);
    }
}
```

**Giải thích `strstr()`:**
```c
strstr(haystack, needle)
```
- `haystack` - Chuỗi cần tìm trong đó
- `needle` - Chuỗi cần tìm
- Return: Con trỏ nếu tìm thấy, NULL nếu không

**Ví dụ:**
```c
strstr("C Programming", "Pro")  → Tìm thấy
strstr("C Programming", "Java") → NULL
```

---

### **Hàm 10: `search_books_by_author()`**

**Gõ tiếp:**

```c
/**
 * @brief Search books by author (partial match, case-sensitive)
 * Uses strstr() for substring matching
 */
void search_books_by_author(Library *lib, const char *author) {
    // Validate inputs
    if (lib == NULL || !validate_string(author)) {
        print_error(ERROR_INVALID_INPUT);
        return;
    }
    
    int found_count = 0;
    
    printf("\n🔍 Searching for author: \"%s\"\n", author);
    printf("═══════════════════════════════════════════════\n\n");
    
    // Tìm kiếm
    for (int i = 0; i < lib->book_count; i++) {
        if (strstr(lib->books[i].author, author) != NULL) {
            display_book(&lib->books[i]);
            printf("\n");
            found_count++;
        }
    }
    
    // Hiển thị kết quả
    if (found_count == 0) {
        printf("No books found by author \"%s\"\n", author);
    } else {
        printf("Found %d book(s)\n", found_count);
    }
}
```

---

## ✅ File `book.c` Hoàn Chỉnh

Xem file đầy đủ tại: `src/book.c` (280 dòng)

---

## 📝 FAQ - Câu Hỏi Thường Gặp

### **Q1: Tại sao `find_book_by_id()` return `Book*` thay vì `Book`?**

**A:** Return con trỏ để:
- Tiết kiệm bộ nhớ (không copy struct)
- Có thể sửa trực tiếp sách gốc
- Return NULL khi không tìm thấy

### **Q2: Tại sao cần `find_book_index_by_id()` khi đã có `find_book_by_id()`?**

**A:** Vì:
- `delete_book()` cần index để shift array
- Tách riêng logic tìm index và tìm pointer

### **Q3: Tại sao không thể xóa sách đang được mượn?**

**A:** Để đảm bảo:
- Dữ liệu nhất quán
- Không mất thông tin sách đang mượn
- User phải trả sách trước khi xóa

---

## 💡 Tips & Best Practices

### **1. Luôn validate input**
```c
if (lib == NULL) return ERROR_NULL_POINTER;
if (!validate_id(id)) return ERROR_INVALID_INPUT;
```

### **2. Dùng helper functions**
```c
// Tốt hơn
int index = find_book_index_by_id(lib, id);

// Thay vì viết lại logic tìm kiếm
```

### **3. Return error codes rõ ràng**
```c
if (lib->book_count >= MAX_BOOKS) return ERROR_FULL;
if (find_book_by_id(lib, id) != NULL) return ERROR_ALREADY_EXISTS;
```

### **4. Comment đầy đủ**
```c
/**
 * @brief Mô tả ngắn gọn
 * @param param1 Mô tả tham số
 * @return Mô tả giá trị trả về
 */
```

---

## ✅ Checklist Hoàn Thành

- [ ] Tạo file `include/book.h`
- [ ] Tạo file `src/book.c`
- [ ] Implement 10 hàm:
  - [ ] `get_book_count()`
  - [ ] `find_book_index_by_id()`
  - [ ] `display_book()`
  - [ ] `display_all_books()`
  - [ ] `find_book_by_id()`
  - [ ] `add_book()`
  - [ ] `update_book()`
  - [ ] `delete_book()`
  - [ ] `search_books_by_title()`
  - [ ] `search_books_by_author()`
- [ ] Compile: `gcc -Wall -Wextra -Werror -std=c11 -I./include -c src/book.c -o obj/book.o`
- [ ] Test từng hàm
- [ ] Commit và push lên GitHub

Chúc bạn code thành công! 🚀

---

## 📄 File `book.c` Hoàn Chỉnh - Copy Toàn Bộ

> Bạn có thể copy toàn bộ code dưới đây vào file `src/book.c`

```c
/**
 * @file book.c
 * @brief Implementation of book management functions
 * @author Minh Tri
 * @date 2026-01-20
 */

#include "book.h"

/* ========== HELPER FUNCTIONS ========== */

/**
 * @brief Get total number of books in library
 */
int get_book_count(Library *lib) {
    if (lib == NULL) {
        return 0;
    }
    return lib->book_count;
}

/**
 * @brief Find book index by ID (helper function)
 */
int find_book_index_by_id(Library *lib, int id) {
    if (lib == NULL) {
        return -1;
    }
    
    if (!validate_id(id)) {
        return -1;
    }
    
    for (int i = 0; i < lib->book_count; i++) {
        if (lib->books[i].id == id) {
            return i;
        }
    }
    
    return -1;
}

/* ========== DISPLAY FUNCTIONS ========== */

/**
 * @brief Display single book information with formatted output
 */
void display_book(const Book *book) {
    if (book == NULL) {
        print_error(ERROR_NULL_POINTER);
        return;
    }
    
    printf("┌─────────────────────────────────────────┐\n");
    printf("│ ID: %-3d                                │\n", book->id);
    printf("│ Title: %-32s │\n", book->title);
    printf("│ Author: %-31s │\n", book->author);
    printf("│ Status: %-31s │\n", 
           book->is_borrowed ? "Borrowed" : "Available");
    printf("└─────────────────────────────────────────┘\n");
}

/**
 * @brief Display all books in library
 */
void display_all_books(Library *lib) {
    if (lib == NULL) {
        print_error(ERROR_NULL_POINTER);
        return;
    }
    
    if (lib->book_count == 0) {
        printf("\n📚 Library is empty!\n\n");
        return;
    }
    
    printf("\n📚 LIBRARY BOOKS (Total: %d)\n", lib->book_count);
    printf("═══════════════════════════════════════════════\n\n");
    
    for (int i = 0; i < lib->book_count; i++) {
        display_book(&lib->books[i]);
        printf("\n");
    }
}

/* ========== CRUD OPERATIONS ========== */

/**
 * @brief Find book by ID
 * @return Pointer to book if found, NULL otherwise
 */
Book* find_book_by_id(Library *lib, int id) {
    if (lib == NULL) {
        return NULL;
    }
    
    if (!validate_id(id)) {
        return NULL;
    }
    
    for (int i = 0; i < lib->book_count; i++) {
        if (lib->books[i].id == id) {
            return &lib->books[i];
        }
    }
    
    return NULL;
}

/**
 * @brief Add a new book to the library
 * Validates all inputs and checks for duplicates
 */
ErrorCode add_book(Library *lib, Book book) {
    if (lib == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    if (!validate_id(book.id)) {
        return ERROR_INVALID_INPUT;
    }
    
    if (!validate_string(book.title) || 
        !validate_string_length(book.title, MAX_TITLE_LENGTH)) {
        return ERROR_INVALID_INPUT;
    }
    
    if (!validate_string(book.author) || 
        !validate_string_length(book.author, MAX_AUTHOR_LENGTH)) {
        return ERROR_INVALID_INPUT;
    }
    
    if (lib->book_count >= MAX_BOOKS) {
        return ERROR_FULL;
    }
    
    if (find_book_by_id(lib, book.id) != NULL) {
        return ERROR_ALREADY_EXISTS;
    }
    
    lib->books[lib->book_count] = book;
    lib->book_count++;
    
    return SUCCESS;
}

/**
 * @brief Update book information
 * Keeps ID and borrowed status unchanged
 */
ErrorCode update_book(Library *lib, int id, Book new_book) {
    Book *book = find_book_by_id(lib, id);
    if (book == NULL) {
        return ERROR_NOT_FOUND;
    }
    
    if (!validate_string(new_book.title) || 
        !validate_string_length(new_book.title, MAX_TITLE_LENGTH)) {
        return ERROR_INVALID_INPUT;
    }
    
    if (!validate_string(new_book.author) || 
        !validate_string_length(new_book.author, MAX_AUTHOR_LENGTH)) {
        return ERROR_INVALID_INPUT;
    }
    
    safe_string_copy(book->title, new_book.title, MAX_TITLE_LENGTH);
    safe_string_copy(book->author, new_book.author, MAX_AUTHOR_LENGTH);
    
    return SUCCESS;
}

/**
 * @brief Delete book from library
 * Cannot delete borrowed books, shifts remaining books
 */
ErrorCode delete_book(Library *lib, int id) {
    int index = find_book_index_by_id(lib, id);
    if (index == -1) {
        return ERROR_NOT_FOUND;
    }
    
    if (lib->books[index].is_borrowed) {
        return ERROR_BOOK_BORROWED;
    }
    
    for (int i = index; i < lib->book_count - 1; i++) {
        lib->books[i] = lib->books[i + 1];
    }
    
    lib->book_count--;
    
    return SUCCESS;
}

/* ========== SEARCH FUNCTIONS ========== */

/**
 * @brief Search books by title (partial match, case-sensitive)
 * Uses strstr() for substring matching
 */
void search_books_by_title(Library *lib, const char *title) {
    if (lib == NULL || !validate_string(title)) {
        print_error(ERROR_INVALID_INPUT);
        return;
    }
    
    int found_count = 0;
    
    printf("\n🔍 Searching for title: \"%s\"\n", title);
    printf("═══════════════════════════════════════════════\n\n");
    
    for (int i = 0; i < lib->book_count; i++) {
        if (strstr(lib->books[i].title, title) != NULL) {
            display_book(&lib->books[i]);
            printf("\n");
            found_count++;
        }
    }
    
    if (found_count == 0) {
        printf("No books found with title containing \"%s\"\n", title);
    } else {
        printf("Found %d book(s)\n", found_count);
    }
}

/**
 * @brief Search books by author (partial match, case-sensitive)
 * Uses strstr() for substring matching
 */
void search_books_by_author(Library *lib, const char *author) {
    if (lib == NULL || !validate_string(author)) {
        print_error(ERROR_INVALID_INPUT);
        return;
    }
    
    int found_count = 0;
    
    printf("\n🔍 Searching for author: \"%s\"\n", author);
    printf("═══════════════════════════════════════════════\n\n");
    
    for (int i = 0; i < lib->book_count; i++) {
        if (strstr(lib->books[i].author, author) != NULL) {
            display_book(&lib->books[i]);
            printf("\n");
            found_count++;
        }
    }
    
    if (found_count == 0) {
        printf("No books found by author \"%s\"\n", author);
    } else {
        printf("Found %d book(s)\n", found_count);
    }
}
```

---

## 🎯 Cách Sử Dụng File Hoàn Chỉnh:

### **Option 1: Copy toàn bộ**
1. Mở file `src/book.c`
2. Xóa toàn bộ nội dung cũ
3. Copy toàn bộ code trên
4. Save file

### **Option 2: Viết từng hàm**
1. Đọc hướng dẫn từng hàm ở trên
2. Viết code theo từng bước
3. Test từng hàm

---

## ✅ Compile và Test

```bash
# Compile
gcc -Wall -Wextra -Werror -std=c11 -I./include -c src/book.c -o obj/book.o

# Nếu thành công
echo "✅ Module Book hoàn thành!"
```

---

**Tổng số dòng:** 280 dòng  
**Tổng số hàm:** 10 hàm  
**Compile:** ✅ Thành công

