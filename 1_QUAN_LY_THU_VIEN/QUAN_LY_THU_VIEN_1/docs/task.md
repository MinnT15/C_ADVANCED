# Task: Xây Dựng Ứng Dụng Quản Lý Thư Viện

## Giai đoạn 1: Thiết lập cấu trúc dự án
- [x] Tạo cấu trúc thư mục
  - [x] Tạo thư mục gốc `library_management`
  - [x] Tạo thư mục `src/`
  - [x] Tạo thư mục `include/`
  - [x] Tạo thư mục `data/`
- [x] Tạo file `common.h` với constants và error codes
  - [x] Header guards và includes
  - [x] Constants (MAX_BOOKS, MAX_USERS, etc.)
  - [x] Error codes enum
  - [x] Data structures (Book, User, Library)
- [x] Tạo `Makefile`
- [x] Tạo `README.md`

## Giai đoạn 2: Module Utils (Tiện ích) ✅
- [x] Tạo file `include/utils.h`
- [x] Tạo file `src/utils.c`
- [x] Implement validation functions (validate_id, validate_string, validate_string_length)
- [x] Implement input functions (clear_input_buffer, get_integer_input, get_string_input)
- [x] Implement string utilities (trim_string, safe_string_copy)
- [x] Implement error handling (get_error_message, print_error)
- [x] Test và compile thành công
- [x] Commit và push lên GitHub

## Giai đoạn 3: Module Book ✅
- [x] Tạo `book.h` và `book.c`
- [x] Implement CRUD operations (add, find, update, delete)
- [x] Implement search functions (by title, by author)
- [x] Implement display functions (single book, all books)
- [x] Implement helper functions (get_book_count, find_book_index_by_id)
- [x] Fix error handling consistency
- [x] Fix compilation errors (delete_book, search functions)
- [x] Test và compile thành công (298 dòng, 10 hàm)

## Giai đoạn 4: Module User
- [ ] Tạo `user.h` và `user.c`
- [ ] Implement CRUD operations
- [ ] Implement display functions

## Giai đoạn 5: Module Borrow
- [ ] Tạo `borrow.h` và `borrow.c`
- [ ] Implement borrow_book()
- [ ] Implement return_book()
- [ ] Implement helper functions

## Giai đoạn 6: Module UI
- [ ] Tạo `ui.h` và `ui.c`
- [ ] Implement menu system
- [ ] Implement screen utilities

## Giai đoạn 7: File I/O (Optional)
- [ ] Implement save functions
- [ ] Implement load functions

## Giai đoạn 8: Main Program
- [ ] Tạo `main.c`
- [ ] Integrate all modules
- [ ] Implement main loop

## Giai đoạn 9: Testing
- [ ] Unit tests
- [ ] Integration tests
- [ ] Edge case tests

## Giai đoạn 10: Clean Code & Documentation
- [ ] Code review
- [ ] Refactoring
- [ ] Documentation
