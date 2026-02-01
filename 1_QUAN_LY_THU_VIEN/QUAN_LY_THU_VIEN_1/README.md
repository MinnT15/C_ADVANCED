# Library Management System

Ứng dụng quản lý thư viện đơn giản được viết bằng C, tuân thủ Clean Code và C Coding Convention.

## 📚 Tính Năng

### Quản Lý Sách
- ✅ Thêm sách mới vào thư viện
- ✅ Sửa thông tin sách
- ✅ Xóa sách khỏi thư viện
- ✅ Tìm kiếm sách theo tiêu đề, tác giả
- ✅ Hiển thị danh sách sách có sẵn

### Quản Lý Người Dùng
- ✅ Thêm người dùng mới
- ✅ Sửa thông tin người dùng
- ✅ Xóa người dùng
- ✅ Hiển thị thông tin người dùng và sách đã mượn

### Quản Lý Mượn/Trả Sách
- ✅ Cho phép người dùng mượn sách (nếu sách còn)
- ✅ Theo dõi số lượng sách đã mượn
- ✅ Trả sách về thư viện
- ✅ Giới hạn mỗi người tối đa 5 cuốn

### Xử Lý Lỗi
- ✅ Kiểm tra dữ liệu đầu vào hợp lệ
- ✅ Xử lý các trường hợp: sách hết, người dùng không tồn tại, ID trùng lặp...

## 🏗️ Cấu Trúc Dự Án

```
library_management/
├── src/              # Source files (.c)
│   ├── main.c
│   ├── book.c
│   ├── user.c
│   ├── borrow.c
│   ├── ui.c
│   └── utils.c
├── include/          # Header files (.h)
│   ├── common.h
│   ├── book.h
│   ├── user.h
│   ├── borrow.h
│   ├── ui.h
│   └── utils.h
├── obj/              # Object files (generated)
├── bin/              # Executable (generated)
├── data/             # Data files
│   ├── books.txt
│   └── users.txt
├── docs/             # Documentation
│   ├── implementation_plan.md
│   ├── git_master_guide.md
│   └── ...
├── Makefile          # Build configuration
└── README.md         # This file
```

## 🛠️ Yêu Cầu Hệ Thống

- **Compiler**: GCC (hỗ trợ C11)
- **Build Tool**: Make
- **OS**: Linux/Unix environment

## 📦 Cài Đặt

### 1. Clone repository

```bash
git clone https://github.com/MinnT15/library-management-c.git
cd library-management-c
```

### 2. Build dự án

```bash
make
```

Hoặc xem các lệnh có sẵn:

```bash
make help
```

## 🚀 Cách Sử Dụng

### Build và chạy chương trình

```bash
make run
```

### Chỉ build (không chạy)

```bash
make
```

### Xóa build artifacts

```bash
make clean
```

### Rebuild toàn bộ

```bash
make rebuild
```

## 📖 Hướng Dẫn Sử Dụng

### Menu Chính

Khi chạy chương trình, bạn sẽ thấy menu:

```
=== QUẢN LÝ THƯ VIỆN ===
1. Quản lý sách
2. Quản lý người dùng
3. Quản lý mượn/trả
4. Tìm kiếm
5. Thoát
```

### Quản Lý Sách

- **Thêm sách**: Nhập ID, tiêu đề, tác giả
- **Sửa sách**: Chọn ID sách cần sửa
- **Xóa sách**: Chọn ID sách cần xóa
- **Hiển thị**: Xem tất cả sách hoặc chỉ sách có sẵn

### Quản Lý Người Dùng

- **Thêm người dùng**: Nhập ID, tên
- **Sửa người dùng**: Chọn ID người dùng cần sửa
- **Xóa người dùng**: Chọn ID người dùng cần xóa
- **Hiển thị**: Xem thông tin người dùng và sách đã mượn

### Mượn/Trả Sách

- **Mượn sách**: Nhập ID người dùng và ID sách
- **Trả sách**: Nhập ID người dùng và ID sách cần trả

## 🎯 Giới Hạn

- **Số sách tối đa**: 100 cuốn
- **Số người dùng tối đa**: 50 người
- **Số sách mỗi người mượn**: Tối đa 5 cuốn

## 🧪 Testing

### Compile với warnings

```bash
gcc -Wall -Wextra -Werror -std=c11 -I./include src/*.c -o bin/library_app
```

### Kiểm tra memory leaks (với Valgrind)

```bash
valgrind --leak-check=full ./bin/library_app
```

## 📝 Quy Tắc Code

Dự án tuân thủ:

- **Clean Code principles**
- **C Coding Convention**
- **Naming convention**: `snake_case` cho functions/variables, `PascalCase` cho structs
- **Error handling**: Sử dụng error codes enum
- **Comments**: Giải thích "tại sao", không phải "cái gì"

## 🗂️ Data Structures

### Book

```c
typedef struct {
    int id;
    char title[100];
    char author[50];
    bool is_borrowed;
} Book;
```

### User

```c
typedef struct {
    int id;
    char name[50];
    int borrowed_books[5];
    int borrowed_count;
} User;
```

### Library

```c
typedef struct {
    Book books[100];
    int book_count;
    User users[50];
    int user_count;
} Library;
```

## 🔧 Error Codes

```c
typedef enum {
    SUCCESS = 0,
    ERROR_INVALID_INPUT = -1,
    ERROR_NOT_FOUND = -2,
    ERROR_ALREADY_EXISTS = -3,
    ERROR_FULL = -4,
    ERROR_BOOK_BORROWED = -5,
    ERROR_BOOK_NOT_BORROWED = -6,
    ERROR_MAX_BORROWED_REACHED = -7,
    ERROR_FILE_IO = -8,
    ERROR_NULL_POINTER = -9
} ErrorCode;
```

## 📚 Tài Liệu

Xem thêm trong thư mục `docs/`:

- [Implementation Plan](docs/implementation_plan.md) - Kế hoạch triển khai chi tiết
- [Git Master Guide](docs/git_master_guide.md) - Hướng dẫn Git từ Zero đến Hero
- [Common.h Guide](docs/huong_dan_viet_common_h.md) - Hướng dẫn viết common.h
- [Makefile Guide](docs/huong_dan_viet_makefile.md) - Hướng dẫn viết Makefile

## 🤝 Đóng Góp

Mọi đóng góp đều được chào đón! Hãy:

1. Fork dự án
2. Tạo branch mới (`git checkout -b feature/AmazingFeature`)
3. Commit thay đổi (`git commit -m 'Add some AmazingFeature'`)
4. Push lên branch (`git push origin feature/AmazingFeature`)
5. Tạo Pull Request

## 📄 License

Dự án này được phát hành dưới MIT License.

## 👤 Tác Giả

**Ngo Minh Tri**

- GitHub: [@MinnT15](https://github.com/MinnT15)
- Email: ngominhtri151002@gmail.com

## 🙏 Lời Cảm Ơn

- Cảm ơn các tài liệu về Clean Code và C Programming
- Cảm ơn cộng đồng C developers

---

**Ngày tạo**: 2026-01-17  
**Phiên bản**: 1.0.0  
**Trạng thái**: 🚧 Đang phát triển (Phase 1 hoàn thành)
