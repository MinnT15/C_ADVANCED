# Hướng Dẫn Xây Dựng Module Utils - Đầy Đủ

## Mục Đích Tài Liệu

Hướng dẫn chi tiết cách xây dựng module **Utils** (Utilities) từ đầu, bao gồm cả file `.h` và `.c`, giải thích từng dòng code.

---

## Module Utils Là Gì?

### **Định Nghĩa**

**Module Utils** (Utilities) là module chứa các **hàm tiện ích dùng chung** cho toàn bộ dự án.

### **Tại Sao Cần Module Utils?**

**Vấn đề:**
- Nhiều module cần validation (kiểm tra input)
- Nhiều nơi cần nhập dữ liệu từ user
- Nhiều nơi cần xử lý chuỗi
- Nhiều nơi cần hiển thị lỗi

**Giải pháp:**
- Tạo module Utils chứa các hàm dùng chung
- Tránh code trùng lặp
- Dễ maintain (sửa 1 chỗ, tất cả đều được cập nhật)

### **Module Utils Dùng Để Làm Gì?**

| Chức Năng | Ví Dụ |
|-----------|-------|
| **Validation** | Kiểm tra ID > 0, chuỗi không rỗng |
| **Input** | Nhập số nguyên, nhập chuỗi an toàn |
| **String Utilities** | Trim khoảng trắng, copy chuỗi an toàn |
| **Error Handling** | Hiển thị thông báo lỗi |

### **Ví Dụ Thực Tế**

**Không có Utils module:**
```c
// Trong book.c
int add_book(...) {
    if (id <= 0) {
        printf("Lỗi: ID không hợp lệ\n");
        return -1;
    }
    // ...
}

// Trong user.c
int add_user(...) {
    if (id <= 0) {  // Code trùng lặp!
        printf("Lỗi: ID không hợp lệ\n");
        return -1;
    }
    // ...
}
```

**Có Utils module:**
```c
// Trong book.c
int add_book(...) {
    if (!validate_id(id)) {
        print_error(ERROR_INVALID_INPUT);
        return ERROR_INVALID_INPUT;
    }
    // ...
}

// Trong user.c
int add_user(...) {
    if (!validate_id(id)) {  // Dùng chung hàm!
        print_error(ERROR_INVALID_INPUT);
        return ERROR_INVALID_INPUT;
    }
    // ...
}
```

---

## Cấu Trúc Module Utils

Module Utils gồm 2 file:

```
include/utils.h    - Khai báo hàm (header)
src/utils.c        - Implementation (code thực tế)
```

**Workflow:**
```
utils.h (khai báo) → utils.c (implement) → Các module khác dùng
```

---

## Phần 1: Viết File `utils.h`

### **Bước 1: Tạo File**

```bash
touch include/utils.h
```

### **Bước 2: Mở File**

```bash
nano include/utils.h
# Hoặc
code include/utils.h
```

---

### **Bước 3: Header Guards** (Dòng 1-3)

**Gõ vào file:**

```c
#ifndef UTILS_H
#define UTILS_H
```

**Giải thích:**
- Tránh include file nhiều lần
- Tương tự như `common.h`

---

### **Bước 4: Include common.h** (Dòng 5)

**Gõ tiếp:**

```c

#include "common.h"
```

**Giải thích:**
- `utils.h` cần dùng các định nghĩa trong `common.h`
- VD: `bool`, `ErrorCode`

---

### **Bước 5: Comment Phân Cách** (Dòng 7-8)

**Gõ tiếp:**

```c

/* ========== VALIDATION FUNCTIONS ========== */
```

**Giải thích:**
- Giúp dễ đọc, phân chia các nhóm hàm

---

### **Bước 6: Khai Báo Validation Functions** (Dòng 10-20)

**Gõ tiếp:**

```c

/**
 * @brief Validate if ID is valid (must be > 0)
 * @param id The ID to validate
 * @return true if valid, false otherwise
 */
bool validate_id(int id);

bool validate_string(const char *str);
bool validate_string_length(const char *str, int max_len);
```

**Giải thích:**

#### **Documentation Comment**
```c
/**
 * @brief Mô tả ngắn gọn
 * @param tên_tham_số Mô tả tham số
 * @return Mô tả giá trị trả về
 */
```
- Giúp người đọc hiểu hàm làm gì
- Công cụ như Doxygen có thể tạo documentation tự động

