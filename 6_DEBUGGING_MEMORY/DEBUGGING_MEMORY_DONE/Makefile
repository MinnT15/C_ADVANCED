# ==============================================================================
# Makefile — DEBUGGING_MEMORY
# Dự án: Thực hành gỡ lỗi bộ nhớ với GDB
# ==============================================================================

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -Iinclude -g
BUILD   = build
LOG_DIR = logs

# Source files
SRC_LIB  = src/memory_lab.c
SRC_MAIN = src/main.c

# Binary targets
TARGET_MAIN = $(BUILD)/memory_lab_main
TARGET_T1   = $(BUILD)/test1
TARGET_T2   = $(BUILD)/test2

# Màu terminal
GREEN  = \033[0;32m
YELLOW = \033[0;33m
CYAN   = \033[0;36m
RESET  = \033[0m

# ==============================================================================
# Default target
# ==============================================================================
.PHONY: all
all: $(TARGET_MAIN)
	@echo "$(GREEN)[BUILD OK] $(TARGET_MAIN)$(RESET)"

$(TARGET_MAIN): $(SRC_LIB) $(SRC_MAIN) include/memory_lab.h | $(BUILD)
	$(CC) $(CFLAGS) $(SRC_LIB) $(SRC_MAIN) -o $(TARGET_MAIN)

# ==============================================================================
# Run chương trình chính
# Cách dùng: make run ARGS=stack_overflow
#            make run ARGS=memory_leak
#            make run ARGS=out_of_memory
# ==============================================================================
ARGS ?= out_of_memory

.PHONY: run
run: $(TARGET_MAIN)
	@echo "$(CYAN)[RUN] $(TARGET_MAIN) $(ARGS)$(RESET)"
	./$(TARGET_MAIN) $(ARGS)

# ==============================================================================
# Chạy với GDB
# Cách dùng: make gdb ARGS=stack_overflow
# ==============================================================================
.PHONY: gdb
gdb: $(TARGET_MAIN)
	@echo "$(CYAN)[GDB] gdb $(TARGET_MAIN)$(RESET)"
	gdb -ex "run $(ARGS)" $(TARGET_MAIN)

# ==============================================================================
# Test Iteration 1: Stack Overflow module
# ==============================================================================
.PHONY: test1
test1: $(TARGET_T1)
	@echo "$(CYAN)[TEST1] Chạy Iteration 1 tests...$(RESET)"
	./$(TARGET_T1)

$(TARGET_T1): $(SRC_LIB) tests/test_iteration1.c include/memory_lab.h | $(BUILD)
	$(CC) $(CFLAGS) $(SRC_LIB) tests/test_iteration1.c -o $(TARGET_T1)

# ==============================================================================
# Test Iteration 2: Memory Leak + OOM module
# ==============================================================================
.PHONY: test2
test2: $(TARGET_T2)
	@echo "$(CYAN)[TEST2] Chạy Iteration 2 tests...$(RESET)"
	./$(TARGET_T2)

$(TARGET_T2): $(SRC_LIB) tests/test_iteration2.c include/memory_lab.h | $(BUILD)
	$(CC) $(CFLAGS) $(SRC_LIB) tests/test_iteration2.c -o $(TARGET_T2)

# ==============================================================================
# Chạy tất cả tests
# ==============================================================================
.PHONY: test
test: test1 test2
	@echo "$(GREEN)[DONE] Tất cả tests hoàn thành.$(RESET)"

# ==============================================================================
# Valgrind — kiểm tra memory leak
# Cách dùng: make valgrind ARGS=memory_leak
# ==============================================================================
.PHONY: valgrind
valgrind: $(TARGET_MAIN)
	@echo "$(CYAN)[VALGRIND] Chạy valgrind với ARGS=$(ARGS)$(RESET)"
	valgrind --leak-check=full --show-leak-kinds=all \
	         --track-origins=yes --verbose \
	         ./$(TARGET_MAIN) $(ARGS) 2>&1 | head -50

# ==============================================================================
# Tạo thư mục build
# ==============================================================================
$(BUILD):
	mkdir -p $(BUILD)
	mkdir -p $(LOG_DIR)

# ==============================================================================
# Clean
# ==============================================================================
.PHONY: clean
clean:
	rm -rf $(BUILD)/
	@echo "$(YELLOW)[CLEAN] Đã xóa $(BUILD)/$(RESET)"

.PHONY: cleanall
cleanall: clean
	rm -rf $(LOG_DIR)/
	@echo "$(YELLOW)[CLEANALL] Đã xóa $(BUILD)/ và $(LOG_DIR)/$(RESET)"

# ==============================================================================
# Help
# ==============================================================================
.PHONY: help
help:
	@echo "$(CYAN)==================================================$(RESET)"
	@echo "$(CYAN)  DEBUGGING_MEMORY — Makefile Help$(RESET)"
	@echo "$(CYAN)==================================================$(RESET)"
	@echo ""
	@echo "  $(GREEN)make all$(RESET)                    → Build chương trình chính"
	@echo "  $(GREEN)make run ARGS=<mode>$(RESET)        → Chạy với mode:"
	@echo "                                  stack_overflow"
	@echo "                                  memory_leak"
	@echo "                                  out_of_memory"
	@echo "  $(GREEN)make gdb ARGS=<mode>$(RESET)        → Chạy trong GDB"
	@echo "  $(GREEN)make test1$(RESET)                  → Test Iteration 1 (Stack Overflow)"
	@echo "  $(GREEN)make test2$(RESET)                  → Test Iteration 2 (Memory Leak+OOM)"
	@echo "  $(GREEN)make test$(RESET)                   → Chạy tất cả tests"
	@echo "  $(GREEN)make valgrind ARGS=<mode>$(RESET)   → Chạy với Valgrind"
	@echo "  $(GREEN)make clean$(RESET)                  → Xóa build/"
	@echo "  $(GREEN)make cleanall$(RESET)               → Xóa build/ và logs/"
	@echo ""
	@echo "  Ví dụ GDB commands sau khi $(GREEN)make gdb ARGS=stack_overflow$(RESET):"
	@echo "    (gdb) backtrace      ← Xem call stack"
	@echo "    (gdb) info frame     ← Xem frame hiện tại"
	@echo "    (gdb) frame 0        ← Nhảy đến frame lỗi"
