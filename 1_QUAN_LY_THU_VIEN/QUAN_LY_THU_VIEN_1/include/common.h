#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/*======================CONSTANTS=====================*/

/* Maximum limits */
#define MAX_BOOKS 100 //The Library is limited to 100 books
#define MAX_USERS 50
#define MAX_BORROWED 5

/* String lengths */
#define MAX_TITLE_LENGTH 100 //The Book's title is limited to 100 characters
#define MAX_AUTHOR_LENGTH 50
#define MAX_NAME_LENGTH 50

/* File paths */
#define BOOKS_FILE "data/books.txt"
#define USERS_FILE "data/users.txt"

/*======================ERROR CODES=====================*/

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

/*
Tại sao dùng số âm?
0 = SUCCESS (thành công)
Số âm = Lỗi
Dễ kiểm tra: if (result < 0) → có lỗi
*/

/*======================DATA STRUCTURES=====================*/

/**
 * @brief Book structure
 * Represents a book in the library
 */
typedef struct {
    int id;                              // Unique book ID
    char title[MAX_TITLE_LENGTH];        // Book title
    char author[MAX_AUTHOR_LENGTH];      // Author name
    bool is_borrowed;                    // Borrowed status: true = borrowed, false = available
} Book;

/**
 * @brief User structure
 * Represents a library user
 */
typedef struct {
    int id;                              // Unique user ID
    char name[MAX_NAME_LENGTH];          // User name
    int borrowed_books[MAX_BORROWED];    // Array of borrowed book IDs
    int borrowed_count;                  // Number of books currently borrowed
} User;

/**
 * @brief Library structure
 * Manages all books and users in the library system
 */
typedef struct {
    Book books[MAX_BOOKS];               // Array of all books
    int book_count;                      // Current number of books
    User users[MAX_USERS];               // Array of all users
    int user_count;                      // Current number of users
} Library;

#endif /* COMMON_H */