#### **Khai báo hàm**
```c
bool validate_id(int id);
```
- `bool` - Kiểu trả về (true/false)
- `validate_id` - Tên hàm
- `int id` - Tham số
- `;` - Kết thúc khai báo (không có body)

---

### **Bước 7: Khai Báo Input Functions** (Dòng 22-30)

**Gõ tiếp:**

```c

/* ========== INPUT FUNCTIONS ========== */

void clear_input_buffer(void);
int get_integer_input(const char *prompt);
void get_string_input(const char *prompt, char *buffer, int max_len);
```

**Giải thích:**

| Hàm | Return Type | Mục Đích |
|-----|-------------|----------|
| `clear_input_buffer()` | `void` | Xóa buffer, không return gì |
| `get_integer_input()` | `int` | Return số đã nhập |
| `get_string_input()` | `void` | Lưu vào buffer, không return |

---

### **Bước 8: Khai Báo String Utilities** (Dòng 32-38)

**Gõ tiếp:**

```c

/* ========== STRING UTILITIES ========== */

void trim_string(char *str);
void safe_string_copy(char *dest, const char *src, size_t dest_size);
```

**Giải thích:**

#### **`trim_string(char *str)`**
- `char *str` - Con trỏ đến chuỗi
- Sửa chuỗi trực tiếp (in-place)
- Không return gì

#### **`safe_string_copy()`**
- `char *dest` - Destination (đích)
- `const char *src` - Source (nguồn)
- `const` - Không sửa src
- `size_t dest_size` - Kích thước buffer đích

---

### **Bước 9: Khai Báo Error Handling** (Dòng 40-45)

**Gõ tiếp:**

```c

/* ========== ERROR HANDLING ========== */

const char* get_error_message(ErrorCode error);
void print_error(ErrorCode error);
```

**Giải thích:**

#### **`const char*`**
- Return con trỏ đến chuỗi
- `const` - Không được sửa chuỗi trả về

---

### **Bước 10: Đóng Header Guard** (Dòng 47)

**Gõ tiếp:**

```c

#endif /* UTILS_H */
```

---

### **✅ File `utils.h` Hoàn Chỉnh**

```c
#ifndef UTILS_H
#define UTILS_H

#include "common.h"

/* ========== VALIDATION FUNCTIONS ========== */

bool validate_id(int id);
bool validate_string(const char *str);
bool validate_string_length(const char *str, int max_len);

/* ========== INPUT FUNCTIONS ========== */

void clear_input_buffer(void);
int get_integer_input(const char *prompt);
void get_string_input(const char *prompt, char *buffer, int max_len);

/* ========== STRING UTILITIES ========== */

void trim_string(char *str);
void safe_string_copy(char *dest, const char *src, size_t dest_size);

/* ========== ERROR HANDLING ========== */

const char* get_error_message(ErrorCode error);
void print_error(ErrorCode error);

#endif /* UTILS_H */
```

**Tổng số dòng:** ~28 dòng

---

## Phần 2: Viết File `utils.c`

### **Bước 1: Tạo File**

```bash
touch src/utils.c
```

### **Bước 2: Mở File**

```bash
nano src/utils.c
```

---

### **Bước 3: Header Comment và Include** (Dòng 1-8)

**Gõ vào file:**

```c
/**
 * @file utils.c
 * @brief Implementation of utility functions
 * @author Your Name
 * @date 2026-01-18
 */

#include "utils.h"
```

---

### **Bước 4: Implement `validate_id()`** (Dòng 10-17)

**Gõ tiếp:**

```c

/* ========== VALIDATION FUNCTIONS ========== */

/**
 * @brief Validate if ID is valid (must be > 0)
 */
bool validate_id(int id) {
    return id > 0;
}
```

---

#### **📌 Chức Năng**

Kiểm tra xem ID có hợp lệ hay không. ID hợp lệ phải là số nguyên dương (> 0).

**Tại sao cần hàm này?**
- Trong hệ thống, ID được dùng để định danh duy nhất cho sách và người dùng
- ID = 0 hoặc âm không có ý nghĩa trong thực tế
- Tránh lỗi logic khi thêm/tìm kiếm sách/user

**Khi nào dùng?**
- Khi thêm sách mới: kiểm tra ID sách hợp lệ
- Khi thêm user mới: kiểm tra ID user hợp lệ
- Khi tìm kiếm: kiểm tra ID cần tìm hợp lệ

