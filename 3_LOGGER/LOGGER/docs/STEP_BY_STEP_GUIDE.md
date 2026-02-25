# 🚀 HƯỚNG DẪN THỰC THI DỰ ÁN LOGGER - PHONG CÁCH CHUYÊN NGHIỆP

> **Quy trình Incremental Development - Code từng module, test ngay, đảm bảo chất lượng**

---

## 📋 TRIẾT LÝ PHÁT TRIỂN

```
┌─────────────────────────────────────────────────────────────────┐
│         QUY TRÌNH PHÁT TRIỂN CHUYÊN NGHIỆP                      │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  ❌ CÁCH LÀM SAI (Beginner):                                    │
│  1. Code hết tất cả                                             │
│  2. Test một lần ở cuối                                         │
│  3. Gặp lỗi → Không biết lỗi ở đâu                              │
│                                                                 │
│  ✅ CÁCH LÀM ĐÚNG (Professional):                               │
│  1. Code một chức năng nhỏ                                      │
│  2. Test ngay lập tức                                           │
│  3. Pass → Tiếp tục chức năng tiếp theo                         │
│  4. Fail → Fix ngay (biết chính xác lỗi ở đâu)                  │
│                                                                 │
│  Lợi ích:                                                       │
│  ✓ Phát hiện lỗi sớm                                            │
│  ✓ Dễ debug (chỉ test code vừa viết)                            │
│  ✓ Tự tin hơn (luôn có code working)                            │
│  ✓ Giống quy trình công ty thực tế                              │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

## 📋 MỤC LỤC

1. [Chuẩn bị môi trường](#phase-0-chuẩn-bị-môi-trường)
2. [Iteration 1: Logger cơ bản](#iteration-1-logger-cơ-bản)
3. [Iteration 2: Thêm timestamp](#iteration-2-thêm-timestamp)
4. [Iteration 3: Thêm file output](#iteration-3-thêm-file-output)
5. [Iteration 4: Level filtering](#iteration-4-level-filtering)
6. [Iteration 5: Convenience macros](#iteration-5-convenience-macros)
7. [Iteration 6: Polish & Production](#iteration-6-polish--production)

---

## PHASE 0: CHUẨN BỊ MÔI TRƯỜNG

### Bước 0.1: Tạo cấu trúc thư mục

```bash
cd /home/minhtri/Working_space/C_ADVANCED/3_LOGGER

# Tạo thư mục
mkdir -p include src build logs tests
```

### Bước 0.2: Tạo Makefile đơn giản

**File: `Makefile`**

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -g
BUILD_DIR = build

# Phony targets
.PHONY: all clean run test

# Default: build all
all:
	@echo "Use 'make test' to build and run tests"

# Clean
clean:
	rm -rf $(BUILD_DIR)
	@echo "✓ Cleaned"

# Test target (sẽ update trong từng iteration)
test:
	@echo "No tests yet. Will be updated in each iteration."
```

**Giải thích:**
- `-g`: Thêm debug symbols (để dùng gdb nếu cần)
- Makefile này sẽ được **cập nhật liên tục** trong từng iteration

---

## ITERATION 1: LOGGER CỞ BẢN

> **Mục tiêu:** Tạo logger đơn giản nhất - chỉ in ra console với 1 level

### 1.1 Tạo header tối thiểu

**File: `include/logger.h`**

```c
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

// Chỉ 1 level để bắt đầu
typedef enum {
    LOG_INFO = 0
} LogLevel;

// Hàm log đơn giản nhất
void logger_log(LogLevel level, const char *message);

#endif // LOGGER_H
```

### 1.2 Implement hàm log cơ bản

**File: `src/logger.c`**

```c
#include "logger.h"

void logger_log(LogLevel level, const char *message) {
    // Chỉ in ra console, không có gì fancy
    printf("[INFO] %s\n", message);
}
```

### 1.3 Tạo test đơn giản

**File: `tests/test_iteration1.c`**

```c
#include "logger.h"

int main(void) {
    printf("=== ITERATION 1 TEST ===\n");
    printf("Testing basic logger...\n\n");
    
    logger_log(LOG_INFO, "Hello, Logger!");
    logger_log(LOG_INFO, "This is a test message");
    
    printf("\n✓ If you see 2 log lines above, test PASSED\n");
    return 0;
}
```

### 1.4 Update Makefile

**File: `Makefile` (thêm vào cuối)**

```makefile
# Iteration 1 test
test1:
	@echo "Building Iteration 1 test..."
	$(CC) $(CFLAGS) -c src/logger.c -o $(BUILD_DIR)/logger.o
	$(CC) $(CFLAGS) tests/test_iteration1.c $(BUILD_DIR)/logger.o -o $(BUILD_DIR)/test1
	@echo "Running test..."
	@echo ""
	./$(BUILD_DIR)/test1
```

### 1.5 Build và Test

```bash
mkdir -p build
make test1
```

**Output mong đợi:**
```
=== ITERATION 1 TEST ===
Testing basic logger...

[INFO] Hello, Logger!
[INFO] This is a test message

✓ If you see 2 log lines above, test PASSED
```

### 1.6 Checklist Iteration 1

```
□ Code compile không lỗi
□ Thấy 2 dòng log trên console
□ Format: [INFO] Message
```

**✅ PASS → Tiếp tục Iteration 2**  
**❌ FAIL → Fix trước khi tiếp tục**

---

## ITERATION 2: THÊM TIMESTAMP

> **Mục tiêu:** Thêm timestamp vào mỗi log line

### 2.1 Update logger.c - Thêm timestamp

**File: `src/logger.c`**

```c
#include "logger.h"
#include <time.h>
#include <string.h>

// Hàm helper lấy timestamp
static void get_timestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

void logger_log(LogLevel level, const char *message) {
    char timestamp[64];
    get_timestamp(timestamp, sizeof(timestamp));
    
    // Format: [YYYY-MM-DD HH:MM:SS] [INFO] Message
    printf("[%s] [INFO] %s\n", timestamp, message);
}
```

