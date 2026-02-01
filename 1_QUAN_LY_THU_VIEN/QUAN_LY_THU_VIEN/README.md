# 📚 Library Management System

A simple library management system written in C, demonstrating modular programming and file handling.

## 🏗️ Project Structure

```
QUANLYTHUVIEN/
├── Book/              # Book management module
│   ├── book.h
│   └── book.c
├── Management/        # Library management module
│   ├── management.h
│   └── management.c
├── User/              # User management module
│   ├── user.h
│   └── user.c
├── Utils/             # Utility functions module
│   ├── utils.h
│   └── utils.c
├── main.c             # Main program entry point
├── Makefile           # Build configuration
└── library_data.txt   # Data storage file
```

## ✨ Features

- 📖 Add, edit, and delete books
- 👥 User management
- 🔍 Search and filter books
- 💾 Persistent data storage
- 🎯 Modular architecture

## 🚀 Getting Started

### Prerequisites

- GCC compiler
- Make utility (optional)

### Building the Project

Using Make:
```bash
make
```

Manual compilation:
```bash
gcc -Wall -Wextra -std=c11 -I. main.c Book/book.c Management/management.c User/user.c Utils/utils.c -o QUANLYTHUVIEN.exe
```

### Running the Program

```bash
make run
```

Or directly:
```bash
./bin/Debug/QUANLYTHUVIEN.exe
```

## 🧹 Cleaning Build Files

```bash
make clean
```

## 📝 Usage

Follow the on-screen menu to:
1. Add new books to the library
2. View all books
3. Search for specific books
4. Manage user accounts
5. Borrow and return books

## 🛠️ Development

### Modules

- **Book**: Handles book-related operations (CRUD)
- **Management**: Manages library operations and business logic
- **User**: Handles user authentication and management
- **Utils**: Provides utility functions (input validation, string handling, etc.)

## 📄 License

This project is created for educational purposes.

## 👨‍💻 Author

MinnT15

## 🔗 Repository

[https://github.com/MinnT15/C-Advance](https://github.com/MinnT15/C-Advance)
