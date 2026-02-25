CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -Iinclude -g
BUILD_DIR = build
LOG_DIR   = logs
SRC       = src/filestat.c

.PHONY: all run test1 test2 clean cleanall help

## Mặc định: build chương trình chính
all: $(BUILD_DIR)/filestat

$(BUILD_DIR)/filestat: src/main.c $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ src/main.c $(SRC)

## Chạy chương trình chính với các ví dụ
run: $(BUILD_DIR)/filestat
	@echo "=== filestat Demo ==="
	@echo ""
	@echo "--- /etc/hostname ---"
	@./$(BUILD_DIR)/filestat /etc/hostname
	@echo ""
	@echo "--- /tmp ---"
	@./$(BUILD_DIR)/filestat /tmp
	@echo ""
	@echo "--- /etc (directory) ---"
	@./$(BUILD_DIR)/filestat /etc
	@echo ""
	@echo "--- Test symlink ---"
	@ln -sf /etc/hostname /tmp/filestat_test_link 2>/dev/null || true
	@./$(BUILD_DIR)/filestat /tmp/filestat_test_link
	@rm -f /tmp/filestat_test_link
	@echo ""
	@echo "--- Test usage (no args) ---"
	@./$(BUILD_DIR)/filestat || true
	@echo ""
	@echo "--- Test error (nonexistent) ---"
	@./$(BUILD_DIR)/filestat /nonexistent/path || true

## Iteration 1: test lstat + file type
test1: $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/test1 tests/test_iteration1.c $(SRC)
	@echo "--- Running test1 ---"
	@./$(BUILD_DIR)/test1

## Iteration 2: test size + last modified
test2: $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/test2 tests/test_iteration2.c $(SRC)
	@echo "--- Running test2 ---"
	@./$(BUILD_DIR)/test2

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(LOG_DIR):
	mkdir -p $(LOG_DIR)

## Xoá build/
clean:
	rm -rf $(BUILD_DIR)

## Xoá build/ và logs/
cleanall: clean
	rm -rf $(LOG_DIR)

## Hiển thị danh sách lệnh
help:
	@echo "Các lệnh có thể dùng:"
	@echo "  make all      - Build chương trình chính (./build/filestat)"
	@echo "  make run      - Build và chạy demo với các ví dụ"
	@echo "  make test1    - Build và chạy test iteration 1 (lstat + file type)"
	@echo "  make test2    - Build và chạy test iteration 2 (size + time)"
	@echo "  make clean    - Xoá thư mục build/"
	@echo "  make cleanall - Xoá build/ và logs/"
	@echo "  make help     - Hiển thị danh sách này"