### 2.2 Tạo test cho Iteration 2

**File: `tests/test_iteration2.c`**

```c
#include "logger.h"
#include <unistd.h>

int main(void) {
    printf("=== ITERATION 2 TEST ===\n");
    printf("Testing timestamp...\n\n");
    
    logger_log(LOG_INFO, "First message");
    sleep(1);  // Đợi 1 giây
    logger_log(LOG_INFO, "Second message (1 second later)");
    
    printf("\n✓ Check if timestamps are different\n");
    printf("✓ Format should be: [YYYY-MM-DD HH:MM:SS] [INFO] Message\n");
    return 0;
}
```

### 2.3 Update Makefile

**File: `Makefile` (thêm vào cuối)**

```makefile
# Iteration 2 test
test2:
	@echo "Building Iteration 2 test..."
	$(CC) $(CFLAGS) -c src/logger.c -o $(BUILD_DIR)/logger.o
	$(CC) $(CFLAGS) tests/test_iteration2.c $(BUILD_DIR)/logger.o -o $(BUILD_DIR)/test2
	@echo "Running test..."
	@echo ""
	./$(BUILD_DIR)/test2
```

### 2.4 Build và Test

```bash
make test2
```

**Output mong đợi:**
```
=== ITERATION 2 TEST ===
Testing timestamp...

[2026-02-02 10:35:00] [INFO] First message
[2026-02-02 10:35:01] [INFO] Second message (1 second later)

✓ Check if timestamps are different
✓ Format should be: [YYYY-MM-DD HH:MM:SS] [INFO] Message
```

### 2.5 Checklist Iteration 2

```
□ Timestamp xuất hiện
□ Format đúng: [YYYY-MM-DD HH:MM:SS]
□ Timestamp thay đổi theo thời gian
```

**✅ PASS → Tiếp tục Iteration 3**

---

## ITERATION 3: THÊM FILE OUTPUT

> **Mục tiêu:** Logger ghi ra cả file, không chỉ console

### 3.1 Update header - Thêm init/cleanup

**File: `include/logger.h`**

```c
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdbool.h>

typedef enum {
    LOG_INFO = 0
} LogLevel;

// Thêm init và cleanup
int logger_init(const char *log_filename);
void logger_cleanup(void);
void logger_log(LogLevel level, const char *message);

#endif // LOGGER_H
```

**File: `src/logger.c`**

```c
#include "logger.h"
#include <time.h>
#include <string.h>

// Định nghĩa struct Logger với typedef
typedef struct {
    FILE *log_file;
    bool initialized;
} Logger;

// Tạo biến static (chỉ dùng trong file này)
static Logger g_logger = { NULL, false };

// Helper: get timestamp
static void get_timestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

// Init logger
int logger_init(const char *log_filename) {
    if (g_logger.initialized) {
        logger_cleanup();
    }
    
    if (log_filename != NULL) {
        g_logger.log_file = fopen(log_filename, "a");
        if (g_logger.log_file == NULL) {
            fprintf(stderr, "Error: Cannot open log file: %s\n", log_filename);
            return -1;
        }
    }
    
    g_logger.initialized = true;
    return 0;
}

// Cleanup
void logger_cleanup(void) {
    if (g_logger.log_file != NULL) {
        fclose(g_logger.log_file);
        g_logger.log_file = NULL;
    }
    g_logger.initialized = false;
}

// Log function
void logger_log(LogLevel level, const char *message) {
    char timestamp[64];
    get_timestamp(timestamp, sizeof(timestamp));
    
    char log_line[512];
    snprintf(log_line, sizeof(log_line), "[%s] [INFO] %s", timestamp, message);
    
    // Ghi ra console
    printf("%s\n", log_line);
    
    // Ghi ra file (nếu có)
    if (g_logger.log_file != NULL) {
        fprintf(g_logger.log_file, "%s\n", log_line);
        fflush(g_logger.log_file);  // Flush ngay
    }
}
```



### 3.3 Tạo test cho Iteration 3

**File: `tests/test_iteration3.c`**

```c
#include "logger.h"

int main(void) {
    printf("=== ITERATION 3 TEST ===\n");
    printf("Testing file output...\n\n");
    
    // Test 1: Console only
    printf("--- Test 1: Console only ---\n");
    logger_init(NULL);
    logger_log(LOG_INFO, "Console only message");
    logger_cleanup();
    
    // Test 2: Console + File
    printf("\n--- Test 2: Console + File ---\n");
    logger_init("logs/test_iter3.log");
    logger_log(LOG_INFO, "This goes to console AND file");
    logger_log(LOG_INFO, "Second message to both");
    logger_cleanup();
    
    printf("\n✓ Check logs/test_iter3.log for file output\n");
    return 0;
}
```

### 3.4 Update Makefile

```makefile
# Iteration 3 test
test3:
	@mkdir -p logs
	@echo "Building Iteration 3 test..."
	$(CC) $(CFLAGS) -c src/logger.c -o $(BUILD_DIR)/logger.o
	$(CC) $(CFLAGS) tests/test_iteration3.c $(BUILD_DIR)/logger.o -o $(BUILD_DIR)/test3
	@echo "Running test..."
	@echo ""
	./$(BUILD_DIR)/test3
	@echo ""
	@echo "File output:"
	@cat logs/test_iter3.log
```

### 3.5 Build và Test

```bash
make test3
```

**Output mong đợi:**
```
=== ITERATION 3 TEST ===
Testing file output...

--- Test 1: Console only ---
[2026-02-02 10:40:00] [INFO] Console only message

--- Test 2: Console + File ---
[2026-02-02 10:40:00] [INFO] This goes to console AND file
[2026-02-02 10:40:00] [INFO] Second message to both

✓ Check logs/test_iter3.log for file output

File output:
[2026-02-02 10:40:00] [INFO] This goes to console AND file
[2026-02-02 10:40:00] [INFO] Second message to both
```

### 3.6 Checklist Iteration 3