---

#### **⚙️ Nguyên Lý Hoạt Động**

```c
bool validate_id(int id) {
    return id > 0;
}
```

**Cách hoạt động:**

1. **Nhận tham số:** `int id` - ID cần kiểm tra
2. **So sánh:** `id > 0`
   - Nếu `id > 0` → biểu thức trả về `true` (1)
   - Nếu `id <= 0` → biểu thức trả về `false` (0)
3. **Return:** Trả về kết quả so sánh

**Phân tích chi tiết:**

| Input | So sánh `id > 0` | Return |
|-------|------------------|--------|
| `5` | `5 > 0` → true | `true` |
| `1` | `1 > 0` → true | `true` |
| `0` | `0 > 0` → false | `false` |
| `-1` | `-1 > 0` → false | `false` |
| `-100` | `-100 > 0` → false | `false` |

**Tại sao dùng `> 0` thay vì `>= 1`?**
- Cả hai đều đúng về logic
- `> 0` rõ ràng hơn: "lớn hơn 0"
- `>= 1` cũng OK: "lớn hơn hoặc bằng 1"

**Ví dụ sử dụng thực tế:**

```c
// Trong hàm add_book()
int add_book(Library *lib, Book book) {
    // Kiểm tra ID hợp lệ
    if (!validate_id(book.id)) {
        print_error(ERROR_INVALID_INPUT);
        return ERROR_INVALID_INPUT;
    }
    
    // Tiếp tục xử lý...
}
```

---

**Test:**
```c
validate_id(5);   // true - ID hợp lệ
validate_id(0);   // false - ID = 0 không hợp lệ
validate_id(-1);  // false - ID âm không hợp lệ
```

---

### **Bước 5: Implement `validate_string()`** (Dòng 19-40)

**Gõ tiếp:**

```c

/**
 * @brief Validate if string is not empty and not NULL
 */
bool validate_string(const char *str) {
    // Bước 1: Kiểm tra NULL
    if (str == NULL) {
        return false;
    }
    
    // Bước 2: Kiểm tra chuỗi rỗng
    if (str[0] == '\0') {
        return false;
    }
    
    // Bước 3: Kiểm tra toàn khoảng trắng
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isspace((unsigned char)str[i])) {
            return true;
        }
    }
    
    return false;
}
```

**Giải thích từng bước:**

#### **Bước 1: Kiểm tra NULL**
```c
if (str == NULL) {
    return false;
}
```
- Con trỏ NULL → không hợp lệ
- Tránh lỗi segmentation fault

#### **Bước 2: Kiểm tra chuỗi rỗng**
```c
if (str[0] == '\0') {
    return false;
}
```
- `str[0]` - Ký tự đầu tiên
- `'\0'` - Null terminator (kết thúc chuỗi)
- `str[0] == '\0'` → chuỗi "" (rỗng)

#### **Bước 3: Kiểm tra toàn khoảng trắng**
```c
for (int i = 0; str[i] != '\0'; i++) {
    if (!isspace((unsigned char)str[i])) {
        return true;
    }
}
return false;
```
- Duyệt từng ký tự
- `isspace()` - Kiểm tra khoảng trắng (space, tab, newline...)
- `!isspace()` - KHÔNG phải khoảng trắng
- Nếu tìm thấy ký tự không phải khoảng trắng → `true`
- Nếu toàn khoảng trắng → `false`

**Tại sao `(unsigned char)`?**
- `isspace()` yêu cầu `unsigned char`
- Tránh undefined behavior với ký tự âm

---

### **Bước 6: Implement `validate_string_length()`** (Dòng 42-50)

**Gõ tiếp:**

```c

/**
 * @brief Validate if string length is within limit
 */
bool validate_string_length(const char *str, int max_len) {
    if (str == NULL) {
        return false;
    }
    
    return strlen(str) <= (size_t)max_len;
}
```

---

#### **📌 Chức Năng**

Kiểm tra xem **độ dài của chuỗi** có nằm trong giới hạn cho phép hay không.

**Tại sao cần hàm này?**
- Trong hệ thống, mỗi trường dữ liệu có giới hạn độ dài:
  - Tiêu đề sách: tối đa 100 ký tự (`MAX_TITLE_LENGTH`)
  - Tên tác giả: tối đa 50 ký tự (`MAX_AUTHOR_LENGTH`)
  - Tên người dùng: tối đa 50 ký tự (`MAX_NAME_LENGTH`)
