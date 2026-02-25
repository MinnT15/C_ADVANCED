CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -g
BUILD_DIR = build
LOG_DIR = logs

SOURCES = src/logger.c src/main.c
OBJECTS = $(BUILD_DIR)/logger.o $(BUILD_DIR)/main.o
TARGET = $(BUILD_DIR)/logger_demo

.PHONY: all clean run test1 test2 test3 test4 test5 help

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

run: $(TARGET) | $(LOG_DIR)
	@echo "Running logger demo..."
	@echo ""
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
	@echo "✓ Cleaned build directory"

cleanall: clean
	rm -rf $(LOG_DIR)

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

help:
	@echo "Available targets:"
	@echo "  make          - Build final demo"
	@echo "  make run      - Build and run final demo"
	@echo "  make test1-5  - Run Iteration tests"
	@echo "  make clean    - Clean build directory"
	@echo "  make cleanall - Clean build and logs"
	@echo "  make help     - Show this help"