```
□ logger_init() hoạt động
□ logger_cleanup() hoạt động
□ Console output vẫn hoạt động
□ File output hoạt động
□ File được tạo trong logs/
```

**✅ PASS → Tiếp tục Iteration 4**

---

## ITERATION 4: LEVEL FILTERING

> **Mục tiêu:** Thêm tất cả 8 log levels và filtering

### 4.1 Update header - Thêm tất cả levels

**File: `include/logger.h`**

```c
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdbool.h>

// Tất cả 8 levels
typedef enum {
    LOG_EMERGENCY = 0,
    LOG_ALERT     = 1,
    LOG_CRITICAL  = 2,
    LOG_ERROR     = 3,
    LOG_WARNING   = 4,
    LOG_NOTICE    = 5,
    LOG_INFO      = 6,
    LOG_DEBUG     = 7
} LogLevel;

// Thêm min_level vào init
int logger_init(LogLevel min_level, const char *log_filename);
void logger_set_level(LogLevel min_level);
void logger_cleanup(void);
void logger_log(LogLevel level, const char *message);

#endif // LOGGER_H
```

**File: `src/logger.c`**

```c
#include "logger.h"
#include <time.h>
#include <string.h>

// Định nghĩa struct Logger với typedef
typedef struct {
    LogLevel min_level;
    FILE *log_file;
    bool initialized;
} Logger;

// Tạo biến static
static Logger g_logger = { LOG_INFO, NULL, false };

// Helper: get level string
static const char* get_level_string(LogLevel level) {
    static const char *level_strings[] = {
        "EMERGENCY", "ALERT", "CRITICAL", "ERROR",
        "WARNING", "NOTICE", "INFO", "DEBUG"
    };
    
    if (level >= 0 && level <= LOG_DEBUG) {
        return level_strings[level];
    }
    return "UNKNOWN";
}

// Helper: get timestamp
static void get_timestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

// Helper: should log?
static bool should_log(LogLevel level) {
    return level <= g_logger.min_level;
}

// Init
int logger_init(LogLevel min_level, const char *log_filename) {
    if (g_logger.initialized) {
        logger_cleanup();
    }
    
    g_logger.min_level = min_level;
    
    if (log_filename != NULL) {
        g_logger.log_file = fopen(log_filename, "a");
        if (g_logger.log_file == NULL) {
            fprintf(stderr, "Error: Cannot open log file: %s\n", log_filename);
            return -1;
        }
    }
    
    g_logger.initialized = true;
    return 0;
}

// Set level
void logger_set_level(LogLevel min_level) {
    g_logger.min_level = min_level;
}

// Cleanup
void logger_cleanup(void) {
    if (g_logger.log_file != NULL) {
        fclose(g_logger.log_file);
        g_logger.log_file = NULL;
    }
    g_logger.initialized = false;
}

// Log
void logger_log(LogLevel level, const char *message) {
    // Filtering
    if (!should_log(level)) {
        return;
    }
    
    char timestamp[64];
    get_timestamp(timestamp, sizeof(timestamp));
    
    const char *level_str = get_level_string(level);
    
    char log_line[512];
    snprintf(log_line, sizeof(log_line), "[%s] [%s] %s", 
             timestamp, level_str, message);
    
    // Console
    printf("%s\n", log_line);
    
    // File
    if (g_logger.log_file != NULL) {
        fprintf(g_logger.log_file, "%s\n", log_line);
        fflush(g_logger.log_file);
    }
}
```



### 4.3 Tạo test cho Iteration 4

**File: `tests/test_iteration4.c`**

```c
#include "logger.h"

int main(void) {
    printf("=== ITERATION 4 TEST ===\n");
    printf("Testing all levels and filtering...\n\n");
    
    // Test 1: All levels (min = DEBUG)
    printf("--- Test 1: All levels (min = DEBUG) ---\n");
    logger_init(LOG_DEBUG, NULL);
    
    logger_log(LOG_EMERGENCY, "EMERGENCY message");
    logger_log(LOG_ALERT, "ALERT message");
    logger_log(LOG_CRITICAL, "CRITICAL message");
    logger_log(LOG_ERROR, "ERROR message");
    logger_log(LOG_WARNING, "WARNING message");
    logger_log(LOG_NOTICE, "NOTICE message");
    logger_log(LOG_INFO, "INFO message");
    logger_log(LOG_DEBUG, "DEBUG message");
    
    printf("\n✓ Should see all 8 levels above\n");
    
    // Test 2: Filtering (min = WARNING)
    printf("\n--- Test 2: Filtering (min = WARNING) ---\n");
    logger_set_level(LOG_WARNING);
    
    printf("These should show:\n");
    logger_log(LOG_EMERGENCY, "Should show");
    logger_log(LOG_ALERT, "Should show");
    logger_log(LOG_CRITICAL, "Should show");
    logger_log(LOG_ERROR, "Should show");
    logger_log(LOG_WARNING, "Should show");
    
    printf("\nThese should NOT show:\n");
    logger_log(LOG_NOTICE, "Should NOT show");
    logger_log(LOG_INFO, "Should NOT show");
    logger_log(LOG_DEBUG, "Should NOT show");
    
    printf("(If you see log lines above, filtering is broken!)\n");
    
    logger_cleanup();
    
    printf("\n✓ Test completed\n");
    return 0;
}
```

### 4.4 Update Makefile

```makefile
# Iteration 4 test
test4:
	@echo "Building Iteration 4 test..."
	$(CC) $(CFLAGS) -c src/logger.c -o $(BUILD_DIR)/logger.o
	$(CC) $(CFLAGS) tests/test_iteration4.c $(BUILD_DIR)/logger.o -o $(BUILD_DIR)/test4
	@echo "Running test..."
	@echo ""
	./$(BUILD_DIR)/test4
```

### 4.5 Build và Test

```bash
make test4
```

### 4.6 Checklist Iteration 4

```
□ Tất cả 8 levels hoạt động
□ Level string đúng (EMERGENCY, ALERT, ...)
□ Filtering hoạt động (chỉ hiện log <= min_level)
□ logger_set_level() hoạt động
```

