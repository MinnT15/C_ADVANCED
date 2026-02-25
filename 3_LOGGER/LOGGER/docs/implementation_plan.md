# 🚀 KẾ HOẠCH THỰC THI DỰ ÁN LOGGER

> Áp dụng quy trình SDLC chuyên nghiệp cho dự án Logger System

---

## 📋 1. REQUIREMENTS - THU THẬP YÊU CẦU

### 1.1 Áp Dụng Công Thức 5W1H

#### 1️⃣ WHO - AI sử dụng?
- **Người dùng chính**: Developers (lập trình viên)
- **Use case**: Sử dụng logger module trong các dự án C để gỡ lỗi và ghi log

#### 2️⃣ WHAT - LÀM GÌ?
**Chức năng chính:**
- Ghi log ra nhiều đầu ra (console + file)
- Hỗ trợ 8 mức độ log (theo chuẩn syslog)
- Lọc log theo mức độ nghiêm trọng
- Tự động thêm metadata (timestamp, filename, line number)
- Cung cấp macro tiện lợi để sử dụng

#### 3️⃣ WHERE - Ở ĐÂU?
- **Platform**: Desktop PC (Linux/Windows/macOS)
- **Environment**: Terminal/Console
- **Deployment**: Static library hoặc source files

#### 4️⃣ WHEN - KHI NÀO?
- **Deadline**: Theo yêu cầu học tập
- **Real-time**: Không có yêu cầu real-time nghiêm ngặt
- **Performance**: Logging không được ảnh hưởng đáng kể đến hiệu năng chương trình chính

#### 5️⃣ WHY - TẠI SAO?
- **Mục đích**: Xây dựng module logger chuyên nghiệp, tái sử dụng được
- **Lý do**: Thay thế printf đơn giản, học cách tổ chức module C
- **Giá trị**: Có thể sử dụng trong mọi dự án C sau này

#### 6️⃣ HOW - NHƯ THẾ NÀO?
- **Ngôn ngữ**: C (C99 trở lên)
- **Thư viện**: Chỉ dùng standard library (stdio.h, stdarg.h, time.h, string.h)
- **Constraints**: 
  - Không dùng Design Pattern
  - Không dùng thư viện bên ngoài
  - Code phải clean và maintainable

---

### 1.2 Tài Liệu Yêu Cầu (SRS)

```
=============================================================
              TÀI LIỆU YÊU CẦU DỰ ÁN LOGGER
=============================================================
Tên dự án: Professional Logger System
Ngày tạo : 2026-02-01

-------------------------------------------------------------
1. TỔNG QUAN
-------------------------------------------------------------
Mục đích   : Xây dựng module logger chuyên nghiệp cho C
Người dùng : Developers
Nền tảng   : [x] PC   [ ] MCU   [ ] Linux

-------------------------------------------------------------
2. TÍNH NĂNG (Functional Requirements)
-------------------------------------------------------------
ID       | Tên                      | Input              | Output
---------|--------------------------|--------------------|-----------------
FR-001   | Ghi log ra console       | Log message        | stdout/stderr
FR-002   | Ghi log ra file          | Log message        | File text
FR-003   | Hỗ trợ 8 mức log         | Log level          | Filtered output
FR-004   | Lọc theo mức độ          | Min level          | Filtered logs
FR-005   | Thêm timestamp           | -                  | [YYYY-MM-DD HH:MM:SS]
FR-006   | Thêm filename:line       | __FILE__, __LINE__ | [file.c:123]
FR-007   | Macro tiện lợi           | Format string      | Formatted log
FR-008   | Khởi tạo logger          | Config             | Logger instance
FR-009   | Đóng logger              | -                  | Cleanup resources

-------------------------------------------------------------
3. YÊU CẦU PHI CHỨC NĂNG
-------------------------------------------------------------
Response time : < 10 ms (không block chương trình chính)
Max log size  : Không giới hạn (file có thể lớn)
Memory limit  : < 1 KB (static buffers)
Thread-safe   : Không bắt buộc (single-threaded)

-------------------------------------------------------------
4. YÊU CẦU KỸ THUẬT
-------------------------------------------------------------
Ngôn ngữ  : [x] C (C99+)
Compiler  : [x] GCC   [ ] ARM-GCC
Thư viện  : stdio.h, stdarg.h, time.h, string.h, stdbool.h
Hardware  : Desktop PC (x86/x64)

-------------------------------------------------------------
5. RÀNG BUỘC
-------------------------------------------------------------
Deadline  : Theo yêu cầu học tập
Ngân sách : N/A
Khác      : - Không dùng Design Pattern
            - Không dùng thư viện bên ngoài
            - Code phải tuân thủ clean code principles

=============================================================
```

