/**
 * @file book.c
 * @brief Implementation of book management functions
 * @author Minh Tri
 * @date 2026-01-20
 */

#include "book.h"

/* ========== HELPER FUNCTIONS ========== */

/**
 * @brief Get total number of books in library
 */
int get_book_count(Library *lib) {
    // Kiểm tra library pointer
    if (lib == NULL) {
        return 0;
    }
    
    // Return số lượng sách
    return lib->book_count;
}

/**
 * @brief Find book index by ID (helper function)
 */
int find_book_index_by_id(Library *lib, int id) {
    // Bước 1: Validate library pointer
    if (lib == NULL) {
        return -1;
    }
    
    // Bước 2: Validate ID
    if (!validate_id(id)) {
        return -1;
    }
    
    // Bước 3: Tìm kiếm trong mảng books
    for (int i = 0; i < lib->book_count; i++) {
        if (lib->books[i].id == id) {
            return i;  // Tìm thấy, return index
        }
    }
    
    // Bước 4: Không tìm thấy
    return -1;
}

/* ========== DISPLAY FUNCTIONS ========== */

/**
 * @brief Display single book information with formatted output
 */
void display_book(const Book *book) {
    // Kiểm tra NULL pointer
    if (book == NULL) {
        print_error(ERROR_NULL_POINTER);
        return;
    }

    // In thông tin sách
    printf("┌─────────────────────────────────────────┐\n");
    printf("│ ID: %-3d                                │\n", book->id);
    printf("│ Title: %-32s │\n", book->title);
    printf("│ Author: %-31s │\n", book->author);
    printf("│ Status: %-31s │\n", 
           book->is_borrowed ? "Borrowed" : "Available");
    printf("└─────────────────────────────────────────┘\n");
}

/**
 * @brief Display all books in library
 */
void display_all_books(Library *lib) {
    // Bước 1: Validate library pointer
    if (lib == NULL) {
        print_error(ERROR_NULL_POINTER);
        return;
    }

    // Bước 2: Validate book count
    if (lib->book_count == 0) {
        printf("\nLibrary is empty!\n\n");
        return;
    }

    // Bước 3: Hiển thị header
    printf("\n LIBRARY BOOKS (Total : %d)\n", lib->book_count);
    printf("=============================================\n\n");

    // Bước 4: Hiển thị từng sách
    for (int i = 0; i < lib->book_count; i++) {
        display_book(&lib->books[i]);
        printf("\n");
    }
}

/* ========== CRUD OPERATIONS ========== */
/**
 * @brief Find book by ID
 * @return Pointer to book if found, NULL otherwise
 */
Book* find_book_by_id(Library *lib, int id) {
    // Bước 1: Validate library pointer
    if (lib == NULL) {
        return NULL;
    }

    // Bước 2: Validate ID
    if (!validate_id(id)) {
        return NULL;
    }

    // Bước 3: Tìm kiếm sách
    for (int i = 0; i < lib->book_count; i++) {
        if (lib->books[i].id == id) {
            return &lib->books[i];
        }
    }
    // Bước 4: Không tìm thấy
    return NULL;
}
/**
 * @brief Add a new book to the library
 * Validates all inputs and checks for duplicates
 */
ErrorCode add_book(Library *lib, Book book) {
    // Bước 1: Validate library pointer
    if (lib == NULL) {
        return ERROR_NULL_POINTER;
    }

    // Bước 2: Validate book ID
    if (!validate_id(book.id)) {
        return ERROR_INVALID_INPUT;
    }

    // Bước 3: Validate book title
    if (!validate_string(book.title)) {
        return ERROR_INVALID_INPUT;
    }

    // Bước 4: Validate book author
    if (!validate_string(book.author)) {
        return ERROR_INVALID_INPUT;
    }

    if (!validate_string_length(book.author, MAX_AUTHOR_LENGTH)) {
        return ERROR_INVALID_INPUT;
    }

    // Bước 4.5: Validate title length
    if (!validate_string_length(book.title, MAX_TITLE_LENGTH)) {
        return ERROR_INVALID_INPUT;
    }

    // Bước 5: Kiểm tra thư viện đầy
    if (lib->book_count >= MAX_BOOKS) {
        return ERROR_FULL;
    }

    // Bước 6: Kiểm tra ID đã tồn tại
    if (find_book_by_id(lib, book.id) != NULL) {
        return ERROR_ALREADY_EXISTS;
    }

    // Bước 7: Thêm sách vào thư viện
    lib->books[lib->book_count] = book;
    lib->book_count++;

    return SUCCESS;
}
/**
 * @brief Update book information
 * Keeps ID and borrowed status unchanged
 */
