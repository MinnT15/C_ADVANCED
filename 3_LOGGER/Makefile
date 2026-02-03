CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -g
BUILD_DIR = build
LOG_DIR = logs

SOURCES = src/logger.c src/main.c
OBJECTS = $(BUILD_DIR)/logger.o $(BUILD_DIR)/main.o
TARGET = $(BUILD_DIR)/logger_demo

.PHONY: all clean run test1 test2 test3 test4 test5 cleanall

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

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
	@echo "✓ Build artifacts cleaned"

# Clean everything (including logs)
cleanall: clean
	rm -rf $(LOG_DIR)
	@echo "✓ All artifacts cleaned"

# Iteration 1 test
test1:
	@mkdir -p $(BUILD_DIR)
	@echo "Building Iteration 1 test..."
	$(CC) $(CFLAGS) -c src/logger.c -o $(BUILD_DIR)/logger.o
	$(CC) $(CFLAGS) tests/test_iteration1.c $(BUILD_DIR)/logger.o -o $(BUILD_DIR)/test1
	@echo "Running test..."
	@echo ""
	./$(BUILD_DIR)/test1

# Iteration 2 test
test2:
	@mkdir -p $(BUILD_DIR)
	@echo "Building Iteration 2 test..."
	$(CC) $(CFLAGS) -c src/logger.c -o $(BUILD_DIR)/logger.o
	$(CC) $(CFLAGS) tests/test_iteration2.c $(BUILD_DIR)/logger.o -o $(BUILD_DIR)/test2
	@echo "Running test..."
	@echo ""
	./$(BUILD_DIR)/test2

# Iteration 3 test
test3:
	@mkdir -p $(BUILD_DIR) $(LOG_DIR)
	@echo "Building Iteration 3 test..."
	$(CC) $(CFLAGS) -c src/logger.c -o $(BUILD_DIR)/logger.o
	$(CC) $(CFLAGS) tests/test_iteration3.c $(BUILD_DIR)/logger.o -o $(BUILD_DIR)/test3
	@echo "Running test..."
	@echo ""
	./$(BUILD_DIR)/test3
	@echo ""
	@echo "File output:"
	@cat logs/test_iter3.log 2>/dev/null || echo "(File not created yet)"

# Iteration 4 test
test4:
	@mkdir -p $(BUILD_DIR)
	@echo "Building Iteration 4 test..."
	$(CC) $(CFLAGS) -c src/logger.c -o $(BUILD_DIR)/logger.o
	$(CC) $(CFLAGS) tests/test_iteration4.c $(BUILD_DIR)/logger.o -o $(BUILD_DIR)/test4
	@echo "Running test..."
	@echo ""
	./$(BUILD_DIR)/test4

# Iteration 5 test
test5:
	@mkdir -p $(BUILD_DIR)
	@echo "Building Iteration 5 test..."
	$(CC) $(CFLAGS) -c src/logger.c -o $(BUILD_DIR)/logger.o
	$(CC) $(CFLAGS) tests/test_iteration5.c $(BUILD_DIR)/logger.o -o $(BUILD_DIR)/test5
	@echo "Running test..."
	@echo ""
	./$(BUILD_DIR)/test5

# Help
help:
	@echo "Logger System - Makefile"
	@echo ""
	@echo "Available targets:"
	@echo "  make          - Build the final demo"
	@echo "  make run      - Build and run the final demo"
	@echo "  make test1    - Build and run Iteration 1 test"
	@echo "  make test2    - Build and run Iteration 2 test"
	@echo "  make test3    - Build and run Iteration 3 test"
	@echo "  make test4    - Build and run Iteration 4 test"
	@echo "  make test5    - Build and run Iteration 5 test"
	@echo "  make clean    - Remove build artifacts"
	@echo "  make cleanall - Remove build artifacts and logs"
	@echo "  make help     - Show this help message"
