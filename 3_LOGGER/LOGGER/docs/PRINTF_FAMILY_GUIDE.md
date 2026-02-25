# 📚 HỌ HÀM PRINTF - HƯỚNG DẪN TOÀN DIỆN

> **Tài liệu đầy đủ về printf, fprintf, sprintf, snprintf và các biến thể va_list**

---

## 📋 MỤC LỤC

1. [Tổng quan về họ hàm printf](#1-tổng-quan)
2. [printf và vprintf](#2-printf-và-vprintf)
3. [fprintf và vfprintf](#3-fprintf-và-vfprintf)
4. [sprintf và vsprintf](#4-sprintf-và-vsprintf)
5. [snprintf và vsnprintf](#5-snprintf-và-vsnprintf)
6. [So sánh và lựa chọn](#6-so-sánh-và-lựa-chọn)
7. [Format Specifiers](#7-format-specifiers)
8. [Best Practices](#8-best-practices)
9. [Common Pitfalls](#9-common-pitfalls)
10. [Ví dụ thực tế](#10-ví-dụ-thực-tế)

---

## 1. TỔNG QUAN

### 1.1 Họ hàm printf là gì?

**Họ hàm printf** là nhóm các hàm trong C dùng để **format và xuất chuỗi** theo một định dạng cho trước.

### 1.2 Bảng tổng quan

```c
┌─────────────────────────────────────────────────────────────────┐
│                    HỌ HÀM PRINTF                                │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  Variadic (...)              va_list version                    │
│  ───────────────────────     ──────────────────────────         │
│                                                                 │
│  printf(fmt, ...)            vprintf(fmt, args)                 │
│  └─ In ra stdout             └─ In ra stdout                    │
│                                                                 │
│  fprintf(fp, fmt, ...)       vfprintf(fp, fmt, args)            │
│  └─ In ra file               └─ In ra file                      │
│                                                                 │
│  sprintf(buf, fmt, ...)      vsprintf(buf, fmt, args)           │
│  └─ In ra buffer             └─ In ra buffer                    │
│     (KHÔNG AN TOÀN!)            (KHÔNG AN TOÀN!)                │
│                                                                 │
│  snprintf(buf, n, fmt, ...)  vsnprintf(buf, n, fmt, args)       │
│  └─ In ra buffer (AN TOÀN)   └─ In ra buffer (AN TOÀN)         │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

### 1.3 Quy tắc đặt tên

```
┌─────────────────────────────────────────────────────────────────┐
│              QUY TẮC ĐẶT TÊN                                    │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  Prefix:                                                        │
│  ├─ (không có) → stdout (console)                               │
│  ├─ f → file (FILE*)                                            │
│  ├─ s → string (char*)                                          │
│  └─ sn → string with size limit                                 │
│                                                                 │
│  Prefix v:                                                      │
│  └─ v → variadic (nhận va_list thay vì ...)                     │
│                                                                 │
│  Ví dụ:                                                         │
│  ├─ printf   = print to stdout, variadic                        │
│  ├─ vprintf  = print to stdout, va_list                         │
│  ├─ fprintf  = print to file, variadic                          │
│  ├─ vfprintf = print to file, va_list                           │
│  ├─ sprintf  = print to string, variadic                        │
│  └─ snprintf = print to string with size, variadic              │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

## 2. PRINTF VÀ VPRINTF

### 2.1 printf - In ra stdout

**Prototype:**
```c
int printf(const char *format, ...);
```

**Mô tả:**
- In chuỗi đã format ra **standard output (stdout)**
- Nhận số lượng tham số thay đổi (`...`)
- Trả về số ký tự đã in (không tính `\0`)

**Ví dụ:**
```c
#include <stdio.h>

int main() {
    int x = 42;
    char *name = "Alice";
    
    // In ra stdout (console)
    printf("Hello, World!\n");
    printf("x = %d\n", x);
    printf("Name: %s, Age: %d\n", name, 25);
    
    // Lấy số ký tự đã in
    int count = printf("Test");  // count = 4
    printf("\nĐã in %d ký tự\n", count);
    
    return 0;
}
```

**Output:**
```
Hello, World!
x = 42
Name: Alice, Age: 25
Test
Đã in 4 ký tự
```

---

### 2.2 vprintf - In ra stdout (va_list)

**Prototype:**
```c
int vprintf(const char *format, va_list args);
```

**Mô tả:**
- Giống `printf` nhưng nhận **va_list** thay vì `...`
- Dùng trong **variadic functions**

**Ví dụ:**
```c
#include <stdio.h>
#include <stdarg.h>

// Wrapper function cho printf
void my_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    // Dùng vprintf với va_list
    vprintf(format, args);
    
    va_end(args);
}

int main() {
    my_printf("x = %d, y = %d\n", 10, 20);
    my_printf("Name: %s\n", "Bob");
    return 0;
}
```

**Output:**
```
x = 10, y = 20
Name: Bob
```

---

## 3. FPRINTF VÀ VFPRINTF

### 3.1 fprintf - In ra file

**Prototype:**
```c
int fprintf(FILE *stream, const char *format, ...);
```

**Mô tả:**
- In chuỗi đã format ra **file stream**
- `stream` có thể là: file, `stdout`, `stderr`
- Trả về số ký tự đã ghi

**Ví dụ:**
```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("output.txt", "w");
    if (!fp) {
        perror("fopen");
        return 1;
    }
    
    // In ra file
    fprintf(fp, "Hello, File!\n");
    fprintf(fp, "x = %d\n", 42);
    
    // fprintf cũng dùng được với stdout/stderr
    fprintf(stdout, "In ra stdout\n");
    fprintf(stderr, "In ra stderr\n");
    
    fclose(fp);
    return 0;
}
```

**File output.txt:**
```
Hello, File!
x = 42
```

---

### 3.2 vfprintf - In ra file (va_list)

**Prototype:**
```c
int vfprintf(FILE *stream, const char *format, va_list args);
```

**Mô tả:**
- Giống `fprintf` nhưng nhận **va_list**
- Dùng trong variadic functions

**Ví dụ:**
```c
#include <stdio.h>
#include <stdarg.h>

// Logger ghi vào file
void log_to_file(FILE *fp, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    // Thêm prefix
    fprintf(fp, "[LOG] ");
    
    // Dùng vfprintf với va_list
    vfprintf(fp, format, args);
    
    fprintf(fp, "\n");
    
    va_end(args);
}

int main() {
    FILE *fp = fopen("log.txt", "w");
    
    log_to_file(fp, "Application started");
    log_to_file(fp, "User %s logged in", "admin");
    log_to_file(fp, "Processing %d items", 100);
    
    fclose(fp);
    return 0;
}
```

**File log.txt:**
```
[LOG] Application started
[LOG] User admin logged in
[LOG] Processing 100 items
```

---

## 4. SPRINTF VÀ VSPRINTF

### 4.1 sprintf - In ra buffer (KHÔNG AN TOÀN!)

**Prototype:**
```c
int sprintf(char *str, const char *format, ...);
```

**Mô tả:**
- In chuỗi đã format vào **buffer**
- ⚠️ **NGUY HIỂM**: Không kiểm tra kích thước buffer → Buffer overflow!
- Trả về số ký tự đã ghi (không tính `\0`)

**Ví dụ:**
```c
#include <stdio.h>

int main() {
    char buffer[100];
    
    // In vào buffer
    sprintf(buffer, "x = %d, y = %d", 10, 20);
    printf("Buffer: %s\n", buffer);
    
    // ❌ NGUY HIỂM - Buffer overflow!
    char small[5];
    sprintf(small, "This is a very long string");  // OVERFLOW!
    
    return 0;
}
```

**⚠️ Cảnh báo:**
```c
// ❌ KHÔNG BAO GIỜ dùng sprintf với input không tin cậy
char buffer[50];
char *user_input = get_user_input();  // Có thể rất dài!
sprintf(buffer, "%s", user_input);    // BUFFER OVERFLOW!

// ✅ Dùng snprintf thay thế
snprintf(buffer, sizeof(buffer), "%s", user_input);
```

---

### 4.2 vsprintf - In ra buffer (KHÔNG AN TOÀN!)

**Prototype:**
```c
int vsprintf(char *str, const char *format, va_list args);
```

**Mô tả:**
- Giống `sprintf` nhưng nhận **va_list**
- ⚠️ **NGUY HIỂM**: Không kiểm tra kích thước buffer

**Ví dụ:**
```c
#include <stdio.h>
#include <stdarg.h>

void format_string(char *buffer, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    // ⚠️ Không an toàn!
    vsprintf(buffer, format, args);
    
    va_end(args);
}

int main() {
    char buffer[100];
    format_string(buffer, "x = %d, y = %d", 10, 20);
    printf("%s\n", buffer);
    return 0;
}
```

---

## 5. SNPRINTF VÀ VSNPRINTF

### 5.1 snprintf - In ra buffer (AN TOÀN)

**Prototype:**
```c
int snprintf(char *str, size_t size, const char *format, ...);
```

**Mô tả:**
- In chuỗi đã format vào **buffer** với **giới hạn kích thước**
- ✅ **AN TOÀN**: Không bao giờ ghi quá `size` bytes
- Luôn thêm `\0` ở cuối (nếu `size > 0`)
- Trả về số ký tự **sẽ được ghi** (không tính `\0`) nếu buffer đủ lớn

**Ví dụ:**
```c
#include <stdio.h>

int main() {
    char buffer[20];
    
    // In vào buffer an toàn
    int written = snprintf(buffer, sizeof(buffer), "x = %d, y = %d", 10, 20);
    printf("Buffer: %s\n", buffer);
    printf("Số ký tự cần: %d\n", written);
    
    // Trường hợp buffer quá nhỏ
    char small[10];
    written = snprintf(small, sizeof(small), "This is a very long string");
    printf("Buffer: %s\n", small);           // Bị cắt
    printf("Số ký tự cần: %d\n", written);   // Số ký tự thực sự cần
    
    return 0;
}
```

**Output:**
```
Buffer: x = 10, y = 20
Số ký tự cần: 14
Buffer: This is a
Số ký tự cần: 27
```

**Giải thích:**
```c
char buffer[10];
int n = snprintf(buffer, sizeof(buffer), "Hello, World!");
// buffer = "Hello, Wo\0" (9 ký tự + \0)
// n = 13 (số ký tự của "Hello, World!" nếu buffer đủ lớn)

// Kiểm tra truncation:
if (n >= sizeof(buffer)) {
    printf("Chuỗi bị cắt!\n");
}
```

---

### 5.2 vsnprintf - In ra buffer (AN TOÀN)

**Prototype:**
```c
int vsnprintf(char *str, size_t size, const char *format, va_list args);
```

**Mô tả:**
- Giống `snprintf` nhưng nhận **va_list**
- ✅ **AN TOÀN**: Giới hạn kích thước
- **CỰC KỲ QUAN TRỌNG** trong variadic functions

**Ví dụ:**
```c
#include <stdio.h>
#include <stdarg.h>

// Logger an toàn
void safe_log(const char *format, ...) {
    char buffer[256];
    
    va_list args;
    va_start(args, format);
    
    // Dùng vsnprintf - AN TOÀN
    int written = vsnprintf(buffer, sizeof(buffer), format, args);
    
    va_end(args);
    
    // Kiểm tra truncation
    if (written >= sizeof(buffer)) {
        printf("[TRUNCATED] %s\n", buffer);
    } else {
        printf("%s\n", buffer);
    }
}

int main() {
    safe_log("User %s logged in at %d:%d", "admin", 14, 30);
    safe_log("Processing %d items", 100);
    return 0;
}
```

**Output:**
```
User admin logged in at 14:30
Processing 100 items
```

---

## 6. SO SÁNH VÀ LỰA CHỌN

### 6.1 Bảng so sánh

```c
┌─────────────────────────────────────────────────────────────────┐
│                  SO SÁNH CÁC HÀM                                │
├──────────┬──────────┬──────────┬──────────┬────────────────────┤
│ Hàm      │ Output   │ Variadic │ An toàn? │ Khi nào dùng?      │
├──────────┼──────────┼──────────┼──────────┼────────────────────┤
│ printf   │ stdout   │ ...      │ N/A      │ In ra console      │
│ vprintf  │ stdout   │ va_list  │ N/A      │ Wrapper cho printf │
├──────────┼──────────┼──────────┼──────────┼────────────────────┤
│ fprintf  │ FILE*    │ ...      │ N/A      │ In ra file         │
│ vfprintf │ FILE*    │ va_list  │ N/A      │ Wrapper cho fprintf│
├──────────┼──────────┼──────────┼──────────┼────────────────────┤
│ sprintf  │ buffer   │ ...      │ ❌ KHÔNG │ KHÔNG BAO GIỜ!     │
│ vsprintf │ buffer   │ va_list  │ ❌ KHÔNG │ KHÔNG BAO GIỜ!     │
├──────────┼──────────┼──────────┼──────────┼────────────────────┤
│ snprintf │ buffer   │ ...      │ ✅ CÓ    │ Format vào buffer  │
│ vsnprintf│ buffer   │ va_list  │ ✅ CÓ    │ Variadic + buffer  │
└──────────┴──────────┴──────────┴──────────┴────────────────────┘
```

### 6.2 Khi nào dùng hàm nào?

```c
┌─────────────────────────────────────────────────────────────────┐
│              HƯỚNG DẪN LỰA CHỌN                                 │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  📺 In ra CONSOLE:                                              │
│  ├─ Hàm thông thường → printf()                                 │
│  └─ Variadic function → vprintf()                               │
│                                                                 │
│  📄 In ra FILE:                                                 │
│  ├─ Hàm thông thường → fprintf()                                │
│  └─ Variadic function → vfprintf()                              │
│                                                                 │
│  💾 Format vào BUFFER:                                          │
│  ├─ Hàm thông thường → snprintf() (KHÔNG dùng sprintf!)         │
│  └─ Variadic function → vsnprintf() (KHÔNG dùng vsprintf!)      │
│                                                                 │
│  ⚠️ KHÔNG BAO GIỜ DÙNG:                                         │
│  ├─ sprintf() → Dùng snprintf() thay thế                        │
│  └─ vsprintf() → Dùng vsnprintf() thay thế                      │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

### 6.3 Ví dụ lựa chọn

```c
#include <stdio.h>
#include <stdarg.h>

// ✅ ĐÚNG: In ra console trong variadic function
void log_console(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);  // ← Dùng vprintf
    va_end(args);
}

// ✅ ĐÚNG: In ra file trong variadic function
void log_file(FILE *fp, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(fp, format, args);  // ← Dùng vfprintf
    va_end(args);
}

// ✅ ĐÚNG: Format vào buffer trong variadic function
void format_message(char *buffer, size_t size, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, size, format, args);  // ← Dùng vsnprintf
    va_end(args);
}

// ❌ SAI: Dùng vsprintf (không an toàn)
void bad_format(char *buffer, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);  // ← NGUY HIỂM!
    va_end(args);
}
```

---

## 7. FORMAT SPECIFIERS

### 7.1 Các format specifier cơ bản

```c
┌─────────────────────────────────────────────────────────────────┐
│              FORMAT SPECIFIERS                                  │
├──────────┬──────────────────────────────────────────────────────┤
│ Specifier│ Mô tả                                                │
├──────────┼──────────────────────────────────────────────────────┤
│ %d, %i   │ Signed decimal integer                               │
│ %u       │ Unsigned decimal integer                             │
│ %o       │ Unsigned octal                                       │
│ %x, %X   │ Unsigned hexadecimal (lowercase/uppercase)           │
│ %f       │ Decimal floating point                               │
│ %e, %E   │ Scientific notation (lowercase/uppercase)            │
│ %g, %G   │ Shortest of %f and %e                                │
│ %c       │ Character                                            │
│ %s       │ String                                               │
│ %p       │ Pointer address                                      │
│ %%       │ Literal %                                            │
├──────────┼──────────────────────────────────────────────────────┤
│ Length   │                                                      │
├──────────┼──────────────────────────────────────────────────────┤
│ %ld      │ long int                                             │
│ %lld     │ long long int                                        │
│ %zu      │ size_t                                               │
│ %zd      │ ssize_t                                              │
└──────────┴──────────────────────────────────────────────────────┘
```

### 7.2 Width và Precision

```c
#include <stdio.h>

int main() {
    // Width (độ rộng tối thiểu)
    printf("|%5d|\n", 42);        // |   42|
    printf("|%-5d|\n", 42);       // |42   | (căn trái)
    printf("|%05d|\n", 42);       // |00042| (pad với 0)
    
    // Precision cho số thực
    printf("%.2f\n", 3.14159);    // 3.14
    printf("%.5f\n", 3.14159);    // 3.14159
    
    // Precision cho chuỗi (giới hạn độ dài)
    printf("%.5s\n", "Hello, World!");  // Hello
    
    // Kết hợp width và precision
    printf("|%10.2f|\n", 3.14159);      // |      3.14|
    
    return 0;
}
```

---

## 8. BEST PRACTICES

### 8.1 Luôn dùng snprintf/vsnprintf

```c
// ❌ SAI
char buffer[100];
sprintf(buffer, "%s", user_input);

// ✅ ĐÚNG
char buffer[100];
snprintf(buffer, sizeof(buffer), "%s", user_input);
```

### 8.2 Kiểm tra truncation

```c
char buffer[50];
int n = snprintf(buffer, sizeof(buffer), "Very long string: %s", data);

if (n >= sizeof(buffer)) {
    fprintf(stderr, "Warning: String truncated\n");
}
```

### 8.3 Dùng sizeof() cho buffer size

```c
// ✅ ĐÚNG
char buffer[256];
snprintf(buffer, sizeof(buffer), "%s", str);

// ❌ SAI - Hard-code size
snprintf(buffer, 256, "%s", str);  // Nếu buffer thay đổi size?
```

### 8.4 Trong variadic functions, dùng v* versions

```c
void my_logger(const char *format, ...) {
    char buffer[512];
    va_list args;
    
    va_start(args, format);
    
    // ✅ ĐÚNG - Dùng vsnprintf
    vsnprintf(buffer, sizeof(buffer), format, args);
    
    // ❌ SAI - Không thể dùng snprintf với va_list
    // snprintf(buffer, sizeof(buffer), format, args);
    
    va_end(args);
    
    printf("%s\n", buffer);
}
```

---

## 9. COMMON PITFALLS

### 9.1 Dùng sprintf thay vì snprintf

```c
// ❌ NGUY HIỂM
char buffer[10];
sprintf(buffer, "This is a very long string");  // BUFFER OVERFLOW!

// ✅ AN TOÀN
char buffer[10];
snprintf(buffer, sizeof(buffer), "This is a very long string");
// buffer = "This is a\0"
```

### 9.2 Quên kiểm tra return value

```c
// ❌ Không kiểm tra
char buffer[50];
snprintf(buffer, sizeof(buffer), "%s", very_long_string);
// Có thể bị truncate mà không biết!

// ✅ Kiểm tra
char buffer[50];
int n = snprintf(buffer, sizeof(buffer), "%s", very_long_string);
if (n >= sizeof(buffer)) {
    fprintf(stderr, "String truncated: needed %d bytes\n", n);
}
```

### 9.3 Dùng sai hàm trong variadic function

```c
void bad_logger(const char *format, ...) {
    char buffer[256];
    va_list args;
    va_start(args, format);
    
    // ❌ SAI - snprintf không nhận va_list
    snprintf(buffer, sizeof(buffer), format, args);  // COMPILE ERROR!
    
    va_end(args);
}

void good_logger(const char *format, ...) {
    char buffer[256];
    va_list args;
    va_start(args, format);
    
    // ✅ ĐÚNG - vsnprintf nhận va_list
    vsnprintf(buffer, sizeof(buffer), format, args);
    
    va_end(args);
}
```

### 9.4 Truyền sai kiểu dữ liệu

```c
// ❌ SAI
size_t size = 1024;
printf("Size: %d\n", size);  // %d cho int, không phải size_t!

// ✅ ĐÚNG
size_t size = 1024;
printf("Size: %zu\n", size);  // %zu cho size_t
```

---

## 10. VÍ DỤ THỰC TẾ

### 10.1 Logger System hoàn chỉnh

```c
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} LogLevel;

// Logger ghi ra cả console và file
void logger(LogLevel level, const char *file, int line, const char *format, ...) {
    // Lấy timestamp
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timestamp[64];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);
    
    // Level string
    const char *level_str[] = {"INFO", "WARNING", "ERROR"};
    
    // Format message
    char message[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(message, sizeof(message), format, args);
    va_end(args);
    
    // In ra console
    printf("[%s] [%s] [%s:%d] - %s\n", 
           timestamp, level_str[level], file, line, message);
    
    // Ghi vào file
    FILE *fp = fopen("app.log", "a");
    if (fp) {
        fprintf(fp, "[%s] [%s] [%s:%d] - %s\n",
                timestamp, level_str[level], file, line, message);
        fclose(fp);
    }
}

#define log_info(...)    logger(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define log_warning(...) logger(LOG_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...)   logger(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)

int main() {
    log_info("Application started");
    log_warning("Memory usage: %d%%", 85);
    log_error("Failed to connect to %s", "database");
    return 0;
}
```

### 10.2 String Builder

```c
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

typedef struct {
    char buffer[4096];
    size_t length;
    size_t capacity;
} StringBuilder;

void sb_init(StringBuilder *sb) {
    sb->buffer[0] = '\0';
    sb->length = 0;
    sb->capacity = sizeof(sb->buffer);
}

int sb_append(StringBuilder *sb, const char *format, ...) {
    if (sb->length >= sb->capacity - 1) {
        return -1;  // Buffer full
    }
    
    va_list args;
    va_start(args, format);
    
    size_t remaining = sb->capacity - sb->length;
    int written = vsnprintf(sb->buffer + sb->length, remaining, format, args);
    
    va_end(args);
    
    if (written > 0 && written < remaining) {
        sb->length += written;
        return written;
    }
    
    return -1;  // Truncated or error
}

int main() {
    StringBuilder sb;
    sb_init(&sb);
    
    sb_append(&sb, "Name: %s\n", "Alice");
    sb_append(&sb, "Age: %d\n", 30);
    sb_append(&sb, "Score: %.2f\n", 95.5);
    
    printf("Result:\n%s", sb.buffer);
    printf("Length: %zu bytes\n", sb.length);
    
    return 0;
}
```

### 10.3 Dual Output Logger

```c
#include <stdio.h>
#include <stdarg.h>

// In ra cả console VÀ file
void log_dual(FILE *fp, const char *format, ...) {
    va_list console_args, file_args;
    
    va_start(console_args, format);
    va_copy(file_args, console_args);
    
    // In ra console
    printf("[CONSOLE] ");
    vprintf(format, console_args);
    printf("\n");
    
    // In ra file
    fprintf(fp, "[FILE] ");
    vfprintf(fp, format, file_args);
    fprintf(fp, "\n");
    
    va_end(file_args);
    va_end(console_args);
}

int main() {
    FILE *fp = fopen("output.log", "w");
    
    log_dual(fp, "User %s logged in", "admin");
    log_dual(fp, "Processing %d items", 100);
    log_dual(fp, "Success rate: %.2f%%", 98.5);
    
    fclose(fp);
    return 0;
}
```

---

## 📚 TÓM TẮT

### Checklist nhanh

```
✅ Dùng printf/vprintf cho console output
✅ Dùng fprintf/vfprintf cho file output
✅ Dùng snprintf/vsnprintf cho buffer (KHÔNG dùng sprintf/vsprintf!)
✅ Trong variadic functions, dùng v* versions (vprintf, vfprintf, vsnprintf)
✅ Luôn kiểm tra return value của snprintf/vsnprintf
✅ Dùng sizeof() cho buffer size
✅ Dùng đúng format specifier (%d, %s, %zu, etc.)
✅ Kiểm tra truncation khi dùng snprintf/vsnprintf
```

### Quy tắc vàng

```
┌─────────────────────────────────────────────────────────────────┐
│                    QUY TẮC VÀNG                                 │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  1. KHÔNG BAO GIỜ dùng sprintf/vsprintf                         │
│     → Luôn dùng snprintf/vsnprintf                              │
│                                                                 │
│  2. Trong variadic functions:                                   │
│     → Dùng vprintf, vfprintf, vsnprintf (có chữ v)              │
│                                                                 │
│  3. Luôn kiểm tra return value của snprintf/vsnprintf           │
│     → Phát hiện truncation                                      │
│                                                                 │
│  4. Dùng sizeof() cho buffer size                               │
│     → Tránh hard-code                                           │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

> 💡 **Lời khuyên:** Trong dự án Logger, bạn sẽ dùng `vsnprintf` để format message trong variadic function!