---

## 🎨 2. DESIGN - THIẾT KẾ

### 2.1 Áp Dụng 7 Bước Thiết Kế

#### BƯỚC 1: Xác Định DỮ LIỆU Cần Quản Lý

**Entities (Thực thể):**

```
1️⃣ LOGGER INSTANCE
   - Mức log tối thiểu (min_level)
   - File pointer (nếu ghi ra file)
   - Trạng thái khởi tạo (initialized)

2️⃣ LOG MESSAGE
   - Mức độ log (level)
   - Timestamp
   - Source file name
   - Line number
   - Message content

3️⃣ LOG LEVEL
   - Level value (0-7)
   - Level name string ("EMERGENCY", "ALERT", ...)
```

---

#### BƯỚC 2: Thiết Kế DATA STRUCTURES

```c
// ===== Log Levels (theo chuẩn syslog) =====
typedef enum {
    LOG_EMERGENCY = 0,  // System is unusable
    LOG_ALERT     = 1,  // Action must be taken immediately
    LOG_CRITICAL  = 2,  // Critical conditions
    LOG_ERROR     = 3,  // Error conditions
    LOG_WARNING   = 4,  // Warning conditions
    LOG_NOTICE    = 5,  // Normal but significant condition
    LOG_INFO      = 6,  // Informational messages
    LOG_DEBUG     = 7   // Debug-level messages
} LogLevel;

// ===== Logger Configuration =====
typedef struct {
    LogLevel min_level;      // Mức log tối thiểu
    FILE *log_file;          // File pointer (NULL nếu không ghi file)
    bool initialized;        // Đã khởi tạo chưa?
    char log_filename[256];  // Tên file log
} Logger;
```

---

#### BƯỚC 3: Xác Định OPERATIONS

```
┌─────────────────────────────────────────────────────────┐
│              OPERATIONS CHO LOGGER                      │
├─────────────────────────────────────────────────────────┤
│                                                         │
│  🔧 INITIALIZATION & CLEANUP:                           │
│  ├── logger_init()       - Khởi tạo logger             │
│  ├── logger_set_level()  - Đặt mức log tối thiểu       │
│  └── logger_cleanup()    - Dọn dẹp tài nguyên          │
│                                                         │
│  📝 LOGGING OPERATIONS:                                 │
│  ├── logger_log()        - Hàm log chính (internal)    │
│  ├── log_emergency()     - Log EMERGENCY               │
│  ├── log_alert()         - Log ALERT                   │
│  ├── log_critical()      - Log CRITICAL                │
│  ├── log_error()         - Log ERROR                   │
│  ├── log_warning()       - Log WARNING                 │
│  ├── log_notice()        - Log NOTICE                  │
│  ├── log_info()          - Log INFO                    │
│  └── log_debug()         - Log DEBUG                   │
│                                                         │
│  🛠️ UTILITY OPERATIONS:                                │
│  ├── get_level_string()  - Chuyển level thành string   │
│  ├── get_timestamp()     - Lấy timestamp hiện tại      │
│  └── should_log()        - Kiểm tra có nên log không   │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

---

#### BƯỚC 4: Thiết Kế FUNCTION SIGNATURES

```c
// ===== INITIALIZATION & CLEANUP =====

/**
 * @brief Khởi tạo logger
 * @param min_level Mức log tối thiểu
 * @param log_filename Tên file log (NULL nếu không ghi file)
 * @return 0 nếu thành công, -1 nếu lỗi
 */
int logger_init(LogLevel min_level, const char *log_filename);

/**
 * @brief Thay đổi mức log tối thiểu tại runtime
 * @param min_level Mức log mới
 */
void logger_set_level(LogLevel min_level);

/**
 * @brief Dọn dẹp tài nguyên logger
 */
void logger_cleanup(void);

