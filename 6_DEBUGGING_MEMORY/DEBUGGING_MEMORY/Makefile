# ==============================================================================
# Makefile — DEBUGGING_MEMORY (Bản luyện tập)
# Đọc STEP_BY_STEP_GUIDE.md để biết cách implement từng phần.
# ==============================================================================

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -Iinclude -g
BUILD   = build
LOG_DIR = logs

SRC_LIB  = src/memory_lab.c
SRC_MAIN = src/main.c

TARGET_MAIN = $(BUILD)/memory_lab_main
TARGET_T1   = $(BUILD)/test1
TARGET_T2   = $(BUILD)/test2

.PHONY: all run test1 test2 test clean cleanall help

all: $(TARGET_MAIN)

$(TARGET_MAIN): $(SRC_LIB) $(SRC_MAIN) include/memory_lab.h | $(BUILD)
	$(CC) $(CFLAGS) $(SRC_LIB) $(SRC_MAIN) -o $(TARGET_MAIN)

ARGS ?= out_of_memory
run: $(TARGET_MAIN)
	./$(TARGET_MAIN) $(ARGS)

test1: $(TARGET_T1)
	./$(TARGET_T1)

$(TARGET_T1): $(SRC_LIB) tests/test_iteration1.c include/memory_lab.h | $(BUILD)
	$(CC) $(CFLAGS) $(SRC_LIB) tests/test_iteration1.c -o $(TARGET_T1)

test2: $(TARGET_T2)
	./$(TARGET_T2)

$(TARGET_T2): $(SRC_LIB) tests/test_iteration2.c include/memory_lab.h | $(BUILD)
	$(CC) $(CFLAGS) $(SRC_LIB) tests/test_iteration2.c -o $(TARGET_T2)

test: test1 test2

$(BUILD):
	mkdir -p $(BUILD) $(LOG_DIR)

clean:
	rm -rf $(BUILD)/

cleanall: clean
	rm -rf $(LOG_DIR)/

help:
	@echo "Targets: all | run ARGS=<mode> | test1 | test2 | test | clean | cleanall"
	@echo "Modes:   stack_overflow | memory_leak | out_of_memory"
