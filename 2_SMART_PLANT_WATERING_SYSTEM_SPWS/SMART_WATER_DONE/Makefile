CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -Iinclude -g
LDFLAGS = 

SRC_DIR   = src
INC_DIR   = include
TEST_DIR  = tests
BUILD_DIR = build
LOG_DIR   = logs

# Files
MODULE_SRC = $(SRC_DIR)/spws_controller.c $(SRC_DIR)/hal_sensors.c $(SRC_DIR)/hal_actuators.c $(SRC_DIR)/hal_buttons.c
MAIN_SRC   = $(SRC_DIR)/main.c

.PHONY: all clean cleanall run test1 test2 test3 test4 help

all: $(BUILD_DIR)/spws

$(BUILD_DIR)/spws: $(MAIN_SRC) $(MODULE_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

run: all
	@echo "--- RUNNING MAIN APPLICATION ---"
	./$(BUILD_DIR)/spws

# Iteration Tests
test1: $(TEST_DIR)/test_iteration1.c $(SRC_DIR)/spws_controller.c
	@mkdir -p $(BUILD_DIR) $(LOG_DIR)
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/$@
	@./$(BUILD_DIR)/$@

test2: $(TEST_DIR)/test_iteration2.c $(SRC_DIR)/spws_controller.c $(SRC_DIR)/hal_sensors.c $(SRC_DIR)/hal_actuators.c
	@mkdir -p $(BUILD_DIR) $(LOG_DIR)
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/$@
	@./$(BUILD_DIR)/$@

test3: $(TEST_DIR)/test_iteration3.c $(MODULE_SRC)
	@mkdir -p $(BUILD_DIR) $(LOG_DIR)
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/$@
	@./$(BUILD_DIR)/$@

test4: $(TEST_DIR)/test_iteration4.c $(MODULE_SRC)
	@mkdir -p $(BUILD_DIR) $(LOG_DIR)
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/$@
	@./$(BUILD_DIR)/$@

clean:
	rm -rf $(BUILD_DIR)

cleanall: clean
	rm -rf $(LOG_DIR)

help:
	@echo "Available targets:"
	@echo "  all      : Build main application"
	@echo "  run      : Build and run main application"
	@echo "  testN    : Run test for iteration N (1-4)"
	@echo "  clean    : Remove build files"
	@echo "  cleanall : Remove build and log files"