// ===== CORE LOGGING FUNCTION (Internal) =====

/**
 * @brief Hàm log chính (internal, không gọi trực tiếp)
 * @param level Mức độ log
 * @param file Tên file nguồn
 * @param line Số dòng
 * @param format Format string (như printf)
 * @param ... Các tham số
 */
void logger_log(LogLevel level, const char *file, int line, 
                const char *format, ...);

// ===== CONVENIENCE MACROS =====

// Các macro để dễ sử dụng, tự động điền __FILE__ và __LINE__
#define log_emergency(...) logger_log(LOG_EMERGENCY, __FILE__, __LINE__, __VA_ARGS__)
#define log_alert(...)     logger_log(LOG_ALERT,     __FILE__, __LINE__, __VA_ARGS__)
#define log_critical(...)  logger_log(LOG_CRITICAL,  __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...)     logger_log(LOG_ERROR,     __FILE__, __LINE__, __VA_ARGS__)
#define log_warning(...)   logger_log(LOG_WARNING,   __FILE__, __LINE__, __VA_ARGS__)
#define log_notice(...)    logger_log(LOG_NOTICE,    __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)      logger_log(LOG_INFO,      __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...)     logger_log(LOG_DEBUG,     __FILE__, __LINE__, __VA_ARGS__)

// ===== UTILITY FUNCTIONS (Internal) =====

/**
 * @brief Lấy chuỗi tên của log level
 * @param level Log level
 * @return Chuỗi tên level
 */
static const char* get_level_string(LogLevel level);

/**
 * @brief Lấy timestamp hiện tại
 * @param buffer Buffer để lưu timestamp
 * @param size Kích thước buffer
 */
static void get_timestamp(char *buffer, size_t size);

/**
 * @brief Kiểm tra có nên log message này không
 * @param level Mức độ log
 * @return true nếu nên log, false nếu bỏ qua
 */
static bool should_log(LogLevel level);
```

---

#### BƯỚC 5: Phân Chia MODULES

```
┌─────────────────────────────────────────────────────────┐
│                  MODULE ORGANIZATION                    │
├─────────────────────────────────────────────────────────┤
│                                                         │
│  📄 logger.h                                            │
│  ├── Public API declarations                           │
│  ├── Enum LogLevel                                     │
│  ├── Function prototypes                               │
│  └── Convenience macros                                │
│                                                         │
│  📄 logger.c                                            │
│  ├── Static logger instance                            │
│  ├── Implementation of all functions                   │
│  ├── Utility functions (static)                        │
│  └── Core logging logic                                │
│                                                         │
│  📄 main.c                                              │
│  ├── Demo/test program                                 │
│  ├── Test all log levels                               │
│  ├── Test file output                                  │
│  └── Test level filtering                              │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

---

#### BƯỚC 6: Thiết Kế PROJECT STRUCTURE

```
3_LOGGER/
├── include/
│   └── logger.h          # Public header
├── src/
│   ├── logger.c          # Logger implementation
│   └── main.c            # Demo program
├── logs/                 # Output logs (created at runtime)
│   └── app.log
├── Makefile              # Build system
├── README.md             # Documentation
└── Standard IO.pdf       # Đề bài
```

---

#### BƯỚC 7: Vẽ SYSTEM DIAGRAM