**✅ PASS → Tiếp tục Iteration 5**

---

## ITERATION 5: CONVENIENCE MACROS

> **Mục tiêu:** Thêm variadic functions và macros tiện lợi

### 5.1 Update header - Thêm macros

**File: `include/logger.h`**

```c
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdbool.h>

typedef enum {
    LOG_EMERGENCY = 0,
    LOG_ALERT     = 1,
    LOG_CRITICAL  = 2,
    LOG_ERROR     = 3,
    LOG_WARNING   = 4,
    LOG_NOTICE    = 5,
    LOG_INFO      = 6,
    LOG_DEBUG     = 7
} LogLevel;

// API functions
int logger_init(LogLevel min_level, const char *log_filename);
void logger_set_level(LogLevel min_level);
void logger_cleanup(void);

// Core logging function (variadic)
void logger_log(LogLevel level, const char *file, int line,
                const char *format, ...);

// Convenience macros
#define log_emergency(...) logger_log(LOG_EMERGENCY, __FILE__, __LINE__, __VA_ARGS__)
#define log_alert(...)     logger_log(LOG_ALERT,     __FILE__, __LINE__, __VA_ARGS__)
#define log_critical(...)  logger_log(LOG_CRITICAL,  __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...)     logger_log(LOG_ERROR,     __FILE__, __LINE__, __VA_ARGS__)
#define log_warning(...)   logger_log(LOG_WARNING,   __FILE__, __LINE__, __VA_ARGS__)
#define log_notice(...)    logger_log(LOG_NOTICE,    __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)      logger_log(LOG_INFO,      __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...)     logger_log(LOG_DEBUG,     __FILE__, __LINE__, __VA_ARGS__)

#endif // LOGGER_H
```

**File: `src/logger.c`**

```c
#include "logger.h"
#include <stdarg.h>
#include <time.h>
#include <string.h>

// Định nghĩa struct Logger với typedef
typedef struct {
    LogLevel min_level;
    FILE *log_file;
    bool initialized;
} Logger;

// Tạo biến static
static Logger g_logger = { LOG_INFO, NULL, false };

// Helper: get level string
static const char* get_level_string(LogLevel level) {
    static const char *level_strings[] = {
        "EMERGENCY", "ALERT", "CRITICAL", "ERROR",
        "WARNING", "NOTICE", "INFO", "DEBUG"
    };
    
    if (level >= 0 && level <= LOG_DEBUG) {
        return level_strings[level];
    }
    return "UNKNOWN";
}

// Helper: get timestamp
static void get_timestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

// Helper: should log?
static bool should_log(LogLevel level) {
    return level <= g_logger.min_level;
}

// Init
int logger_init(LogLevel min_level, const char *log_filename) {
    if (g_logger.initialized) {
        logger_cleanup();
    }
    
    g_logger.min_level = min_level;
    
    if (log_filename != NULL) {
        g_logger.log_file = fopen(log_filename, "a");
        if (g_logger.log_file == NULL) {
            fprintf(stderr, "Error: Cannot open log file: %s\n", log_filename);
            return -1;
        }
    }
    
    g_logger.initialized = true;
    return 0;
}

// Set level
void logger_set_level(LogLevel min_level) {
    g_logger.min_level = min_level;
}

// Cleanup
void logger_cleanup(void) {
    if (g_logger.log_file != NULL) {
        fclose(g_logger.log_file);
        g_logger.log_file = NULL;
    }
    g_logger.initialized = false;
}

// Log function (variadic)
void logger_log(LogLevel level, const char *file, int line,
                const char *format, ...) {
    // Filtering
    if (!should_log(level)) {
        return;
    }
    
    // Get timestamp
    char timestamp[64];
    get_timestamp(timestamp, sizeof(timestamp));
    
    // Get level string
    const char *level_str = get_level_string(level);
    
    // Get basename of file
    const char *filename = strrchr(file, '/');
    filename = (filename != NULL) ? filename + 1 : file;
    
    // Format message using vsnprintf
    char message[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(message, sizeof(message), format, args);
    va_end(args);
    
    // Format log line
    char log_line[2048];
    snprintf(log_line, sizeof(log_line),
             "[%s] [%s] [%s:%d] - %s",
             timestamp, level_str, filename, line, message);
    
    // Console
    printf("%s\n", log_line);
    
    // File
    if (g_logger.log_file != NULL) {
        fprintf(g_logger.log_file, "%s\n", log_line);
        fflush(g_logger.log_file);
    }
}
```



### 5.3 Tạo test cho Iteration 5

**File: `tests/test_iteration5.c`**

```c
#include "logger.h"

int main(void) {
    printf("=== ITERATION 5 TEST ===\n");
    printf("Testing variadic functions and macros...\n\n");
    
    logger_init(LOG_DEBUG, NULL);
    
    // Test 1: Simple messages
    printf("--- Test 1: Simple messages ---\n");
    log_info("Simple message");
    log_error("Error occurred");
    
    // Test 2: Format strings
    printf("\n--- Test 2: Format strings ---\n");
    int user_id = 12345;
    char *username = "alice";
    log_info("User login: id=%d, name=%s", user_id, username);
    log_error("Connection failed: host=%s, port=%d", "192.168.1.1", 8080);
    
    // Test 3: Check file:line
    printf("\n--- Test 3: Check file:line ---\n");
    log_debug("This is from line %d", __LINE__);
    log_warning("This is from line %d", __LINE__);
    
    printf("\n✓ Check that file:line is correct\n");
    printf("✓ Check that format strings work\n");
    
    logger_cleanup();
    return 0;
}
```

### 5.4 Update Makefile

```makefile
# Iteration 5 test
test5:
	@echo "Building Iteration 5 test..."
	$(CC) $(CFLAGS) -c src/logger.c -o $(BUILD_DIR)/logger.o
	$(CC) $(CFLAGS) tests/test_iteration5.c $(BUILD_DIR)/logger.o -o $(BUILD_DIR)/test5
	@echo "Running test..."
	@echo ""
	./$(BUILD_DIR)/test5
```

