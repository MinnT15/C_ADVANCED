/**
 * @file book.h
 * @brief Book management functions
 * @author Minh Tri
 * @date 2026-01-20
 */

#ifndef BOOK_H
#define BOOK_H

#include "common.h"
#include "utils.h"

/* ========== CRUD OPERATIONS ========== */

/**
 * @brief Add a new book to the library
 * @param lib Pointer to library
 * @param book Book to add
 * @return ErrorCode (SUCCESS or error)
 */
ErrorCode add_book(Library *lib, Book book);

/**
 * @brief Find book by ID
 * @param lib Pointer to library
 * @param id Book ID to find
 * @return Pointer to book if found, NULL otherwise
 */
Book* find_book_by_id(Library *lib, int id);

/**
 * @brief Find book index by ID (helper function)
 * @param lib Pointer to library
 * @param id Book ID to find
 * @return Index if found, -1 otherwise
 */
int find_book_index_by_id(Library *lib, int id);

/**
 * @brief Update book information
 * @param lib Pointer to library
 * @param id Book ID to update
 * @param new_book New book information
 * @return ErrorCode (SUCCESS or error)
 */
ErrorCode update_book(Library *lib, int id, Book new_book);

/**
 * @brief Delete book from library
 * @param lib Pointer to library
 * @param id Book ID to delete
 * @return ErrorCode (SUCCESS or error)
 */
ErrorCode delete_book(Library *lib, int id);

/* ========== SEARCH FUNCTIONS ========== */

/**
 * @brief Search books by title (partial match)
 * @param lib Pointer to library
 * @param title Title to search for
 */
void search_books_by_title(Library *lib, const char *title);

/**
 * @brief Search books by author (partial match)
 * @param lib Pointer to library
 * @param author Author to search for
 */
void search_books_by_author(Library *lib, const char *author);

/* ========== DISPLAY FUNCTIONS ========== */

/**
 * @brief Display single book information
 * @param book Pointer to book
 */
void display_book(const Book *book);

/**
 * @brief Display all books in library
 * @param lib Pointer to library
 */
void display_all_books(Library *lib);

/* ========== HELPER FUNCTIONS ========== */

/**
 * @brief Get total number of books
 * @param lib Pointer to library
 * @return Number of books
 */
int get_book_count(Library *lib);

#endif /* BOOK_H */