```
┌─────────────────────────────────────────────────────────────────┐
│                    LOGGER SYSTEM ARCHITECTURE                   │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│   ┌─────────────┐                                               │
│   │   main.c    │  (User Application)                           │
│   │             │                                               │
│   │  log_info() │                                               │
│   │  log_error()│                                               │
│   └──────┬──────┘                                               │
│          │                                                      │
│          │ Calls macro                                          │
│          ▼                                                      │
│   ┌─────────────────────────────────────┐                       │
│   │         logger.h (API)              │                       │
│   │  ┌───────────────────────────────┐  │                       │
│   │  │ #define log_info(...)         │  │                       │
│   │  │   logger_log(LOG_INFO,        │  │                       │
│   │  │              __FILE__,        │  │                       │
│   │  │              __LINE__, ...)   │  │                       │
│   │  └───────────────────────────────┘  │                       │
│   └──────────────────┬──────────────────┘                       │
│                      │                                          │
│                      │ Expands to                               │
│                      ▼                                          │
│   ┌──────────────────────────────────────────┐                  │
│   │         logger.c (Implementation)        │                  │
│   │                                          │                  │
│   │  void logger_log(level, file, line, ...) │                  │
│   │  {                                       │                  │
│   │    1. Check should_log(level)            │                  │
│   │    2. Get timestamp                      │                  │
│   │    3. Format message with vsnprintf      │                  │
│   │    4. Write to console (stdout/stderr)   │                  │
│   │    5. Write to file (if enabled)         │                  │
│   │  }                                       │                  │
│   └────────┬──────────────────┬──────────────┘                  │
│            │                  │                                 │
│            ▼                  ▼                                 │
│   ┌────────────────┐  ┌────────────────┐                        │
│   │    Console     │  │   Log File     │                        │
│   │  stdout/stderr │  │   app.log      │                        │
│   └────────────────┘  └────────────────┘                        │
│                                                                 │
│   Output Format:                                                │
│   [2026-02-01 21:30:45] [INFO] [main.c:25] - Application started│
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

## 💻 3. IMPLEMENTATION - TRIỂN KHAI

### 3.1 Thứ Tự Implement

```
1️⃣ Tạo cấu trúc thư mục
   └─ mkdir -p include src logs

2️⃣ Implement logger.h
   ├─ Định nghĩa enum LogLevel
   ├─ Khai báo function prototypes
   └─ Định nghĩa convenience macros

3️⃣ Implement logger.c
   ├─ Static logger instance
   ├─ Utility functions (get_timestamp, get_level_string, should_log)
   ├─ logger_init()
   ├─ logger_set_level()
   ├─ logger_log() - Core function
   └─ logger_cleanup()

4️⃣ Implement main.c
   ├─ Test initialization
   ├─ Test all log levels
   ├─ Test level filtering
   ├─ Test file output
   └─ Test metadata

5️⃣ Tạo Makefile
   ├─ Compiler flags
   ├─ Build targets
   └─ Clean target
```

---

### 3.2 Kỹ Thuật Sử Dụng

```
┌─────────────────────────────────────────────────────────┐
│           KỸ THUẬT CẦN ÁP DỤNG                          │
├─────────────────────────────────────────────────────────┤
│                                                         │
│  ✅ stdarg.h - Variadic Functions                       │
│     ├─ va_list args                                    │
│     ├─ va_start(args, format)                          │
│     ├─ vsnprintf(buffer, size, format, args)           │
│     └─ va_end(args)                                    │
│                                                         │
│  ✅ time.h - Timestamp                                  │
│     ├─ time_t now = time(NULL)                         │
│     ├─ struct tm *tm_info = localtime(&now)            │
│     └─ strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm) │
│                                                         │
│  ✅ stdio.h - File I/O                                  │
│     ├─ FILE *fp = fopen(filename, "a")                 │
│     ├─ fprintf(fp, "%s\n", message)                    │
│     ├─ fflush(fp)                                      │
│     └─ fclose(fp)                                      │
│                                                         │
│  ✅ static - Module Encapsulation                       │
│     ├─ static Logger g_logger (global state)           │
│     └─ static functions (internal helpers)             │
│                                                         │
│  ✅ Macros - Convenience                                │
│     ├─ __FILE__ (compiler macro)                       │
│     ├─ __LINE__ (compiler macro)                       │
│     └─ #define log_info(...) (wrapper macro)           │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

---

## 🧪 4. TESTING - KIỂM THỬ

### 4.1 Test Cases