- Tránh **buffer overflow** (tràn bộ nhớ)
- Đảm bảo dữ liệu phù hợp với cấu trúc đã định nghĩa

**Khi nào dùng?**
- Khi thêm sách mới: kiểm tra tiêu đề và tác giả không quá dài
- Khi thêm user: kiểm tra tên không quá dài
- Khi sửa thông tin: kiểm tra input mới hợp lệ

---

#### **⚙️ Nguyên Lý Hoạt Động**

```c
bool validate_string_length(const char *str, int max_len) {
    if (str == NULL) {
        return false;
    }
    
    return strlen(str) <= (size_t)max_len;
}
```

**Cách hoạt động từng bước:**

1. **Kiểm tra NULL:**
   ```c
   if (str == NULL) {
       return false;
   }
   ```
   - Nếu con trỏ NULL → không hợp lệ
   - Tránh lỗi khi gọi `strlen()` với NULL pointer

2. **So sánh độ dài:**
   ```c
   return strlen(str) <= (size_t)max_len;
   ```
   - `strlen(str)` - Đếm số ký tự trong chuỗi (không tính `\0`)
   - `<= max_len` - So sánh với giới hạn
   - `(size_t)` - Cast để tránh warning (strlen trả về size_t)
   - Return `true` nếu độ dài OK, `false` nếu quá dài

**Phân tích chi tiết:**

| Chuỗi | strlen() | max_len | So sánh | Return |
|-------|----------|---------|---------|--------|
| `"Hello"` | 5 | 10 | `5 <= 10` | `true` ✅ |
| `"Hello"` | 5 | 3 | `5 <= 3` | `false` ❌ |
| `""` | 0 | 5 | `0 <= 5` | `true` ✅ |
| `"Hi"` | 2 | 2 | `2 <= 2` | `true` ✅ |
| `NULL` | - | 10 | - | `false` ❌ |

**Tại sao dùng `<=` thay vì `<`?**
- `<=` cho phép chuỗi có độ dài **đúng bằng** max_len
- VD: Nếu max_len = 50, chuỗi 50 ký tự vẫn hợp lệ
- Vì buffer có thêm 1 byte cho `\0`: `char name[50]` chứa được 49 ký tự + `\0`

---

#### **💡 Ví Dụ Sử Dụng Thực Tế**

**Trong hàm thêm sách:**
```c
int add_book(Library *lib, Book book) {
    // Kiểm tra độ dài tiêu đề
    if (!validate_string_length(book.title, MAX_TITLE_LENGTH)) {
        printf("❌ Lỗi: Tiêu đề sách quá dài (tối đa %d ký tự)\n", MAX_TITLE_LENGTH);
        return ERROR_INVALID_INPUT;
    }
    
    // Kiểm tra độ dài tác giả
    if (!validate_string_length(book.author, MAX_AUTHOR_LENGTH)) {
        printf("❌ Lỗi: Tên tác giả quá dài (tối đa %d ký tự)\n", MAX_AUTHOR_LENGTH);
        return ERROR_INVALID_INPUT;
    }
    
    // Tiếp tục xử lý...
}
```

**Trong hàm thêm user:**
```c
int add_user(Library *lib, User user) {
    // Kiểm tra độ dài tên
    if (!validate_string_length(user.name, MAX_NAME_LENGTH)) {
        printf("❌ Lỗi: Tên người dùng quá dài (tối đa %d ký tự)\n", MAX_NAME_LENGTH);
        return ERROR_INVALID_INPUT;
    }
    
    // Tiếp tục xử lý...
}
```

---

**Test:**
```c
validate_string_length("Hello", 10);   // true - 5 <= 10
validate_string_length("Hello", 3);    // false - 5 > 3
validate_string_length("", 5);         // true - 0 <= 5 (chuỗi rỗng hợp lệ)
validate_string_length("Hi", 2);       // true - 2 <= 2 (đúng bằng max)
validate_string_length(NULL, 10);      // false - NULL không hợp lệ
```

---

### **Bước 7: Implement `clear_input_buffer()`** (Dòng 52-60)

**Gõ tiếp:**

```c

/* ========== INPUT FUNCTIONS ========== */

/**
 * @brief Clear input buffer (stdin)
 */
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
```

