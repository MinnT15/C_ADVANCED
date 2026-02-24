CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -Iinclude -g
BUILD   = build
LOG_DIR = logs

SRC     = src/task_queue.c
MAIN    = src/main.c

# ── Targets ──────────────────────────────────────────────────────────
.PHONY: all run test1 test2 test3 clean cleanall help

all: $(BUILD)/main

$(BUILD)/main: $(SRC) $(MAIN) | $(BUILD)
	$(CC) $(CFLAGS) $(SRC) $(MAIN) -o $@

run: $(BUILD)/main
	@echo "=============================="
	@echo " TASK QUEUE SYSTEM — Demo"
	@echo "=============================="
	@./$(BUILD)/main

test1: $(SRC) tests/test_iteration1.c | $(BUILD) $(LOG_DIR)
	$(CC) $(CFLAGS) $(SRC) tests/test_iteration1.c -o $(BUILD)/test1
	@echo "=============================="
	@echo " TEST 1: Task Queue (Singly Linked List)"
	@echo "=============================="
	@./$(BUILD)/test1 2>&1 | tee $(LOG_DIR)/test1.log
	@echo ""

test2: $(SRC) tests/test_iteration2.c | $(BUILD) $(LOG_DIR)
	$(CC) $(CFLAGS) $(SRC) tests/test_iteration2.c -o $(BUILD)/test2
	@echo "=============================="
	@echo " TEST 2: Activity Log (Doubly Linked List)"
	@echo "=============================="
	@./$(BUILD)/test2 2>&1 | tee $(LOG_DIR)/test2.log
	@echo ""

test3: $(SRC) tests/test_iteration3.c | $(BUILD) $(LOG_DIR)
	$(CC) $(CFLAGS) $(SRC) tests/test_iteration3.c -o $(BUILD)/test3
	@echo "=============================="
	@echo " TEST 3: Integration"
	@echo "=============================="
	@./$(BUILD)/test3 2>&1 | tee $(LOG_DIR)/test3.log
	@echo ""

$(BUILD):
	@mkdir -p $(BUILD)

$(LOG_DIR):
	@mkdir -p $(LOG_DIR)

clean:
	rm -rf $(BUILD)

cleanall:
	rm -rf $(BUILD) $(LOG_DIR)

help:
	@echo "Targets:"
	@echo "  make all    - Build chuong trinh chinh"
	@echo "  make run    - Build va chay main.c"
	@echo "  make test1  - Test IT-1: Task Queue FIFO"
	@echo "  make test2  - Test IT-2: Activity Log"
	@echo "  make test3  - Test IT-3: Integration"
	@echo "  make clean  - Xoa build/"
	@echo "  make cleanall - Xoa build/ va logs/"
