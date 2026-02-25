# 📚 STDARG.H - HƯỚNG DẪN TOÀN DIỆN

> **Tài liệu đầy đủ về Variadic Functions (Hàm với số tham số thay đổi) trong C**

---

## 📋 MỤC LỤC

1. [Giới thiệu](#1-giới-thiệu)
2. [Các thành phần cơ bản](#2-các-thành-phần-cơ-bản)
3. [Cú pháp và quy tắc](#3-cú-pháp-và-quy-tắc)
4. [Ví dụ từ cơ bản đến nâng cao](#4-ví-dụ-từ-cơ-bản-đến-nâng-cao)
5. [Type Promotion Rules](#5-type-promotion-rules)
6. [snprintf vs vsnprintf](#6-snprintf-vs-vsnprintf)
7. [Best Practices](#7-best-practices)
8. [Common Pitfalls](#8-common-pitfalls)
9. [Advanced Techniques](#9-advanced-techniques)
10. [Real-world Applications](#10-real-world-applications)

---

## 1. GIỚI THIỆU

### 1.1 Variadic Function là gì?

**Variadic Function** = Hàm có thể nhận **số lượng tham số thay đổi**

**Ví dụ trong C Standard Library:**
```c
printf("Hello");                           // 1 tham số
printf("x = %d", 10);                     // 2 tham số
printf("x = %d, y = %d", 10, 20);        // 3 tham số
printf("a=%d, b=%d, c=%d", 1, 2, 3);     // 4 tham số
```

### 1.2 Tại sao cần Variadic Functions?

**Trước khi có stdarg.h:**
```c
void print1(int a);
void print2(int a, int b);
void print3(int a, int b, int c);
void print4(int a, int b, int c, int d);
// ... phải viết vô số hàm!
```

**Sau khi có stdarg.h:**
```c
void print(int count, ...);  // Một hàm xử lý tất cả!
```

---

## 2. CÁC THÀNH PHẦN CƠ BẢN

### 2.1 Header File

```c
#include <stdarg.h>
```

### 2.2 Các Macro/Type chính

```c
┌─────────────────────────────────────────────────────────┐
│              CÁC THÀNH PHẦN TRONG STDARG.H              │
├─────────────────────────────────────────────────────────┤
│                                                         │
│  va_list                                                │
│  ├─ Kiểu dữ liệu                                       │
│  ├─ Dùng để lưu danh sách tham số                      │
│  └─ Ví dụ: va_list args;                               │
│                                                         │
│  va_start(ap, last)                                     │
│  ├─ Macro khởi tạo                                     │
│  ├─ ap: va_list variable                               │
│  ├─ last: tham số cố định cuối cùng                    │
│  └─ Ví dụ: va_start(args, format);                     │
│                                                         │
│  va_arg(ap, type)                                       │
│  ├─ Macro lấy tham số tiếp theo                        │
│  ├─ ap: va_list variable                               │
│  ├─ type: kiểu dữ liệu của tham số                     │
│  └─ Ví dụ: int x = va_arg(args, int);                  │
│                                                         │
│  va_end(ap)                                             │
│  ├─ Macro kết thúc                                     │
│  ├─ Dọn dẹp tài nguyên                                 │
│  └─ Ví dụ: va_end(args);                               │
│                                                         │
│  va_copy(dest, src)  [C99]                              │
│  ├─ Copy va_list                                       │
│  └─ Ví dụ: va_copy(args2, args1);                      │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

### 2.3 GIẢI THÍCH CHI TIẾT TỪNG THÀNH PHẦN

#### 🔬 1️⃣ va_list - Kiểu dữ liệu

**Định nghĩa:**
```c
va_list args;
```

**va_list là gì?**

`va_list` là một **kiểu dữ liệu đặc biệt** dùng để lưu trữ thông tin về danh sách tham số thay đổi.

**Tưởng tượng:**
```
va_list giống như một "con trỏ thông minh" trỏ đến vị trí hiện tại 
trong danh sách tham số.
```

**Bên trong va_list (Implementation):**

Tùy vào compiler và platform, `va_list` có thể được implement khác nhau:

```c
// Trên x86-64 (Linux/GCC):
typedef struct {
    unsigned int gp_offset;    // Offset cho general purpose registers
    unsigned int fp_offset;    // Offset cho floating point registers
    void *overflow_arg_area;   // Con trỏ đến stack
    void *reg_save_area;       // Con trỏ đến saved registers
} va_list[1];

// Trên ARM/simple platforms:
typedef char* va_list;  // Đơn giản chỉ là con trỏ
```

**⚠️ Lưu ý quan trọng:**

Bạn **KHÔNG BAO GIỜ** truy cập trực tiếp vào `va_list`. Luôn dùng các macro để thao tác.

```c
// ❌ KHÔNG BAO GIỜ làm thế này
va_list args;
char *ptr = (char*)args;  // SAI!

// ✅ Luôn dùng macro
va_list args;
va_start(args, last_param);
int x = va_arg(args, int);
va_end(args);
```

---

#### 🔬 2️⃣ va_start(ap, last) - Khởi tạo

**Cú pháp:**
```c
va_start(ap, last);
//       ↑    ↑
//       |    └─ Tham số cố định cuối cùng
//       └─ va_list variable
```

**va_start làm gì?**

`va_start` **khởi tạo** `va_list` để trỏ đến tham số **ĐẦU TIÊN** trong danh sách `...`

**Minh họa:**
```c
void func(int a, int b, ...) {
//        ↑    ↑    ↑
//        |    |    └─ Danh sách tham số thay đổi
//        |    └─ last (tham số cố định cuối)
//        └─ Tham số cố định đầu
    
    va_list args;
    va_start(args, b);  // args giờ trỏ đến tham số đầu tiên sau 'b'
}

// Gọi: func(10, 20, 30, 40, 50);
//                   ↑
//                   args trỏ đến đây sau va_start
```

**Bên trong va_start (Conceptual):**

```c
// Đây là cách va_start hoạt động (đơn giản hóa)
#define va_start(ap, last) \
    ap = (va_list)((char*)&last + sizeof(last))
//                          ↑
//                          Lấy địa chỉ của 'last'
//                          Cộng thêm kích thước của 'last'
//                          → Trỏ đến tham số tiếp theo
```

**Sơ đồ bộ nhớ:**
```
Stack:
┌─────────────┐
│   a = 10    │ ← Tham số cố định 1
├─────────────┤
│   b = 20    │ ← Tham số cố định 2 (last)
├─────────────┤
│   30        │ ← args trỏ đến đây sau va_start(args, b)
├─────────────┤
│   40        │
├─────────────┤
│   50        │
└─────────────┘
```

**⚠️ Lưu ý:**

1. **Phải truyền đúng tham số cuối:**
```c
void func(int a, int b, int c, ...) {
    va_list args;
    
    // ✅ ĐÚNG
    va_start(args, c);
    
    // ❌ SAI
    va_start(args, a);  // Sẽ bỏ qua b và c!
}
```

2. **Tham số last phải có tên:**
```c
// ❌ SAI
void func(int, int, ...);  // Tham số không có tên

// ✅ ĐÚNG
void func(int a, int b, ...);  // Có tên
```

---

#### 🔬 3️⃣ va_arg(ap, type) - Lấy tham số

**Cú pháp:**
```c
type value = va_arg(ap, type);
//                      ↑
//                      Kiểu dữ liệu của tham số
```

**va_arg làm gì?**

`va_arg` làm **2 việc**:
1. **Lấy** giá trị tham số hiện tại
2. **Di chuyển** con trỏ đến tham số tiếp theo

**Minh họa:**
```c
void func(int count, ...) {
    va_list args;
    va_start(args, count);
    
    int x = va_arg(args, int);  // Lấy tham số 1, di chuyển đến tham số 2
    int y = va_arg(args, int);  // Lấy tham số 2, di chuyển đến tham số 3
    int z = va_arg(args, int);  // Lấy tham số 3, di chuyển đến tham số 4
    
    va_end(args);
}

// Gọi: func(3, 10, 20, 30);
// x = 10, y = 20, z = 30
```

**Bên trong va_arg (Conceptual):**

```c
// Đây là cách va_arg hoạt động (đơn giản hóa)
#define va_arg(ap, type) \
    (*(type*)((ap += sizeof(type)) - sizeof(type)))
//    ↑       ↑                      ↑
//    |       |                      └─ Quay lại vị trí cũ để lấy giá trị
//    |       └─ Di chuyển con trỏ đến tham số tiếp theo
//    └─ Cast về type* và dereference
```

**Sơ đồ hoạt động:**
```
Ban đầu:
┌─────────────┐
│   10        │ ← args trỏ đây
├─────────────┤
│   20        │
├─────────────┤
│   30        │
└─────────────┘

Sau va_arg(args, int):
┌─────────────┐
│   10        │ ← Trả về giá trị này (10)
├─────────────┤
│   20        │ ← args giờ trỏ đây
├─────────────┤
│   30        │
└─────────────┘

Sau va_arg(args, int) lần 2:
┌─────────────┐
│   10        │
├─────────────┤
│   20        │ ← Trả về giá trị này (20)
├─────────────┤
│   30        │ ← args giờ trỏ đây
└─────────────┘
```

**⚠️ Lưu ý cực kỳ quan trọng:**

1. **Phải biết chính xác kiểu dữ liệu:**
```c
// Gọi: func(2, 10, "hello");

va_list args;
va_start(args, count);

// ✅ ĐÚNG - Đúng thứ tự kiểu
int x = va_arg(args, int);      // 10
char *s = va_arg(args, char*);  // "hello"

// ❌ SAI - Sai thứ tự kiểu
char *s = va_arg(args, char*);  // Lấy 10 như là char* → CRASH!
int x = va_arg(args, int);      // Lấy "hello" như int → CRASH!
```

2. **Type Promotion - Cực kỳ quan trọng:**
```c
// Gọi: func(3, 'A', 3.14f, 100);
//              ↑    ↑
//              char float

va_list args;
va_start(args, count);

// ❌ SAI
char c = va_arg(args, char);    // ERROR! char → int
float f = va_arg(args, float);  // ERROR! float → double

// ✅ ĐÚNG
char c = (char)va_arg(args, int);       // OK
float f = (float)va_arg(args, double);  // OK
int x = va_arg(args, int);              // OK
```

**Tại sao?** Khi truyền vào `...`, C tự động promote:
- `char` → `int`
- `short` → `int`
- `float` → `double`

3. **Không gọi va_arg quá số lượng tham số:**
```c
void func(int count, ...) {
    va_list args;
    va_start(args, count);
    
    // Gọi: func(2, 10, 20);
    
    int a = va_arg(args, int);  // OK: a = 10
    int b = va_arg(args, int);  // OK: b = 20
    int c = va_arg(args, int);  // ❌ UNDEFINED BEHAVIOR! Không có tham số thứ 3!
    
    va_end(args);
}
```

---

#### 🔬 4️⃣ va_end(ap) - Kết thúc

**Cú pháp:**
```c
va_end(ap);
```

**va_end làm gì?**

`va_end` **dọn dẹp** tài nguyên được sử dụng bởi `va_list`.

**Tại sao cần va_end?**
- Trên một số platform, `va_start` có thể allocate memory hoặc resources
- `va_end` giải phóng những resources đó
- Không gọi `va_end` có thể gây **memory leak**

**Bên trong va_end (Conceptual):**

```c
// Trên simple platforms:
#define va_end(ap) ((void)0)  // Không làm gì

// Trên complex platforms (x86-64):
#define va_end(ap) \
    do { \
        /* Cleanup register save area */ \
        /* Free allocated memory */ \
    } while(0)
```

**⚠️ Quy tắc bắt buộc:**

```c
// ✅ ĐÚNG - Luôn gọi va_end
void good_func(int count, ...) {
    va_list args;
    va_start(args, count);
    
    // ... làm việc với args ...
    
    va_end(args);  // ← BẮT BUỘC!
}

// ❌ SAI - Quên va_end
void bad_func(int count, ...) {
    va_list args;
    va_start(args, count);
    
    // ... làm việc với args ...
    
    // Quên va_end() → Có thể memory leak!
}

// ✅ ĐÚNG - va_end ngay cả khi return sớm
void good_func2(int count, ...) {
    va_list args;
    va_start(args, count);
    
    if (count <= 0) {
        va_end(args);  // ← Phải gọi trước khi return!
        return;
    }
    
    // ... làm việc với args ...
    
    va_end(args);
}
```

---

#### 🔬 5️⃣ va_copy(dest, src) - Copy va_list [C99]

**Cú pháp:**
```c
va_list args1, args2;
va_start(args1, last);
va_copy(args2, args1);  // Copy args1 → args2
```

**Tại sao cần va_copy?**

**Vấn đề:** Sau khi dùng `va_arg`, con trỏ đã di chuyển. Nếu muốn dùng lại từ đầu?

```c
void func(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    vprintf(format, args);   // Lần 1: OK
    vprintf(format, args);   // Lần 2: UNDEFINED BEHAVIOR!
    //                          args đã di chuyển rồi!
    
    va_end(args);
}
```

**Giải pháp:** Dùng `va_copy`!

```c
void func(const char *format, ...) {
    va_list args, args_copy;
    va_start(args, format);
    
    va_copy(args_copy, args);  // Copy args → args_copy
    
    vprintf(format, args);      // Dùng args
    vprintf(format, args_copy); // Dùng args_copy (bản copy)
    
    va_end(args_copy);  // ← Phải end cả 2!
    va_end(args);
}
```

**Bên trong va_copy:**

```c
// Simple implementation:
#define va_copy(dest, src) ((dest) = (src))

// Complex implementation (x86-64):
#define va_copy(dest, src) \
    do { \
        (dest)[0].gp_offset = (src)[0].gp_offset; \
        (dest)[0].fp_offset = (src)[0].fp_offset; \
        (dest)[0].overflow_arg_area = (src)[0].overflow_arg_area; \
        (dest)[0].reg_save_area = (src)[0].reg_save_area; \
    } while(0)
```

**Ví dụ thực tế:**

```c
#include <stdio.h>
#include <stdarg.h>

// In message ra cả console VÀ file
void log_dual(FILE *fp, const char *format, ...) {
    va_list console_args, file_args;
    
    va_start(console_args, format);
    va_copy(file_args, console_args);  // Copy
    
    // In ra console
    printf("[CONSOLE] ");
    vprintf(format, console_args);
    printf("\n");
    
    // In ra file
    fprintf(fp, "[FILE] ");
    vfprintf(fp, format, file_args);
    fprintf(fp, "\n");
    
    va_end(file_args);      // End cả 2
    va_end(console_args);
}

int main() {
    FILE *fp = fopen("log.txt", "w");
    log_dual(fp, "User %s logged in at %d:%d", "admin", 14, 30);
    fclose(fp);
    return 0;
}
```

---

#### 📊 TÓM TẮT QUAN HỆ GIỮA CÁC THÀNH PHẦN

```
┌─────────────────────────────────────────────────────────┐
│         LUỒNG HOẠT ĐỘNG CỦA STDARG.H                    │
├─────────────────────────────────────────────────────────┤
│                                                         │
│  1. KHAI BÁO                                            │
│     va_list args;                                       │
│     └─ Tạo biến để lưu thông tin tham số                │
│                                                         │
│  2. KHỞI TẠO                                            │
│     va_start(args, last_param);                         │
│     └─ args trỏ đến tham số đầu tiên trong ...          │
│                                                         │
│  3. LẤY THAM SỐ (lặp lại nhiều lần)                     │
│     type value = va_arg(args, type);                    │
│     ├─ Lấy giá trị tham số hiện tại                     │
│     └─ Di chuyển đến tham số tiếp theo                  │
│                                                         │
│  4. (TÙY CHỌN) COPY                                     │
│     va_copy(args2, args);                               │
│     └─ Tạo bản copy để dùng lại                         │
│                                                         │
│  5. KẾT THÚC (BẮT BUỘC!)                                │
│     va_end(args);                                       │
│     └─ Dọn dẹp tài nguyên                               │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

---

#### 🎯 VÍ DỤ TỔNG HỢP

```c
#include <stdio.h>
#include <stdarg.h>

void demo_all_components(int count, ...) {
    printf("=== DEMO TẤT CẢ THÀNH PHẦN ===\n\n");
    
    // 1. KHAI BÁO va_list
    va_list args, args_copy;
    printf("1. Đã khai báo va_list args, args_copy\n");
    
    // 2. KHỞI TẠO với va_start
    va_start(args, count);
    printf("2. Đã khởi tạo args với va_start(args, count)\n");
    printf("   → args giờ trỏ đến tham số đầu tiên sau 'count'\n\n");
    
    // 3. COPY với va_copy
    va_copy(args_copy, args);
    printf("3. Đã copy args → args_copy\n\n");
    
    // 4. LẤY THAM SỐ với va_arg
    printf("4. Lấy %d tham số bằng va_arg:\n", count);
    for (int i = 0; i < count; i++) {
        int value = va_arg(args, int);
        printf("   Tham số %d: %d\n", i + 1, value);
    }
    printf("\n");
    
    // 5. SỬ DỤNG BẢN COPY
    printf("5. Dùng lại bản copy:\n");
    for (int i = 0; i < count; i++) {
        int value = va_arg(args_copy, int);
        printf("   Tham số %d (từ copy): %d\n", i + 1, value);
    }
    printf("\n");
    
    // 6. KẾT THÚC với va_end
    va_end(args_copy);
    va_end(args);
    printf("6. Đã gọi va_end cho cả args và args_copy\n");
}

int main() {
    demo_all_components(5, 10, 20, 30, 40, 50);
    return 0;
}
```

---

## 3. CÚ PHÁP VÀ QUY TẮC

### 3.1 Cú pháp khai báo

```c
return_type function_name(type1 param1, type2 param2, ..., typeN paramN, ...);
//                                                                          ↑
//                                                                  Dấu ... (ellipsis)
```

**Quy tắc bắt buộc:**
1. ✅ Phải có **ít nhất 1 tham số cố định** trước `...`
2. ✅ Dấu `...` phải ở **cuối cùng**
3. ✅ Không thể có tham số nào sau `...`

**Ví dụ:**
```c
// ✅ ĐÚNG
void func1(int count, ...);
void func2(const char *format, ...);
void func3(int a, int b, ...);

// ❌ SAI
void func4(...);              // Không có tham số cố định
void func5(..., int x);       // ... không ở cuối
void func6(int, ...);         // Tham số cố định không có tên
```

### 3.2 Quy trình sử dụng chuẩn

```c
return_type function_name(fixed_params, ...) {
    // BƯỚC 1: Khai báo va_list
    va_list args;
    
    // BƯỚC 2: Khởi tạo va_list
    va_start(args, last_fixed_param);
    
    // BƯỚC 3: Lấy các tham số
    type1 value1 = va_arg(args, type1);
    type2 value2 = va_arg(args, type2);
    // ...
    
    // BƯỚC 4: Kết thúc (BẮT BUỘC!)
    va_end(args);
    
    return result;
}
```

---

## 4. VÍ DỤ TỪ CƠ BẢN ĐÉN NÂNG CAO

### 4.1 Ví dụ 1: Hàm cộng nhiều số (Cơ bản)

```c
#include <stdio.h>
#include <stdarg.h>

/**
 * Cộng nhiều số nguyên
 * @param count Số lượng số cần cộng
 * @param ... Các số cần cộng
 */
int sum(int count, ...) {
    int total = 0;
    va_list args;
    
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
    va_end(args);
    
    return total;
}

// Sử dụng:
int main() {
    printf("%d\n", sum(3, 10, 20, 30));        // 60
    printf("%d\n", sum(5, 1, 2, 3, 4, 5));     // 15
    printf("%d\n", sum(2, 100, 200));          // 300
    return 0;
}
```

### 4.2 Ví dụ 2: Tìm giá trị lớn nhất

```c
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

/**
 * Tìm số lớn nhất trong danh sách
 * @param count Số lượng số
 * @param ... Các số cần so sánh
 */
int max(int count, ...) {
    if (count <= 0) return INT_MIN;
    
    va_list args;
    va_start(args, count);
    
    int max_value = va_arg(args, int);  // Lấy số đầu tiên
    
    for (int i = 1; i < count; i++) {
        int value = va_arg(args, int);
        if (value > max_value) {
            max_value = value;
        }
    }
    
    va_end(args);
    return max_value;
}

// Sử dụng:
int main() {
    printf("%d\n", max(5, 10, 25, 8, 42, 15));  // 42
    printf("%d\n", max(3, 100, 50, 75));        // 100
    return 0;
}
```

### 4.3 Ví dụ 3: Nối nhiều chuỗi

```c
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

/**
 * Nối nhiều chuỗi lại với nhau
 * @param buffer Buffer để lưu kết quả
 * @param size Kích thước buffer
 * @param count Số lượng chuỗi
 * @param ... Các chuỗi cần nối
 */
void concat(char *buffer, size_t size, int count, ...) {
    buffer[0] = '\0';  // Reset buffer
    
    va_list args;
    va_start(args, count);
    
    for (int i = 0; i < count; i++) {
        char *str = va_arg(args, char*);
        strncat(buffer, str, size - strlen(buffer) - 1);
    }
    
    va_end(args);
}

// Sử dụng:
int main() {
    char result[256];
    concat(result, sizeof(result), 4, "Hello", " ", "World", "!");
    printf("%s\n", result);  // Hello World!
    return 0;
}
```

### 4.4 Ví dụ 4: Printf đơn giản tự làm

```c
#include <stdio.h>
#include <stdarg.h>

/**
 * Printf đơn giản - chỉ hỗ trợ %d, %s, %c
 */
void my_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%' && format[i + 1] != '\0') {
            i++;  // Nhảy sang ký tự sau %
            
            switch (format[i]) {
                case 'd': {
                    int value = va_arg(args, int);
                    printf("%d", value);
                    break;
                }
                case 's': {
                    char *value = va_arg(args, char*);
                    printf("%s", value);
                    break;
                }
                case 'c': {
                    // char được promote thành int
                    char value = (char)va_arg(args, int);
                    printf("%c", value);
                    break;
                }
                default:
                    printf("%%%c", format[i]);
            }
        } else {
            printf("%c", format[i]);
        }
    }
    
    va_end(args);
}

// Sử dụng:
int main() {
    my_printf("Hello, %s!\n", "World");
    my_printf("Number: %d, Char: %c\n", 42, 'A');
    return 0;
}
```

### 4.5 Ví dụ 5: Tính trung bình (với kiểu double)

```c
#include <stdio.h>
#include <stdarg.h>

/**
 * Tính trung bình của nhiều số thực
 */
double average(int count, ...) {
    if (count <= 0) return 0.0;
    
    double sum = 0.0;
    va_list args;
    
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        sum += va_arg(args, double);
    }
    va_end(args);
    
    return sum / count;
}

// Sử dụng:
int main() {
    printf("%.2f\n", average(3, 10.5, 20.3, 15.7));  // 15.50
    printf("%.2f\n", average(4, 1.0, 2.0, 3.0, 4.0)); // 2.50
    return 0;
}
```

---

## 5. TYPE PROMOTION RULES

### 5.1 Quy tắc tự động chuyển đổi kiểu

Khi truyền tham số vào `...`, C tự động **promote** (nâng cấp) một số kiểu dữ liệu:

```c
┌─────────────────────────────────────────────────────────┐
│           TYPE PROMOTION RULES                          │
├─────────────────────────────────────────────────────────┤
│                                                         │
│  char     →  int                                        │
│  short    →  int                                        │
│  float    →  double                                     │
│                                                         │
│  int      →  int      (không đổi)                       │
│  long     →  long     (không đổi)                       │
│  double   →  double   (không đổi)                       │
│  pointer  →  pointer  (không đổi)                       │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

### 5.2 Ví dụ minh họa

```c
#include <stdio.h>
#include <stdarg.h>

void test_types(int count, ...) {
    va_list args;
    va_start(args, count);
    
    // ❌ SAI - char được promote thành int
    // char c = va_arg(args, char);  // COMPILE ERROR!
    
    // ✅ ĐÚNG
    char c = (char)va_arg(args, int);
    
    // ❌ SAI - float được promote thành double
    // float f = va_arg(args, float);  // COMPILE ERROR!
    
    // ✅ ĐÚNG
    float f = (float)va_arg(args, double);
    
    // ✅ ĐÚNG - int, long, double, pointer không đổi
    int i = va_arg(args, int);
    long l = va_arg(args, long);
    double d = va_arg(args, double);
    char *s = va_arg(args, char*);
    
    va_end(args);
}

int main() {
    char ch = 'A';
    float fl = 3.14f;
    
    // Khi truyền vào, char → int, float → double
    test_types(6, ch, fl, 42, 100L, 2.718, "Hello");
    
    return 0;
}
```

### 5.3 Bảng tra cứu nhanh

| Kiểu truyền vào | Kiểu trong ... | va_arg cần dùng |
|-----------------|----------------|-----------------|
| `char`          | `int`          | `va_arg(args, int)` |
| `short`         | `int`          | `va_arg(args, int)` |
| `float`         | `double`       | `va_arg(args, double)` |
| `int`           | `int`          | `va_arg(args, int)` |
| `long`          | `long`         | `va_arg(args, long)` |
| `double`        | `double`       | `va_arg(args, double)` |
| `char*`         | `char*`        | `va_arg(args, char*)` |
| `struct X`      | `struct X`     | `va_arg(args, struct X)` |

---

## 6. SNPRINTF VS VSNPRINTF

### 6.1 Sự khác biệt

```c
┌─────────────────────────────────────────────────────────┐
│         SNPRINTF vs VSNPRINTF                           │
├─────────────────────────────────────────────────────────┤
│                                                         │
│  snprintf(buffer, size, format, ...)                    │
│  ├─ Nhận tham số trực tiếp (...)                       │
│  ├─ Dùng trong hàm thông thường                        │
│  └─ Ví dụ: snprintf(buf, 100, "x=%d", x);              │
│                                                         │
│  vsnprintf(buffer, size, format, va_list)               │
│  ├─ Nhận va_list                                       │
│  ├─ Dùng trong variadic function                       │
│  └─ Ví dụ: vsnprintf(buf, 100, format, args);          │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

### 6.2 Ví dụ so sánh

```c
#include <stdio.h>
#include <stdarg.h>

// Hàm thông thường - dùng snprintf
void normal_function(int x, int y) {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "x=%d, y=%d", x, y);
    printf("%s\n", buffer);
}

// Variadic function - dùng vsnprintf
void variadic_function(const char *format, ...) {
    char buffer[100];
    
    va_list args;
    va_start(args, format);
    
    // ✅ ĐÚNG - Dùng vsnprintf với va_list
    vsnprintf(buffer, sizeof(buffer), format, args);
    
    // ❌ SAI - Không thể dùng snprintf với va_list
    // snprintf(buffer, sizeof(buffer), format, args);  // ERROR!
    
    va_end(args);
    
    printf("%s\n", buffer);
}

int main() {
    normal_function(10, 20);
    variadic_function("x=%d, y=%d", 10, 20);
    return 0;
}
```

### 6.3 Họ hàm printf

```c
┌─────────────────────────────────────────────────────────┐
│              HỌ HÀM PRINTF                              │
├─────────────────────────────────────────────────────────┤
│                                                         │
│  Variadic (...)          va_list version                │
│  ─────────────────────   ──────────────────────         │
│  printf(fmt, ...)        vprintf(fmt, args)             │
│  fprintf(fp, fmt, ...)   vfprintf(fp, fmt, args)        │
│  sprintf(buf, fmt, ...)  vsprintf(buf, fmt, args)       │
│  snprintf(buf, n, ...)   vsnprintf(buf, n, fmt, args)   │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

### 6.4 Ví dụ wrapper function

```c
#include <stdio.h>
#include <stdarg.h>

/**
 * Wrapper cho fprintf - thêm prefix tự động
 */
void log_to_file(FILE *fp, const char *format, ...) {
    // In prefix
    fprintf(fp, "[LOG] ");
    
    // In message với vfprintf
    va_list args;
    va_start(args, format);
    vfprintf(fp, format, args);
    va_end(args);
    
    fprintf(fp, "\n");
}

int main() {
    FILE *fp = fopen("log.txt", "w");
    
    log_to_file(fp, "Application started");
    log_to_file(fp, "User %s logged in", "admin");
    log_to_file(fp, "Processing %d items", 42);
    
    fclose(fp);
    return 0;
}
```

---

## 7. BEST PRACTICES

### 7.1 Luôn gọi va_end()

```c
// ✅ ĐÚNG
void good_function(int count, ...) {
    va_list args;
    va_start(args, count);
    
    // ... làm việc với args ...
    
    va_end(args);  // ← BẮT BUỘC!
}

// ❌ SAI - Quên va_end()
void bad_function(int count, ...) {
    va_list args;
    va_start(args, count);
    
    // ... làm việc với args ...
    
    // Quên va_end() → Memory leak có thể xảy ra!
}
```

### 7.2 Kiểm tra số lượng tham số

```c
// ✅ ĐÚNG - Có kiểm tra
int sum(int count, ...) {
    if (count <= 0) return 0;  // ← Kiểm tra
    
    va_list args;
    va_start(args, count);
    
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
    
    va_end(args);
    return total;
}
```

### 7.3 Sử dụng const cho format string

```c
// ✅ ĐÚNG
void logger(const char *format, ...) {
    // ...
}

// ❌ Không tốt
void logger(char *format, ...) {
    // ...
}
```

### 7.4 Document rõ ràng

```c
/**
 * @brief Tính tổng nhiều số nguyên
 * 
 * @param count Số lượng số cần cộng (phải > 0)
 * @param ... Các số nguyên cần cộng
 * @return Tổng các số, hoặc 0 nếu count <= 0
 * 
 * @example
 *   int result = sum(3, 10, 20, 30);  // result = 60
 */
int sum(int count, ...) {
    // ...
}
```

---

## 8. COMMON PITFALLS

### 8.1 Quên Type Promotion

```c
// ❌ SAI
void wrong(int count, ...) {
    va_list args;
    va_start(args, count);
    
    char c = va_arg(args, char);    // ERROR! char → int
    float f = va_arg(args, float);  // ERROR! float → double
    
    va_end(args);
}

// ✅ ĐÚNG
void correct(int count, ...) {
    va_list args;
    va_start(args, count);
    
    char c = (char)va_arg(args, int);
    float f = (float)va_arg(args, double);
    
    va_end(args);
}
```

### 8.2 Không biết số lượng tham số

```c
// ❌ NGUY HIỂM - Không biết khi nào dừng
void dangerous(...) {  // Không có tham số cố định!
    va_list args;
    // va_start(args, ???);  // Không biết tham số cuối là gì!
}

// ✅ ĐÚNG - Có cách biết số lượng
void safe1(int count, ...) {  // Truyền count
    // ...
}

void safe2(const char *format, ...) {  // Đếm % trong format
    // ...
}
```

### 8.3 Sai thứ tự kiểu dữ liệu

```c
void func(int count, ...) {
    va_list args;
    va_start(args, count);
    
    // Gọi: func(2, 10, "hello");
    
    int x = va_arg(args, int);      // OK: x = 10
    char *s = va_arg(args, char*);  // OK: s = "hello"
    
    va_end(args);
}

void wrong_func(int count, ...) {
    va_list args;
    va_start(args, count);
    
    // Gọi: wrong_func(2, 10, "hello");
    
    char *s = va_arg(args, char*);  // ❌ SAI! Lấy int như char*
    int x = va_arg(args, int);      // ❌ SAI! Lấy char* như int
    
    va_end(args);
}
```

### 8.4 Reuse va_list mà không va_copy

```c
// ❌ SAI - Reuse va_list
void wrong(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    vprintf(format, args);   // Lần 1: OK
    vprintf(format, args);   // Lần 2: UNDEFINED BEHAVIOR!
    
    va_end(args);
}

// ✅ ĐÚNG - Dùng va_copy
void correct(const char *format, ...) {
    va_list args, args_copy;
    va_start(args, format);
    
    va_copy(args_copy, args);  // Copy
    
    vprintf(format, args);      // Lần 1: dùng args
    vprintf(format, args_copy); // Lần 2: dùng args_copy
    
    va_end(args_copy);
    va_end(args);
}
```

---

## 9. ADVANCED TECHNIQUES

### 9.1 va_copy - Copy va_list

```c
#include <stdio.h>
#include <stdarg.h>

/**
 * In message ra cả console và file
 */
void log_dual(FILE *fp, const char *format, ...) {
    va_list args1, args2;
    
    va_start(args1, format);
    va_copy(args2, args1);  // Copy args1 → args2
    
    // In ra console
    vprintf(format, args1);
    printf("\n");
    
    // In ra file
    vfprintf(fp, format, args2);
    fprintf(fp, "\n");
    
    va_end(args2);
    va_end(args1);
}

int main() {
    FILE *fp = fopen("output.txt", "w");
    log_dual(fp, "User %s logged in at %d:%d", "admin", 14, 30);
    fclose(fp);
    return 0;
}
```

### 9.2 Nested Variadic Functions

```c
#include <stdio.h>
#include <stdarg.h>

// Hàm helper nhận va_list
void log_helper(const char *prefix, const char *format, va_list args) {
    printf("[%s] ", prefix);
    vprintf(format, args);
    printf("\n");
}

// Hàm wrapper nhận ...
void log_info(const char *format, ...) {
    va_list args;
    va_start(args, format);
    log_helper("INFO", format, args);
    va_end(args);
}

void log_error(const char *format, ...) {
    va_list args;
    va_start(args, format);
    log_helper("ERROR", format, args);
    va_end(args);
}

int main() {
    log_info("Application started");
    log_error("Failed to connect to %s", "database");
    return 0;
}
```

### 9.3 Sentinel Value Pattern

```c
#include <stdio.h>
#include <stdarg.h>

/**
 * Cộng các số cho đến khi gặp 0
 * Không cần truyền count!
 */
int sum_until_zero(int first, ...) {
    int total = first;
    
    va_list args;
    va_start(args, first);
    
    int value;
    while ((value = va_arg(args, int)) != 0) {
        total += value;
    }
    
    va_end(args);
    return total;
}

int main() {
    printf("%d\n", sum_until_zero(10, 20, 30, 0));        // 60
    printf("%d\n", sum_until_zero(1, 2, 3, 4, 5, 0));     // 15
    return 0;
}
```

### 9.4 Type-safe Variadic với Macro

```c
#include <stdio.h>
#include <stdarg.h>

// Hàm internal
void _sum_impl(int count, ...) {
    va_list args;
    va_start(args, count);
    
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
    
    va_end(args);
    printf("Sum = %d\n", total);
}

// Macro đếm số tham số tự động (C99)
#define COUNT_ARGS(...) (sizeof((int[]){__VA_ARGS__})/sizeof(int))
#define sum(...) _sum_impl(COUNT_ARGS(__VA_ARGS__), __VA_ARGS__)

int main() {
    sum(10, 20, 30);           // Không cần truyền count!
    sum(1, 2, 3, 4, 5);
    return 0;
}
```

---

## 10. REAL-WORLD APPLICATIONS

### 10.1 Logger System

```c
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} LogLevel;

void logger(LogLevel level, const char *file, int line, const char *format, ...) {
    // Timestamp
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timestamp[64];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);
    
    // Level string
    const char *level_str[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    
    // Format message
    char message[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(message, sizeof(message), format, args);
    va_end(args);
    
    // Print
    printf("[%s] [%s] [%s:%d] - %s\n", 
           timestamp, level_str[level], file, line, message);
}

#define log_debug(...) logger(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)  logger(LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...) logger(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)

int main() {
    log_info("Application started");
    log_error("Failed to connect to %s", "database");
    log_debug("Variable x = %d", 42);
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
} StringBuilder;

void sb_init(StringBuilder *sb) {
    sb->buffer[0] = '\0';
    sb->length = 0;
}

void sb_append(StringBuilder *sb, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    size_t remaining = sizeof(sb->buffer) - sb->length;
    int written = vsnprintf(sb->buffer + sb->length, remaining, format, args);
    
    if (written > 0) {
        sb->length += written;
    }
    
    va_end(args);
}

int main() {
    StringBuilder sb;
    sb_init(&sb);
    
    sb_append(&sb, "Name: %s\n", "John");
    sb_append(&sb, "Age: %d\n", 30);
    sb_append(&sb, "Score: %.2f\n", 95.5);
    
    printf("%s", sb.buffer);
    return 0;
}
```

### 10.3 Error Handler

```c
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void fatal_error(const char *format, ...) {
    fprintf(stderr, "FATAL ERROR: ");
    
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    
    fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
}

int main() {
    FILE *fp = fopen("nonexistent.txt", "r");
    if (!fp) {
        fatal_error("Cannot open file: %s", "nonexistent.txt");
    }
    return 0;
}
```

---

## 📚 TÓM TẮT

### Checklist nhanh

```
✅ Phải có ít nhất 1 tham số cố định trước ...
✅ Dấu ... phải ở cuối cùng
✅ Luôn gọi va_end() sau va_start()
✅ Nhớ type promotion: char→int, float→double
✅ Dùng vsnprintf, không phải snprintf trong variadic function
✅ Dùng va_copy nếu cần reuse va_list
✅ Document rõ ràng cách sử dụng
```

### Khi nào dùng Variadic Functions?

✅ **NÊN dùng:**
- Logging/debugging
- String formatting
- Wrapper functions
- Khi số lượng tham số thực sự thay đổi

❌ **KHÔNG NÊN dùng:**
- Khi có thể dùng array/struct
- Khi type safety quan trọng
- Khi performance critical

---

> 💡 **Lời khuyên cuối:** Variadic functions rất mạnh mẽ nhưng cũng dễ sai. Hãy luôn kiểm tra kỹ và document rõ ràng!