**Giải thích:**

#### **Vòng lặp**
```c
while ((c = getchar()) != '\n' && c != EOF);
```
- `getchar()` - Đọc 1 ký tự từ stdin
- Gán vào `c`
- Tiếp tục đọc cho đến khi gặp:
  - `'\n'` - Newline (Enter)
  - `EOF` - End of file

#### **Tại sao cần?**
```c
int num;
scanf("%d", &num);  // User nhập: 123<Enter>
                    // scanf đọc 123, còn lại '\n' trong buffer
getchar();          // Đọc nhầm '\n' thay vì input mới!
```

**Giải pháp:**
```c
scanf("%d", &num);
clear_input_buffer();  // Xóa '\n'
```

---

### **Bước 8: Implement `get_integer_input()`** (Dòng 62-80)

**Gõ tiếp:**

```c

/**
 * @brief Get integer input from user with validation
 */
int get_integer_input(const char *prompt) {
    int value;
    int result;
    
    while (1) {
        printf("%s", prompt);
        result = scanf("%d", &value);
        
        if (result == 1) {
            clear_input_buffer();
            return value;
        } else {
            printf("❌ Lỗi: Vui lòng nhập số nguyên!\n");
            clear_input_buffer();
        }
    }
}
```

**Giải thích từng phần:**

#### **Vòng lặp vô hạn**
```c
while (1) {
    // Lặp cho đến khi input hợp lệ
}
```

#### **In prompt và đọc input**
```c
printf("%s", prompt);
result = scanf("%d", &value);
```
- `prompt` - Thông báo cho user (VD: "Nhập tuổi: ")
- `scanf("%d", &value)` - Đọc số nguyên
- `result` - Số lượng item đọc thành công

#### **Kiểm tra kết quả**
```c
if (result == 1) {
    clear_input_buffer();
    return value;
}
```
- `result == 1` - Đọc thành công 1 số
- Clear buffer
- Return giá trị

#### **Xử lý lỗi**
```c
else {
    printf("❌ Lỗi: Vui lòng nhập số nguyên!\n");
    clear_input_buffer();
}
```
- In thông báo lỗi
- Clear buffer
- Lặp lại (yêu cầu nhập lại)

**Test:**
```c
int age = get_integer_input("Nhập tuổi: ");
// User nhập: abc → Lỗi, nhập lại
// User nhập: 25 → OK, return 25
```

---

### **Bước 9: Implement `get_string_input()`** (Dòng 82-100)

**Gõ tiếp:**

```c

/**
 * @brief Get string input from user with validation
 */
void get_string_input(const char *prompt, char *buffer, int max_len) {
    printf("%s", prompt);
    
    if (fgets(buffer, max_len, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    
    // Xóa '\n' ở cuối
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    // Trim whitespace
    trim_string(buffer);
}
```

**Giải thích:**

#### **Đọc chuỗi bằng fgets**
```c
if (fgets(buffer, max_len, stdin) == NULL) {
    buffer[0] = '\0';
    return;
}
```
- `fgets()` - Đọc chuỗi an toàn
- Đọc tối đa `max_len - 1` ký tự
- Nếu lỗi → đặt chuỗi rỗng

**Tại sao dùng fgets thay vì scanf?**
- `scanf("%s")` dừng khi gặp khoảng trắng
- `fgets()` đọc cả dòng, kể cả khoảng trắng

#### **Xóa newline**
```c
size_t len = strlen(buffer);
if (len > 0 && buffer[len - 1] == '\n') {
    buffer[len - 1] = '\0';
}
```
- `fgets()` giữ lại `\n` ở cuối
- Tìm vị trí cuối chuỗi: `len - 1`
- Nếu là `\n` → thay bằng `\0`

#### **Trim whitespace**
```c
trim_string(buffer);
```
- Xóa khoảng trắng đầu/cuối

---

### **Bước 10: Implement `trim_string()`** (Dòng 102-130)

**Gõ tiếp:**

```c

/* ========== STRING UTILITIES ========== */

/**
 * @brief Remove leading and trailing whitespace
 */
void trim_string(char *str) {
    if (str == NULL) return;
    
    // Bước 1: Xóa trailing whitespace
    int len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        len--;
    }
    str[len] = '\0';
    
    // Bước 2: Xóa leading whitespace
    int start = 0;
    while (str[start] != '\0' && isspace((unsigned char)str[start])) {
        start++;
    }
    
    // Dịch chuỗi về đầu
    if (start > 0) {
        int i = 0;
        while (str[start] != '\0') {
            str[i++] = str[start++];
        }
        str[i] = '\0';
    }
}
```

