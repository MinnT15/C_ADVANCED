# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.
LDFLAGS = 

# Directories
SRC_DIR = .
BUILD_DIR = build
BIN_DIR = bin/Debug
OBJ_DIR = obj/Debug

# Source files
MAIN_SRC = main.c
BOOK_SRC = Book/book.c
MANAGEMENT_SRC = Management/management.c
USER_SRC = User/user.c
UTILS_SRC = Utils/utils.c

# Object files
MAIN_OBJ = $(OBJ_DIR)/main.o
BOOK_OBJ = $(OBJ_DIR)/Book/book.o
MANAGEMENT_OBJ = $(OBJ_DIR)/Management/management.o
USER_OBJ = $(OBJ_DIR)/User/user.o
UTILS_OBJ = $(OBJ_DIR)/Utils/utils.o

# All object files
OBJS = $(MAIN_OBJ) $(BOOK_OBJ) $(MANAGEMENT_OBJ) $(USER_OBJ) $(UTILS_OBJ)

# Target executable
TARGET = $(BIN_DIR)/QUANLYTHUVIEN.exe

# Default target
all: directories $(TARGET)

# Create necessary directories
directories:
	@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	@if not exist "$(OBJ_DIR)\Book" mkdir "$(OBJ_DIR)\Book"
	@if not exist "$(OBJ_DIR)\Management" mkdir "$(OBJ_DIR)\Management"
	@if not exist "$(OBJ_DIR)\User" mkdir "$(OBJ_DIR)\User"
	@if not exist "$(OBJ_DIR)\Utils" mkdir "$(OBJ_DIR)\Utils"
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)
	@echo Build complete: $(TARGET)

# Compile main.c
$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) $(CFLAGS) -c $(MAIN_SRC) -o $(MAIN_OBJ)

# Compile Book module
$(BOOK_OBJ): $(BOOK_SRC) Book/book.h
	$(CC) $(CFLAGS) -c $(BOOK_SRC) -o $(BOOK_OBJ)

# Compile Management module
$(MANAGEMENT_OBJ): $(MANAGEMENT_SRC) Management/management.h
	$(CC) $(CFLAGS) -c $(MANAGEMENT_SRC) -o $(MANAGEMENT_OBJ)

# Compile User module
$(USER_OBJ): $(USER_SRC) User/user.h
	$(CC) $(CFLAGS) -c $(USER_SRC) -o $(USER_OBJ)

# Compile Utils module
$(UTILS_OBJ): $(UTILS_SRC) Utils/utils.h
	$(CC) $(CFLAGS) -c $(UTILS_SRC) -o $(UTILS_OBJ)

# Clean build artifacts
clean:
	@if exist "$(OBJ_DIR)" rmdir /s /q "$(OBJ_DIR)"
	@if exist "$(BIN_DIR)" rmdir /s /q "$(BIN_DIR)"
	@if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)"
	@echo Clean complete

# Run the program
run: $(TARGET)
	@$(TARGET)

# Rebuild
rebuild: clean all

.PHONY: all clean run rebuild directories