```
┌─────────────────────────────────────────────────────────┐
│                   TEST CASES                            │
├─────────────────────────────────────────────────────────┤
│                                                         │
│  TC-001: Khởi tạo logger không file                     │
│  ├─ Input:  logger_init(LOG_INFO, NULL)                │
│  └─ Expect: Return 0, chỉ log ra console               │
│                                                         │
│  TC-002: Khởi tạo logger với file                       │
│  ├─ Input:  logger_init(LOG_INFO, "app.log")           │
│  └─ Expect: Return 0, log ra cả console và file        │
│                                                         │
│  TC-003: Test tất cả log levels                         │
│  ├─ Input:  log_emergency/alert/.../debug              │
│  └─ Expect: Hiển thị đúng level name                   │
│                                                         │
│  TC-004: Test level filtering                           │
│  ├─ Input:  Set min_level = LOG_WARNING                │
│  │          Log: DEBUG, INFO, WARNING, ERROR           │
│  └─ Expect: Chỉ hiện WARNING và ERROR                  │
│                                                         │
│  TC-005: Test timestamp format                          │
│  ├─ Input:  log_info("Test")                           │
│  └─ Expect: [YYYY-MM-DD HH:MM:SS] [INFO] ...           │
│                                                         │
│  TC-006: Test file:line metadata                        │
│  ├─ Input:  log_info("Test") tại main.c:25            │
│  └─ Expect: [main.c:25] trong output                   │
│                                                         │
│  TC-007: Test format string                             │
│  ├─ Input:  log_info("Value: %d", 42)                  │
│  └─ Expect: "Value: 42" trong message                  │
│                                                         │
│  TC-008: Test stderr cho critical logs                  │
│  ├─ Input:  log_emergency/alert/critical               │
│  └─ Expect: Output ra stderr (không phải stdout)       │
│                                                         │
│  TC-009: Test runtime level change                      │
│  ├─ Input:  logger_set_level(LOG_ERROR)                │
│  └─ Expect: Chỉ log ERROR trở lên                      │
│                                                         │
│  TC-010: Test cleanup                                   │
│  ├─ Input:  logger_cleanup()                           │
│  └─ Expect: File được đóng, không memory leak          │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

---

## ✅ 5. VERIFICATION - XÁC THỰC

### 5.1 Verification Checklist

```
□ Code compile không warning (gcc -Wall -Wextra)
□ Tất cả test cases pass
□ Output format đúng chuẩn: [YYYY-MM-DD HH:MM:SS] [LEVEL] [FILE:LINE] - Message
□ File log được tạo và ghi đúng
□ Level filtering hoạt động chính xác
□ Macro tự động điền __FILE__ và __LINE__
□ Không memory leak (valgrind)
□ Code tuân thủ clean code principles
□ Comment đầy đủ
□ README.md hướng dẫn sử dụng
```

---

## 📚 6. DOCUMENTATION

### 6.1 README.md Structure

```markdown
# Logger System

## Giới thiệu
- Mô tả ngắn gọn
- Tính năng chính

## Cài đặt
- Yêu cầu hệ thống
- Cách build

## Sử dụng
- Ví dụ code
- API reference

## Ví dụ Output
- Screenshot/text output mẫu

## License
```

---

## 🎯 7. TIMELINE DỰ KIẾN

```
┌─────────────────────────────────────────────────────────┐
│                  TIMELINE                               │
├─────────────────────────────────────────────────────────┤
│                                                         │
│  Phase 1: REQUIREMENTS & DESIGN (30 phút)               │
│  ├─ Phân tích đề bài                                   │
│  ├─ Áp dụng 5W1H                                       │
│  └─ Thiết kế 7 bước                                    │
│                                                         │
│  Phase 2: IMPLEMENTATION (2 giờ)                        │
│  ├─ logger.h (15 phút)                                 │
│  ├─ logger.c (1 giờ)                                   │
│  ├─ main.c (30 phút)                                   │
│  └─ Makefile (15 phút)                                 │
│                                                         │
│  Phase 3: TESTING (45 phút)                             │
│  ├─ Viết test cases                                    │
│  ├─ Chạy tests                                         │
│  └─ Fix bugs                                           │
│                                                         │
│  Phase 4: DOCUMENTATION (30 phút)                       │
│  ├─ Comment code                                       │
│  ├─ Viết README                                        │
│  └─ Tạo walkthrough                                    │
│                                                         │
│  TỔNG: ~4 giờ                                           │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

---

## 🚀 NEXT STEPS

Sau khi plan được approve, sẽ tiến hành:

1. ✅ Tạo cấu trúc thư mục
2. ✅ Implement logger.h
3. ✅ Implement logger.c
4. ✅ Implement main.c
5. ✅ Tạo Makefile
6. ✅ Testing & Verification
7. ✅ Documentation

---

> 💡 **Lưu ý**: Plan này áp dụng đầy đủ quy trình SDLC chuyên nghiệp, giúp bạn làm quen với cách làm việc thực tế trong công ty!