**Giải thích:**

#### **Bước 1: Xóa trailing whitespace (khoảng trắng ở cuối)**
```c
int len = strlen(str);
while (len > 0 && isspace((unsigned char)str[len - 1])) {
    len--;
}
str[len] = '\0';
```

**Ví dụ:**
```
"Hello   " → "Hello"
 01234567     01234
```
- `len = 8`
- `str[7]` = ' ' (space) → `len--` → `len = 7`
- `str[6]` = ' ' (space) → `len--` → `len = 6`
- `str[5]` = ' ' (space) → `len--` → `len = 5`
- `str[4]` = 'o' (không phải space) → dừng
- `str[5] = '\0'` → "Hello"

#### **Bước 2: Xóa leading whitespace (khoảng trắng ở đầu)**
```c
int start = 0;
while (str[start] != '\0' && isspace((unsigned char)str[start])) {
    start++;
}
```

**Ví dụ:**
```
"   Hello"
 012345678
```
- `start = 0`, `str[0]` = ' ' → `start++` → `start = 1`
- `start = 1`, `str[1]` = ' ' → `start++` → `start = 2`
- `start = 2`, `str[2]` = ' ' → `start++` → `start = 3`
- `start = 3`, `str[3]` = 'H' → dừng

#### **Dịch chuỗi về đầu**
```c
if (start > 0) {
    int i = 0;
    while (str[start] != '\0') {
        str[i++] = str[start++];
    }
    str[i] = '\0';
}
```

**Ví dụ:**
```
Before: "   Hello"
         012345678
After:  "Hello"
         01234
```
- Copy `str[3]` → `str[0]` ('H')
- Copy `str[4]` → `str[1]` ('e')
- ...
- Đặt `\0` ở cuối

---

### **Bước 11: Implement `safe_string_copy()`** (Dòng 132-145)

**Gõ tiếp:**

```c

/**
 * @brief Safely copy string with size limit
 */
void safe_string_copy(char *dest, const char *src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return;
    }
    
    // Copy tối đa (dest_size - 1) ký tự
    strncpy(dest, src, dest_size - 1);
    
    // Đảm bảo null-terminated
    dest[dest_size - 1] = '\0';
}
```

**Giải thích:**

#### **Kiểm tra NULL và size**
```c
if (dest == NULL || src == NULL || dest_size == 0) {
    return;
}
```

#### **Copy an toàn**
```c
strncpy(dest, src, dest_size - 1);
```
- `strncpy()` - Copy tối đa `n` ký tự
- `dest_size - 1` - Để chừa chỗ cho `\0`

#### **Đảm bảo null-terminated**
```c
dest[dest_size - 1] = '\0';
```
- `strncpy()` không tự động thêm `\0` nếu src dài hơn n
- Phải tự thêm `\0`

**Ví dụ:**
```c
char dest[10];
safe_string_copy(dest, "Hello World", 10);
// Kết quả: "Hello Wor" (9 ký tự + '\0')
```

---

### **Bước 12: Implement Error Handling** (Dòng 147-200)

**Gõ tiếp:**

```c

/* ========== ERROR HANDLING ========== */

/**
 * @brief Get error message from error code
 */
const char* get_error_message(ErrorCode error) {
    switch (error) {
        case SUCCESS:
            return "Thành công";
        
        case ERROR_INVALID_INPUT:
            return "Dữ liệu đầu vào không hợp lệ";
        
        case ERROR_NOT_FOUND:
            return "Không tìm thấy";
        
        case ERROR_ALREADY_EXISTS:
            return "Đã tồn tại";
        
        case ERROR_FULL:
            return "Đã đầy";
        
        case ERROR_BOOK_BORROWED:
            return "Sách đã được mượn";
        
        case ERROR_BOOK_NOT_BORROWED:
            return "Sách chưa được mượn";
        
        case ERROR_MAX_BORROWED_REACHED:
            return "Đã mượn tối đa";
        
        case ERROR_FILE_IO:
            return "Lỗi đọc/ghi file";
        
        case ERROR_NULL_POINTER:
            return "Con trỏ NULL";
        
        default:
            return "Lỗi không xác định";
    }
}

/**
 * @brief Print formatted error message
 */
void print_error(ErrorCode error) {
    if (error == SUCCESS) {
        printf("✅ %s\n", get_error_message(error));
    } else {
        printf("❌ Lỗi: %s\n", get_error_message(error));
    }
}
```