### 5.5 Build và Test

```bash
make test5
```

### 5.6 Checklist Iteration 5

```
□ Variadic functions hoạt động
□ Format strings hoạt động (%d, %s, etc.)
□ __FILE__ và __LINE__ tự động
□ Macros tiện lợi hoạt động
□ File:line hiển thị đúng
```

**✅ PASS → Tiếp tục Iteration 6**

---

## ITERATION 6: POLISH & PRODUCTION

> **Mục tiêu:** Hoàn thiện, thêm stderr cho critical logs, tạo demo cuối cùng

### 6.1 Update logger.c - Thêm stderr

**File: `src/logger.c` (chỉ update hàm logger_log)**

```c
// ... (giữ nguyên phần trên)

// Helper: get console stream
static FILE* get_console_stream(LogLevel level) {
    // Critical logs (0-2) → stderr
    // Normal logs (3-7) → stdout
    return (level <= LOG_CRITICAL) ? stderr : stdout;
}

// Log function
void logger_log(LogLevel level, const char *file, int line,
                const char *format, ...) {
    if (!should_log(level)) {
        return;
    }
    
    char timestamp[64];
    get_timestamp(timestamp, sizeof(timestamp));
    
    const char *level_str = get_level_string(level);
    
    const char *filename = strrchr(file, '/');
    filename = (filename != NULL) ? filename + 1 : file;
    
    char message[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(message, sizeof(message), format, args);
    va_end(args);
    
    char log_line[2048];
    snprintf(log_line, sizeof(log_line),
             "[%s] [%s] [%s:%d] - %s",
             timestamp, level_str, filename, line, message);
    
    // Console (stdout or stderr)
    FILE *console = get_console_stream(level);
    fprintf(console, "%s\n", log_line);
    fflush(console);
    
    // File
    if (g_logger.log_file != NULL) {
        fprintf(g_logger.log_file, "%s\n", log_line);
        fflush(g_logger.log_file);
    }
}
```

### 6.2 Tạo demo cuối cùng

**File: `src/main.c`**

```c
#include "logger.h"
#include <stdio.h>

int main(void) {
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║     LOGGER SYSTEM - FINAL DEMO                 ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");
    
    // Initialize
    logger_init(LOG_DEBUG, "logs/app.log");
    
    // Demo all levels
    printf("=== All Log Levels ===\n");
    log_emergency("System is unusable!");
    log_alert("Action must be taken immediately!");
    log_critical("Critical condition occurred");
    log_error("Error: File not found");
    log_warning("Warning: Memory usage at 90%%");
    log_notice("User admin logged in");
    log_info("Application started successfully");
    log_debug("Debug: Variable x = %d", 42);
    
    printf("\n=== Format Strings ===\n");
    log_info("User %s logged in from %s", "alice", "192.168.1.100");
    log_error("Connection timeout after %d seconds", 30);
    
    printf("\n=== Level Filtering ===\n");
    logger_set_level(LOG_WARNING);
    log_debug("This should NOT appear");
    log_info("This should NOT appear");
    log_warning("This SHOULD appear");
    log_error("This SHOULD appear");
    
    // Cleanup
    logger_cleanup();
    
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║     DEMO COMPLETED                             ║\n");
    printf("║     Check logs/app.log for file output         ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
    
    return 0;
}
```

### 6.3 Update Makefile - Final version

**File: `Makefile` (version cuối cùng)**

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -g
BUILD_DIR = build
LOG_DIR = logs

SOURCES = src/logger.c src/main.c
OBJECTS = $(BUILD_DIR)/logger.o $(BUILD_DIR)/main.o
TARGET = $(BUILD_DIR)/logger_demo

.PHONY: all clean run test1 test2 test3 test4 test5

# Build final demo
all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BUILD_DIR)
	$(CC) $(OBJECTS) -o $(TARGET)
	@echo "✓ Build successful: $(TARGET)"

$(BUILD_DIR)/logger.o: src/logger.c include/logger.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/logger.c -o $(BUILD_DIR)/logger.o

$(BUILD_DIR)/main.o: src/main.c include/logger.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/main.c -o $(BUILD_DIR)/main.o

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(LOG_DIR):
	mkdir -p $(LOG_DIR)

# Run final demo
run: $(TARGET) | $(LOG_DIR)
	@echo "Running logger demo..."
	@echo ""
	./$(TARGET)

# Clean
clean:
	rm -rf $(BUILD_DIR)
	@echo "✓ Cleaned"

cleanall: clean
	rm -rf $(LOG_DIR)

# Individual iteration tests
test1:
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/logger.c -o $(BUILD_DIR)/logger.o
	$(CC) $(CFLAGS) tests/test_iteration1.c $(BUILD_DIR)/logger.o -o $(BUILD_DIR)/test1
	./$(BUILD_DIR)/test1

test2:
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/logger.c -o $(BUILD_DIR)/logger.o
	$(CC) $(CFLAGS) tests/test_iteration2.c $(BUILD_DIR)/logger.o -o $(BUILD_DIR)/test2
	./$(BUILD_DIR)/test2

test3:
	@mkdir -p $(BUILD_DIR) $(LOG_DIR)
	$(CC) $(CFLAGS) -c src/logger.c -o $(BUILD_DIR)/logger.o
	$(CC) $(CFLAGS) tests/test_iteration3.c $(BUILD_DIR)/logger.o -o $(BUILD_DIR)/test3
	./$(BUILD_DIR)/test3

test4:
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/logger.c -o $(BUILD_DIR)/logger.o
	$(CC) $(CFLAGS) tests/test_iteration4.c $(BUILD_DIR)/logger.o -o $(BUILD_DIR)/test4
	./$(BUILD_DIR)/test4

test5:
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/logger.c -o $(BUILD_DIR)/logger.o
	$(CC) $(CFLAGS) tests/test_iteration5.c $(BUILD_DIR)/logger.o -o $(BUILD_DIR)/test5
	./$(BUILD_DIR)/test5