ErrorCode update_book( Library *lib, int id, Book new_book) {
    // Bước 1: Tìm sách theo ID
    Book *book = find_book_by_id(lib, id);
    if (book == NULL) {
        return ERROR_NOT_FOUND;
    }
    // Bước 2: Validate  new book title
    if (!validate_string(new_book.title) ||
        !validate_string_length(new_book.title, MAX_TITLE_LENGTH)){
            return ERROR_INVALID_INPUT;  
    }

    // Bước 3: Validate new book author
    if (!validate_string(new_book.author) ||
        !validate_string_length(new_book.author, MAX_AUTHOR_LENGTH)){
            return ERROR_INVALID_INPUT;  
    }

    // Bước 4: Cập nhật thông tin sách
    safe_string_copy(book->title, new_book.title, MAX_TITLE_LENGTH);
    safe_string_copy(book->author, new_book.author, MAX_AUTHOR_LENGTH);

    return SUCCESS;
}
/**
 * @brief Delete book from library
 * Cannot delete borrowed books, shifts remaining books
 */
ErrorCode delete_book(Library *lib, int id) {
    // Bước 1: Tìm index của sách
    int index = find_book_index_by_id(lib, id);
    if (index == -1) {
        return ERROR_NOT_FOUND;
    }

    // Bước 2: Kiểm tra sách có đang được mượn không
    if (lib->books[index].is_borrowed) {
        return ERROR_BOOK_BORROWED;
    }

    // Bước 3: Dịch các sách phía sau lên
    for (int i = index; i < lib->book_count - 1; i++) {
        lib->books[i] = lib->books[i + 1];
    }

    // Bước 4: Giảm book_count
    lib->book_count--;

    return SUCCESS;
 }
/* ========== SEARCH FUNCTIONS ========== */

/**
 * @brief Search books by title (partial match, case-sensitive)
 * Uses strstr() for substring matching
 */
void search_books_by_title(Library *lib, const char *title) {
    // Bước 1: Validate library pointer
    if (lib == NULL || !validate_string(title)) {
        print_error(ERROR_INVALID_INPUT);
        return;
    }
    
    int found_count = 0;

    // Bước 2: Hiển thị header
    printf("\n SEARCHING FOR BOOK TITLE: \"%s\"\n", title);
    printf("============================================\n\n");

    // Bước 3: Tìm kiếm trong tất cả sách
    for (int i = 0; i < lib->book_count; i++) {
        // Sử dụng strstr() để tìm chuỗi con (partial match)
        if (strstr(lib->books[i].title, title) != NULL) {
            display_book(&lib->books[i]);
            printf("\n");
            found_count++;
        }
    }

    // Bước 4: Hiển thị kết quả
    if (found_count == 0) {
        printf("No books found with title containing \"%s\"\n", title);
    } else {
        printf("Found %d books with title containing \"%s\"\n", found_count, title);
    }
    
}
/**
 * @brief Search books by author (partial match, case-sensitive)
 * Uses strstr() for substring matching
 */
void search_books_by_author(Library *lib, const char *author) {
    // Validate input
    if (lib == NULL || !validate_string(author)) {
        print_error(ERROR_INVALID_INPUT);
        return;
    }

    int found_count = 0;

    printf("\n SEARCHING FOR BOOK AUTHOR: \"%s\"\n", author);
    printf("============================================\n\n");

    // Tìm kiếm
    for (int i = 0; i < lib->book_count; i++) {
        if (strstr(lib->books[i].author, author) != NULL) {
            display_book(&lib->books[i]);
            printf("\n");
            found_count++;
        }
    }

    // Hiển thị kết quả
    if (found_count == 0) {
        printf("No books found with author containing \"%s\"\n", author);
    } else {
        printf("Found %d books with author containing \"%s\"\n", found_count, author);
    }
}