**Giải thích:**

#### **Switch case cho error codes**
```c
switch (error) {
    case SUCCESS:
        return "Thành công";
    case ERROR_INVALID_INPUT:
        return "Dữ liệu đầu vào không hợp lệ";
    // ...
}
```
- Mỗi error code có message riêng
- Return chuỗi tương ứng

#### **Print error**
```c
if (error == SUCCESS) {
    printf("✅ %s\n", get_error_message(error));
} else {
    printf("❌ Lỗi: %s\n", get_error_message(error));
}
```
- SUCCESS → in với ✅
- Lỗi → in với ❌

---

## ✅ File Hoàn Chỉnh

### **`utils.h` - 28 dòng**
### **`utils.c` - ~200 dòng**

---

## 🧪 Test Module Utils

### **Tạo File Test**

Tạo `src/test_utils.c`:

```c
#include "utils.h"

int main() {
    printf("=== TEST VALIDATION ===\n");
    printf("validate_id(5): %s\n", validate_id(5) ? "PASS" : "FAIL");
    printf("validate_id(0): %s\n", !validate_id(0) ? "PASS" : "FAIL");
    
    printf("\n=== TEST INPUT ===\n");
    int age = get_integer_input("Nhập tuổi: ");
    printf("Bạn nhập: %d\n", age);
    
    char name[50];
    get_string_input("Nhập tên: ", name, 50);
    printf("Bạn nhập: '%s'\n", name);
    
    printf("\n=== TEST STRING ===\n");
    char str[] = "  Hello  ";
    printf("Before: '%s'\n", str);
    trim_string(str);
    printf("After: '%s'\n", str);
    
    printf("\n=== TEST ERROR ===\n");
    print_error(SUCCESS);
    print_error(ERROR_NOT_FOUND);
    
    return 0;
}
```

### **Compile và Run**

```bash
gcc -Wall -Wextra -std=c11 -I./include src/utils.c src/test_utils.c -o bin/test_utils
./bin/test_utils
```

---

## ✅ Checklist Hoàn Thành

### **File utils.h**
- [ ] Header guards
- [ ] Include common.h
- [ ] Khai báo validation functions (3 hàm)
- [ ] Khai báo input functions (3 hàm)
- [ ] Khai báo string utilities (2 hàm)
- [ ] Khai báo error handling (2 hàm)

### **File utils.c**
- [ ] Header comment và include
- [ ] Implement validate_id()
- [ ] Implement validate_string()
- [ ] Implement validate_string_length()
- [ ] Implement clear_input_buffer()
- [ ] Implement get_integer_input()
- [ ] Implement get_string_input()
- [ ] Implement trim_string()
- [ ] Implement safe_string_copy()
- [ ] Implement get_error_message()
- [ ] Implement print_error()

### **Testing**
- [ ] Tạo file test
- [ ] Compile thành công
- [ ] Test tất cả hàm
- [ ] Xóa file test
- [ ] Commit và push

---

## 📚 Tóm Tắt

### **Module Utils gồm:**
- **10 hàm** chia thành 4 nhóm
- **Validation**: Kiểm tra dữ liệu
- **Input**: Nhập dữ liệu an toàn
- **String**: Xử lý chuỗi
- **Error**: Hiển thị lỗi

### **Tại sao quan trọng?**
- Tránh code trùng lặp
- Dễ maintain
- Code sạch, professional

---

## ❓ FAQ

**Q: Tại sao cần `const char *str`?**
A: `const` báo compiler không được sửa chuỗi, tránh lỗi.

**Q: `isspace()` là gì?**
A: Hàm kiểm tra ký tự có phải khoảng trắng (space, tab, newline...) không.

**Q: Tại sao dùng `fgets` thay vì `scanf`?**
A: `fgets` an toàn hơn, đọc cả dòng, kiểm soát được độ dài.

**Q: `strncpy` vs `strcpy`?**
A: `strncpy` an toàn hơn, giới hạn số ký tự copy, tránh buffer overflow.

---

Chúc bạn code thành công! 🚀