```

### 6.4 Build và Run final demo

```bash
make clean
make all
make run
```

### 6.5 Final Checklist

```
□ Tất cả iterations đều pass
□ Code compile không warning
□ Final demo chạy thành công
□ File log được tạo đúng
□ Stderr/stdout phân chia đúng
□ Format đúng chuẩn
□ Tất cả tính năng hoạt động
```

---

## 📊 TÓM TẮT QUY TRÌNH

```
┌─────────────────────────────────────────────────────────────────┐
│         QUY TRÌNH ĐÃ THỰC HIỆN                                  │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  Iteration 1: Logger cơ bản                                     │
│  ├─ Code: logger.h, logger.c (minimal)                          │
│  ├─ Test: test_iteration1.c                                     │
│  └─ ✓ PASS → Continue                                           │
│                                                                 │
│  Iteration 2: Thêm timestamp                                    │
│  ├─ Update: logger.c (add timestamp)                            │
│  ├─ Test: test_iteration2.c                                     │
│  └─ ✓ PASS → Continue                                           │
│                                                                 │
│  Iteration 3: Thêm file output                                  │
│  ├─ Update: logger.h, logger.c (add init/cleanup)               │
│  ├─ Test: test_iteration3.c                                     │
│  └─ ✓ PASS → Continue                                           │
│                                                                 │
│  Iteration 4: Level filtering                                   │
│  ├─ Update: logger.h, logger.c (8 levels + filtering)           │
│  ├─ Test: test_iteration4.c                                     │
│  └─ ✓ PASS → Continue                                           │
│                                                                 │
│  Iteration 5: Convenience macros                                │
│  ├─ Update: logger.h, logger.c (variadic + macros)              │
│  ├─ Test: test_iteration5.c                                     │
│  └─ ✓ PASS → Continue                                           │
│                                                                 │
│  Iteration 6: Polish & Production                               │
│  ├─ Update: logger.c (stderr), main.c (final demo)              │
│  ├─ Test: Final demo                                            │
│  └─ ✓ DONE!                                                     │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

## 🎯 LỢI ÍCH CỦA QUY TRÌNH NÀY

### So với cách làm "code hết rồi test"

```
✅ Phát hiện lỗi sớm
   → Mỗi iteration test ngay, biết chính xác lỗi ở đâu

✅ Dễ debug
   → Chỉ debug code vừa viết, không phải debug cả dự án

✅ Tự tin hơn
   → Luôn có code working, không sợ "break everything"

✅ Học tốt hơn
   → Hiểu rõ từng phần, không bị overwhelm

✅ Giống thực tế
   → Đây là cách làm việc trong công ty chuyên nghiệp
```

---

## 💡 LỜI KHUYÊN

### Khi làm theo hướng dẫn này:

1. **KHÔNG skip iteration nào** - Mỗi iteration xây dựng trên iteration trước
2. **Test kỹ từng iteration** - Đảm bảo PASS trước khi tiếp tục
3. **Hiểu code đang viết** - Đừng copy-paste mù quáng
4. **Commit sau mỗi iteration** - Nếu dùng git
5. **Ghi chú vấn đề gặp phải** - Để học từ lỗi sai

### Nếu gặp lỗi:

1. **Đọc error message kỹ** - Compiler/runtime nói gì?
2. **Kiểm tra iteration hiện tại** - Lỗi ở đâu?
3. **So sánh với code mẫu** - Có gì khác không?
4. **Debug từng bước** - Dùng printf hoặc gdb
5. **Không tiếp tục nếu chưa fix** - Lỗi sẽ tích lũy!

---

## 📦 CODE ĐẦY ĐỦ CUỐI CÙNG

> **Đây là code hoàn chỉnh sau khi hoàn thành tất cả 6 iterations**

### File: `include/logger.h`

```c
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

// Log levels (theo chuẩn syslog)
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

// Core functions
int logger_init(LogLevel min_level, const char *log_filename);
void logger_set_level(LogLevel min_level);
void logger_cleanup(void);
void logger_log(LogLevel level, const char *file, int line,
                const char *format, ...);

// Convenience macros
#define log_emergency(...) logger_log(LOG_EMERGENCY, __FILE__, __LINE__, __VA_ARGS__)
#define log_alert(...)     logger_log(LOG_ALERT,     __FILE__, __LINE__, __VA_ARGS__)
#define log_critical(...)  logger_log(LOG_CRITICAL,  __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...)     logger_log(LOG_ERROR,     __FILE__, __LINE__, __VA_ARGS__)
#define log_warning(...)   logger_log(LOG_WARNING,   __FILE__, __LINE__, __VA_ARGS__)
#define log_notice(...)    logger_log(LOG_NOTICE,    __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)      logger_log(LOG_INFO,      __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...)     logger_log(LOG_DEBUG,     __FILE__, __LINE__, __VA_ARGS__)

#endif // LOGGER_H
```

---

### File: `src/logger.c`

