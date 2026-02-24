CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -g
BUILD_DIR = build
LOG_DIR = logs

SOURCES = src/led_rgb.c src/main.c
OBJECTS = $(BUILD_DIR)/led_rgb.o $(BUILD_DIR)/main.o
TARGET = $(BUILD_DIR)/led_rgb_demo

.PHONY: all clean run test1 test2 test3 test4 test5 help

# Build final demo
all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BUILD_DIR)
	$(CC) $(OBJECTS) -o $(TARGET)
	@echo "✓ Build successful: $(TARGET)"

$(BUILD_DIR)/led_rgb.o: src/led_rgb.c include/led_rgb.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/led_rgb.c -o $(BUILD_DIR)/led_rgb.o

$(BUILD_DIR)/main.o: src/main.c include/led_rgb.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/main.c -o $(BUILD_DIR)/main.o

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(LOG_DIR):
	mkdir -p $(LOG_DIR)

# Run final demo
run: $(TARGET)
	@echo "Running LED RGB demo..."
	@echo ""
	./$(TARGET)

# Clean
clean:
	rm -rf $(BUILD_DIR)
	@echo "✓ Cleaned build directory"

cleanall: clean
	rm -rf $(LOG_DIR)
	@echo "✓ Cleaned all"

# Individual iteration tests
test1:
	@echo "Building Iteration 1 test..."
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/led_rgb.c -o $(BUILD_DIR)/led_rgb.o
	$(CC) $(CFLAGS) tests/test_iteration1.c $(BUILD_DIR)/led_rgb.o -o $(BUILD_DIR)/test1
	@echo "Running test..."
	@echo ""
	./$(BUILD_DIR)/test1

test2:
	@echo "Building Iteration 2 test..."
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/led_rgb.c -o $(BUILD_DIR)/led_rgb.o
	$(CC) $(CFLAGS) tests/test_iteration2.c $(BUILD_DIR)/led_rgb.o -o $(BUILD_DIR)/test2
	@echo "Running test..."
	@echo ""
	./$(BUILD_DIR)/test2

test3:
	@echo "Building Iteration 3 test..."
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/led_rgb.c -o $(BUILD_DIR)/led_rgb.o
	$(CC) $(CFLAGS) tests/test_iteration3.c $(BUILD_DIR)/led_rgb.o -o $(BUILD_DIR)/test3
	@echo "Running test..."
	@echo ""
	./$(BUILD_DIR)/test3

test4:
	@echo "Building Iteration 4 test..."
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/led_rgb.c -o $(BUILD_DIR)/led_rgb.o
	$(CC) $(CFLAGS) tests/test_iteration4.c $(BUILD_DIR)/led_rgb.o -o $(BUILD_DIR)/test4
	@echo "Running test..."
	@echo ""
	./$(BUILD_DIR)/test4

test5:
	@echo "Building Iteration 5 test..."
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/led_rgb.c -o $(BUILD_DIR)/led_rgb.o
	$(CC) $(CFLAGS) tests/test_iteration5.c $(BUILD_DIR)/led_rgb.o -o $(BUILD_DIR)/test5
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
