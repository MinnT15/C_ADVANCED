# 📝 GIẢI THÍCH ĐỀ BÀI - LOGGER SYSTEM

> **Phân tích chi tiết đề bài xây dựng hệ thống Logger chuyên nghiệp**

---

## 📋 MỤC LỤC

1. [Tổng quan đề bài](#1-tổng-quan-đề-bài)
2. [Vấn đề cần giải quyết](#2-vấn-đề-cần-giải-quyết)
3. [Yêu cầu phần mềm](#3-yêu-cầu-phần-mềm)
4. [Yêu cầu chức năng](#4-yêu-cầu-chức-năng)
5. [Mục tiêu cần đạt được](#5-mục-tiêu-cần-đạt-được)
6. [Ràng buộc kỹ thuật](#6-ràng-buộc-kỹ-thuật)

---

## 1. TỔNG QUAN ĐỀ BÀI

### 1.1 Bối cảnh

Trong các ứng dụng thực tế, việc chỉ dùng `printf` để gỡ lỗi và ghi lại thông tin là **KHÔNG ĐỦ**.

**Vấn đề của printf:**
```c
printf("Lỗi kết nối database\n");
printf("User đăng nhập\n");
printf("Giá trị x = %d\n", x);
```

❌ Không biết log nào quan trọng, log nào không quan trọng  
❌ Không biết log xuất hiện lúc nào (thời gian)  
❌ Không biết log ở file nào, dòng nào  
❌ Không thể tắt/bật log dễ dàng  
❌ Không thể lưu log vào file để xem sau  

### 1.2 Giải pháp

Xây dựng một **hệ thống logger chuyên nghiệp** với đầy đủ tính năng:

✅ Phân loại log theo mức độ nghiêm trọng  
✅ Tự động thêm timestamp  
✅ Tự động thêm vị trí (file:line)  
✅ Ghi ra nhiều nơi (console + file)  
✅ Lọc log theo mức độ  
✅ Dễ sử dụng với macro tiện lợi  

---

## 2. VẤN ĐỀ CẦN GIẢI QUYẾT

### 2.1 So sánh: printf vs Logger

```c
┌─────────────────────────────────────────────────────────────────┐
│              PRINTF vs LOGGER                                   │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  ❌ PRINTF (Cũ):                                                │
│  printf("Lỗi kết nối database\n");                              │
│  → Output: Lỗi kết nối database                                 │
│                                                                 │
│  ✅ LOGGER (Mới):                                               │
│  log_error("Lỗi kết nối database");                             │
│  → Output:                                                      │
│  [2026-02-02 10:30:45] [ERROR] [main.c:25] - Lỗi kết nối database│
│   ↑                     ↑       ↑                               │
│   Timestamp             Level   File:Line                       │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

### 2.2 Lợi ích của Logger

```
1. PHÂN LOẠI: Biết log nào quan trọng (ERROR) hay không (DEBUG)
2. TIMESTAMP: Biết chính xác log xuất hiện lúc nào
3. VỊ TRÍ: Biết log ở file nào, dòng nào
4. LỌC: Chỉ hiện log quan trọng khi cần
5. LƯU TRỮ: Lưu vào file để phân tích sau
```

---

## 3. YÊU CẦU PHẦN MỀM

### 3.1 Cấu trúc mã nguồn

Đề bài yêu cầu tạo **3 files**:

```
3_LOGGER/
├── logger.h      ← Header file (khai báo API)
├── logger.c      ← Implementation (code thực thi)
└── main.c        ← Demo/test chương trình
```

**Giải thích:**
- `logger.h`: Khai báo enum, functions, macros
- `logger.c`: Triển khai các functions
- `main.c`: Chương trình test/demo logger

### 3.2 Các mức Log (8 cấp độ theo chuẩn syslog)

Đề bài yêu cầu sử dụng **enum** để định nghĩa 8 cấp độ log:

```c
typedef enum {
    LOG_EMERGENCY = 0,  // Hệ thống sập, không dùng được
    LOG_ALERT     = 1,  // Phải xử lý NGAY LẬP TỨC
    LOG_CRITICAL  = 2,  // Lỗi nghiêm trọng
    LOG_ERROR     = 3,  // Lỗi thông thường
    LOG_WARNING   = 4,  // Cảnh báo
    LOG_NOTICE    = 5,  // Thông báo quan trọng
    LOG_INFO      = 6,  // Thông tin
    LOG_DEBUG     = 7   // Debug (ít quan trọng nhất)
} LogLevel;
```

**Ý nghĩa:**
```
┌─────────────────────────────────────────────────────────────────┐
│              8 MỨC ĐỘ LOG                                       │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  🔴 EMERGENCY (0) - Hệ thống sập                                │
│     Ví dụ: "Hết RAM, hệ thống crash!"                           │
│                                                                 │
│  🔴 ALERT (1) - Phải xử lý ngay                                 │
│     Ví dụ: "Database bị tấn công!"                              │
│                                                                 │
│  🔴 CRITICAL (2) - Lỗi nghiêm trọng                             │
│     Ví dụ: "Không kết nối được database"                        │
│                                                                 │
│  🟠 ERROR (3) - Lỗi thông thường                                │
│     Ví dụ: "File không tồn tại"                                 │
│                                                                 │
│  🟡 WARNING (4) - Cảnh báo                                      │
│     Ví dụ: "Bộ nhớ sắp đầy (90%)"                               │
│                                                                 │
│  🔵 NOTICE (5) - Thông báo quan trọng                           │
│     Ví dụ: "User admin đã đăng nhập"                            │
│                                                                 │
│  🟢 INFO (6) - Thông tin                                        │
│     Ví dụ: "Ứng dụng khởi động thành công"                      │
│                                                                 │
│  ⚪ DEBUG (7) - Debug                                           │
│     Ví dụ: "Giá trị biến x = 42"                                │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

### 3.3 Định dạng Log chuẩn

Mỗi dòng log **BẮT BUỘC** có định dạng:

```
[YYYY-MM-DD HH:MM:SS] [LEVEL] [FILENAME:LINE] - Message
```

**Ví dụ cụ thể:**
```
[2026-02-02 10:30:45] [ERROR] [main.c:25] - Failed to connect to database
[2026-02-02 10:30:46] [INFO] [user.c:102] - User logged in successfully
[2026-02-02 10:30:47] [DEBUG] [calc.c:55] - Value of x = 42
```

**Giải thích từng phần:**

| Phần | Ví dụ | Cách lấy |
|------|-------|----------|
| Timestamp | `[2026-02-02 10:30:45]` | Dùng `time()` và `strftime()` |
| Level | `[ERROR]` | Chuyển enum → string |
| File:Line | `[main.c:25]` | Dùng macro `__FILE__` và `__LINE__` |
| Message | `Failed to connect...` | Format string từ user |

---

## 4. YÊU CẦU CHỨC NĂNG

### 4.1 Logger đa đầu ra (Multi-target Logger)

Logger phải ghi log **ĐỒNG THỜI** ra 2 nơi:

```
┌──────────────┐
│   Your Code  │
│  log_error() │
└──────┬───────┘
       │
       ▼
┌──────────────┐
│    LOGGER    │
└──┬────────┬──┘
   │        │
   ▼        ▼
┌─────┐  ┌──────┐
│ 🖥️   │  │ 📄    │
│Console│ │ File │
│stderr │  │app.log│
│stdout │  │      │
└─────┘  └──────┘
```

**Chi tiết:**

1. **Console (màn hình):**
   - Log nghiêm trọng (EMERGENCY, ALERT, CRITICAL) → `stderr`
   - Log thông thường (ERROR, WARNING, INFO, DEBUG) → `stdout`

2. **File (tùy chọn):**
   - Nếu khởi tạo với tên file → ghi vào file
   - Nếu không → chỉ ghi ra console

**Ví dụ sử dụng:**
```c
// Chỉ ghi ra console
logger_init(LOG_INFO, NULL);

// Ghi ra cả console VÀ file
logger_init(LOG_INFO, "app.log");
```

### 4.2 Lọc theo cấp độ (Level Filtering)

Đây là tính năng **CỰC KỲ QUAN TRỌNG**!

**Nguyên tắc:** Chỉ hiển thị log có **mức độ ≤ min_level** (số càng nhỏ càng nghiêm trọng)

**Ví dụ:**
```c
// Khởi tạo với mức tối thiểu là WARNING (4)
logger_init(LOG_WARNING, "app.log");

// Các log sau đây:
log_debug("Debug info");      // ❌ KHÔNG hiển thị (7 > 4)
log_info("App started");      // ❌ KHÔNG hiển thị (6 > 4)
log_notice("User login");     // ❌ KHÔNG hiển thị (5 > 4)
log_warning("Low memory");    // ✅ HIỂN THỊ (4 = 4)
log_error("File not found");  // ✅ HIỂN THỊ (3 < 4)
log_critical("DB crashed");   // ✅ HIỂN THỊ (2 < 4)
```

**Tại sao cần tính năng này?**
- Khi phát triển: Set `LOG_DEBUG` → Thấy tất cả
- Khi production: Set `LOG_ERROR` → Chỉ thấy lỗi

**Bonus:** Có thể thay đổi mức độ khi đang chạy:
```c
logger_set_level(LOG_ERROR);  // Từ giờ chỉ hiện ERROR trở lên
```

### 4.3 Tự động thêm Metadata

**Metadata** = Thông tin bổ sung tự động

Bạn chỉ cần viết:
```c
log_error("Lỗi kết nối");
```

Logger tự động thêm:
- ✅ **Timestamp** - Lấy từ hệ thống (dùng `time()`)
- ✅ **Filename** - Lấy từ macro `__FILE__`
- ✅ **Line number** - Lấy từ macro `__LINE__`

Output:
```
[2026-02-02 10:30:45] [ERROR] [main.c:45] - Lỗi kết nối
```

**Bạn KHÔNG cần phải tự điền!**

### 4.4 Giao diện tiện lợi (Convenience Interface)

Thay vì phải viết:
```c
logger_log(LOG_ERROR, __FILE__, __LINE__, "Lỗi kết nối");
```

Bạn chỉ cần:
```c
log_error("Lỗi kết nối");
```

**Cách làm:** Dùng macro!
```c
#define log_error(...) logger_log(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
```

Macro tự động điền `__FILE__` và `__LINE__` cho bạn!

---

## 5. MỤC TIÊU CẦN ĐẠT ĐƯỢC

Đề bài yêu cầu bạn nắm vững các kỹ thuật sau:

### 5.1 stdarg.h - Hàm với số tham số thay đổi

```c
void logger_log(LogLevel level, const char *file, int line, 
                const char *format, ...) {
    va_list args;
    va_start(args, format);
    vsnprintf(message, size, format, args);
    va_end(args);
}
```

**Học được:**
- Sử dụng `va_list`, `va_start`, `va_arg`, `va_end`
- Hiểu cách hoạt động của variadic functions

### 5.2 snprintf và vsnprintf

```c
// snprintf - Hàm thông thường
char buffer[100];
snprintf(buffer, sizeof(buffer), "x = %d", x);

// vsnprintf - Dùng với va_list
va_list args;
va_start(args, format);
vsnprintf(buffer, sizeof(buffer), format, args);
va_end(args);
```

**Học được:**
- Format chuỗi an toàn (không buffer overflow)
- Sự khác biệt giữa `snprintf` và `vsnprintf`

### 5.3 File I/O

```c
FILE *fp = fopen("app.log", "a");  // Mở file append mode
fprintf(fp, "%s\n", log_message);  // Ghi vào file
fflush(fp);                        // Flush buffer
fclose(fp);                        // Đóng file
```

**Học được:**
- Mở, ghi, đóng file
- Sử dụng `fopen`, `fprintf`, `fflush`, `fclose`

### 5.4 static - Đóng gói module

```c
static struct {
    LogLevel min_level;
    FILE *log_file;
    bool initialized;
} g_logger;  // Chỉ dùng trong file này
```

**Học được:**
- Sử dụng `static` để đóng gói trạng thái
- Tạo module C có tính tái sử dụng cao

### 5.5 Macro

```c
#define log_error(...) logger_log(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
```

**Học được:**
- Sử dụng macro `__FILE__` và `__LINE__`
- Tạo macro tiện lợi với `__VA_ARGS__`

### 5.6 Xây dựng module C hoàn chỉnh

**Học được:**
- Tổ chức code thành module (header + implementation)
- Tạo API rõ ràng, dễ sử dụng
- Code có tính tái sử dụng cao

---

## 6. RÀNG BUỘC KỸ THUẬT

### 6.1 Lưu ý quan trọng

```
❌ KHÔNG dùng Design Pattern
✅ Chỉ dùng standard library (stdio.h, stdarg.h, time.h, string.h)
✅ Code phải clean và maintainable
✅ Tuân thủ C99 standard
```

### 6.2 Thư viện được phép sử dụng

```c
#include <stdio.h>      // printf, fprintf, fopen, fclose, fflush
#include <stdarg.h>     // va_list, va_start, va_arg, va_end
#include <time.h>       // time, localtime, strftime
#include <string.h>     // strrchr (lấy basename)
#include <stdbool.h>    // bool, true, false
```

### 6.3 Không được dùng

```
❌ Thư viện bên ngoài (third-party libraries)
❌ Design patterns phức tạp
❌ C++ features
```

---

## 📊 TÓM TẮT ĐỀ BÀI

### Bạn cần xây dựng một logger có:

```
✅ 8 mức độ log (EMERGENCY → DEBUG)
✅ Format chuẩn: [Time] [Level] [File:Line] - Message
✅ Ghi ra console VÀ file
✅ Lọc log theo mức độ
✅ Tự động thêm timestamp, file, line
✅ Macro tiện lợi (log_error(), log_info(), ...)
```

### Cấu trúc code:

```
✅ logger.h - Header (enum, functions, macros)
✅ logger.c - Implementation
✅ main.c - Demo/test
```

### Kỹ thuật sử dụng:

```
✅ Variadic functions (stdarg.h)
✅ vsnprintf (format string an toàn)
✅ File I/O (fopen, fprintf, fclose, fflush)
✅ static (module encapsulation)
✅ Macros (__FILE__, __LINE__, __VA_ARGS__)
```

---

## 🎯 KẾT LUẬN

Đề bài yêu cầu bạn xây dựng một **hệ thống logger chuyên nghiệp** để:

1. **Thay thế printf** - Có đầy đủ tính năng cần thiết
2. **Học các kỹ thuật C nâng cao** - Variadic functions, file I/O, macros
3. **Tạo module tái sử dụng** - Có thể dùng trong mọi dự án C sau này

Đây là một bài tập **CỰC KỲ THỰC TÉ** vì logger là thành phần **BẮT BUỘC** trong mọi dự án phần mềm chuyên nghiệp!

---

> 💡 **Lời khuyên:** Đọc kỹ đề bài này trước khi bắt đầu code. Hiểu rõ yêu cầu sẽ giúp bạn implement đúng và nhanh hơn!