```c
#include "logger.h"
#include <time.h>
#include <string.h>

// Logger state (typedef struct)
typedef struct {
    LogLevel min_level;
    FILE *log_file;
    bool initialized;
} Logger;

// Global static state
static Logger g_logger = { LOG_INFO, NULL, false };

// Helper: Get timestamp
static void get_timestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

// Helper: Convert level to string
static const char* get_level_string(LogLevel level) {
    static const char *level_strings[] = {
        "EMERGENCY", "ALERT", "CRITICAL", "ERROR",
        "WARNING", "NOTICE", "INFO", "DEBUG"
    };
    
    if (level >= 0 && level <= LOG_DEBUG) {
        return level_strings[level];
    }
    return "UNKNOWN";
}

// Helper: Check if should log
static bool should_log(LogLevel level) {
    return level <= g_logger.min_level;
}

// Helper: Get console stream (stderr for critical, stdout for others)
static FILE* get_console_stream(LogLevel level) {
    return (level <= LOG_CRITICAL) ? stderr : stdout;
}

// Initialize logger
int logger_init(LogLevel min_level, const char *log_filename) {
    // Cleanup if already initialized
    if (g_logger.initialized) {
        logger_cleanup();
    }
    
    g_logger.min_level = min_level;
    
    // Open log file if specified
    if (log_filename != NULL) {
        g_logger.log_file = fopen(log_filename, "a");
        if (g_logger.log_file == NULL) {
            fprintf(stderr, "Error: Cannot open log file: %s\n", log_filename);
            return -1;
        }
    }
    
    g_logger.initialized = true;
    return 0;
}

// Set minimum log level
void logger_set_level(LogLevel min_level) {
    g_logger.min_level = min_level;
}

// Cleanup logger
void logger_cleanup(void) {
    if (g_logger.log_file != NULL) {
        fclose(g_logger.log_file);
        g_logger.log_file = NULL;
    }
    g_logger.initialized = false;
}

// Main logging function (variadic)
void logger_log(LogLevel level, const char *file, int line,
                const char *format, ...) {
    // Filter by level
    if (!should_log(level)) {
        return;
    }
    
    // Get timestamp
    char timestamp[64];
    get_timestamp(timestamp, sizeof(timestamp));
    
    // Get level string
    const char *level_str = get_level_string(level);
    
    // Get basename of file
    const char *filename = strrchr(file, '/');
    filename = (filename != NULL) ? filename + 1 : file;
    
    // Format message using variadic arguments
    char message[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(message, sizeof(message), format, args);
    va_end(args);
    
    // Format final log line
    char log_line[2048];
    snprintf(log_line, sizeof(log_line),
             "[%s] [%s] [%s:%d] - %s",
             timestamp, level_str, filename, line, message);
    
    // Write to console (stderr for critical, stdout for others)
    FILE *console = get_console_stream(level);
    fprintf(console, "%s\n", log_line);
    fflush(console);
    
    // Write to file if configured
    if (g_logger.log_file != NULL) {
        fprintf(g_logger.log_file, "%s\n", log_line);
        fflush(g_logger.log_file);
    }
}
```

---

### File: `src/main.c`

```c
#include "logger.h"
#include <stdio.h>

int main(void) {
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║     LOGGER SYSTEM - FINAL DEMO                 ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");
    
    // Initialize logger (DEBUG level, write to file)
    logger_init(LOG_DEBUG, "logs/app.log");
    
    // Demo 1: All log levels
    printf("=== Demo 1: All Log Levels ===\n");
    log_emergency("System is unusable!");
    log_alert("Action must be taken immediately!");
    log_critical("Critical condition occurred");
    log_error("Error: File not found");
    log_warning("Warning: Memory usage at 90%%");
    log_notice("User admin logged in");
    log_info("Application started successfully");
    log_debug("Debug: Variable x = %d", 42);
    
    // Demo 2: Format strings
    printf("\n=== Demo 2: Format Strings ===\n");
    log_info("User %s logged in from %s", "alice", "192.168.1.100");
    log_error("Connection timeout after %d seconds", 30);
    log_debug("Processing %d items, progress: %.2f%%", 100, 75.5);
    
    // Demo 3: Level filtering
    printf("\n=== Demo 3: Level Filtering ===\n");
    printf("Setting level to WARNING...\n");
    logger_set_level(LOG_WARNING);
    
    log_debug("This should NOT appear");
    log_info("This should NOT appear");
    log_warning("This SHOULD appear");
    log_error("This SHOULD appear");
    
    // Demo 4: File and line tracking
    printf("\n=== Demo 4: File and Line Tracking ===\n");
    log_info("Check the log - it shows file:line automatically!");
    log_error("Error on line %d", __LINE__);
    
    // Cleanup
    logger_cleanup();
    
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║     DEMO COMPLETED                             ║\n");
    printf("║     Check logs/app.log for file output         ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
    
    return 0;
}
```

---

### File: `Makefile`

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -g
BUILD_DIR = build
LOG_DIR = logs

SOURCES = src/logger.c src/main.c
OBJECTS = $(BUILD_DIR)/logger.o $(BUILD_DIR)/main.o
TARGET = $(BUILD_DIR)/logger_demo

.PHONY: all clean run test1 test2 test3 test4 test5 help

# Build final demo
all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BUILD_DIR)
	$(CC) $(OBJECTS) -o $(TARGET)
	@echo "✓ Build successful: $(TARGET)"

$(BUILD_DIR)/logger.o: src/logger.c include/logger.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/logger.c -o $(BUILD_DIR)/logger.o

$(BUILD_DIR)/main.o: src/main.c include/logger.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/main.c -o $(BUILD_DIR)/main.o

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(LOG_DIR):
	mkdir -p $(LOG_DIR)

# Run final demo
run: $(TARGET) | $(LOG_DIR)
	@echo "Running logger demo..."
	@echo ""
	./$(TARGET)

# Clean
clean:
	rm -rf $(BUILD_DIR)
	@echo "✓ Cleaned build directory"

cleanall: clean
	rm -rf $(LOG_DIR)
	@echo "✓ Cleaned all (including logs)"

# Individual iteration tests
test1:
	@echo "Building Iteration 1 test..."
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/logger.c -o $(BUILD_DIR)/logger.o
	$(CC) $(CFLAGS) tests/test_iteration1.c $(BUILD_DIR)/logger.o -o $(BUILD_DIR)/test1
	@echo "Running test..."
	@echo ""
	./$(BUILD_DIR)/test1

test2:
	@echo "Building Iteration 2 test..."
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/logger.c -o $(BUILD_DIR)/logger.o
	$(CC) $(CFLAGS) tests/test_iteration2.c $(BUILD_DIR)/logger.o -o $(BUILD_DIR)/test2
	@echo "Running test..."
	@echo ""
	./$(BUILD_DIR)/test2

test3:
	@echo "Building Iteration 3 test..."
	@mkdir -p $(BUILD_DIR) $(LOG_DIR)
	$(CC) $(CFLAGS) -c src/logger.c -o $(BUILD_DIR)/logger.o
	$(CC) $(CFLAGS) tests/test_iteration3.c $(BUILD_DIR)/logger.o -o $(BUILD_DIR)/test3
	@echo "Running test..."
	@echo ""
	./$(BUILD_DIR)/test3

test4:
	@echo "Building Iteration 4 test..."
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/logger.c -o $(BUILD_DIR)/logger.o
	$(CC) $(CFLAGS) tests/test_iteration4.c $(BUILD_DIR)/logger.o -o $(BUILD_DIR)/test4
	@echo "Running test..."
	@echo ""
	./$(BUILD_DIR)/test4

test5:
	@echo "Building Iteration 5 test..."
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/logger.c -o $(BUILD_DIR)/logger.o
	$(CC) $(CFLAGS) tests/test_iteration5.c $(BUILD_DIR)/logger.o -o $(BUILD_DIR)/test5
	@echo "Running test..."
	@echo ""
	./$(BUILD_DIR)/test5

# Help
help:
	@echo "Available targets:"
	@echo "  make          - Build final demo"
	@echo "  make run      - Build and run final demo"
	@echo "  make test1    - Run Iteration 1 test"
	@echo "  make test2    - Run Iteration 2 test"
	@echo "  make test3    - Run Iteration 3 test"
	@echo "  make test4    - Run Iteration 4 test"
	@echo "  make test5    - Run Iteration 5 test"
	@echo "  make clean    - Clean build directory"
	@echo "  make cleanall - Clean build and logs"
	@echo "  make help     - Show this help"
```

---

## 🎯 CÁCH SỬ DỤNG CODE CUỐI CÙNG

### Build và chạy:

```bash
# Build dự án
make

# Chạy demo
make run

# Hoặc kết hợp
make clean && make run
```

### Kết quả mong đợi:

**Console output:**
```
╔════════════════════════════════════════════════╗
║     LOGGER SYSTEM - FINAL DEMO                 ║
╚════════════════════════════════════════════════╝

=== Demo 1: All Log Levels ===
[2026-02-03 20:04:26] [EMERGENCY] [main.c:15] - System is unusable!
[2026-02-03 20:04:26] [ALERT] [main.c:16] - Action must be taken immediately!
[2026-02-03 20:04:26] [CRITICAL] [main.c:17] - Critical condition occurred
[2026-02-03 20:04:26] [ERROR] [main.c:18] - Error: File not found
[2026-02-03 20:04:26] [WARNING] [main.c:19] - Warning: Memory usage at 90%
[2026-02-03 20:04:26] [NOTICE] [main.c:20] - User admin logged in
[2026-02-03 20:04:26] [INFO] [main.c:21] - Application started successfully
[2026-02-03 20:04:26] [DEBUG] [main.c:22] - Debug: Variable x = 42

=== Demo 2: Format Strings ===
[2026-02-03 20:04:26] [INFO] [main.c:26] - User alice logged in from 192.168.1.100
[2026-02-03 20:04:26] [ERROR] [main.c:27] - Connection timeout after 30 seconds
[2026-02-03 20:04:26] [DEBUG] [main.c:28] - Processing 100 items, progress: 75.50%

=== Demo 3: Level Filtering ===
Setting level to WARNING...
[2026-02-03 20:04:26] [WARNING] [main.c:36] - This SHOULD appear
[2026-02-03 20:04:26] [ERROR] [main.c:37] - This SHOULD appear

=== Demo 4: File and Line Tracking ===
[2026-02-03 20:04:26] [INFO] [main.c:41] - Check the log - it shows file:line automatically!
[2026-02-03 20:04:26] [ERROR] [main.c:42] - Error on line 42

╔════════════════════════════════════════════════╗
║     DEMO COMPLETED                             ║
║     Check logs/app.log for file output         ║
╚════════════════════════════════════════════════╝
```

**File `logs/app.log`:**
```
[2026-02-03 20:04:26] [EMERGENCY] [main.c:15] - System is unusable!
[2026-02-03 20:04:26] [ALERT] [main.c:16] - Action must be taken immediately!
[2026-02-03 20:04:26] [CRITICAL] [main.c:17] - Critical condition occurred
[2026-02-03 20:04:26] [ERROR] [main.c:18] - Error: File not found
[2026-02-03 20:04:26] [WARNING] [main.c:19] - Warning: Memory usage at 90%
[2026-02-03 20:04:26] [NOTICE] [main.c:20] - User admin logged in
[2026-02-03 20:04:26] [INFO] [main.c:21] - Application started successfully
[2026-02-03 20:04:26] [DEBUG] [main.c:22] - Debug: Variable x = 42
[2026-02-03 20:04:26] [INFO] [main.c:26] - User alice logged in from 192.168.1.100
[2026-02-03 20:04:26] [ERROR] [main.c:27] - Connection timeout after 30 seconds
[2026-02-03 20:04:26] [DEBUG] [main.c:28] - Processing 100 items, progress: 75.50%
[2026-02-03 20:04:26] [WARNING] [main.c:36] - This SHOULD appear
[2026-02-03 20:04:26] [ERROR] [main.c:37] - This SHOULD appear
[2026-02-03 20:04:26] [INFO] [main.c:41] - Check the log - it shows file:line automatically!
[2026-02-03 20:04:26] [ERROR] [main.c:42] - Error on line 42
```

---

## ✅ TÍNH NĂNG ĐÃ HOÀN THÀNH

```
✅ 8 mức log levels (EMERGENCY → DEBUG)
✅ Timestamp tự động
✅ File và line number tự động
✅ Multi-target output (console + file)
✅ Level filtering
✅ Variadic functions (format strings)
✅ Convenience macros
✅ stderr cho critical logs
✅ stdout cho normal logs
✅ Safe string handling (snprintf, vsnprintf)
✅ Module encapsulation (static)
✅ Error handling
✅ Memory management (cleanup)
```

---

> 🎉 **Chúc mừng!** Bạn đã học được quy trình phát triển phần mềm chuyên nghiệp - Incremental Development với Test-Driven approach!
