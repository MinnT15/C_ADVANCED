/**
 * @file utils.h
 * @brief Utility functions for Library Management System
 * @author Your Name
 * @date 2026-01-18
 * 
 * This module provides:
 * - Input validation functions
 * - Safe input functions
 * - String utilities
 * - Error handling functions
 */

#ifndef UTILS_H
#define UTILS_H

#include "common.h"

/* ========== VALIDATION FUNCTIONS ========== */

/**
 * @brief Validate if ID is valid (must be > 0)
 * @param id The ID to validate
 * @return true if valid, false otherwise
 */
bool validate_id(int id);

/**
 * @brief Validate if string is not empty and not NULL
 * @param str The string to validate
 * @return true if valid, false otherwise
 */
bool validate_string(const char *str);

/**
 * @brief Validate if string length is within limit
 * @param str The string to validate
 * @param max_len Maximum allowed length
 * @return true if valid, false otherwise
 */
bool validate_string_length(const char *str, int max_len);

/* ========== INPUT FUNCTIONS ========== */

/**
 * @brief Clear input buffer (stdin)
 * Removes all remaining characters from stdin until newline
 */
void clear_input_buffer(void);

/**
 * @brief Get integer input from user with validation
 * @param prompt Message to display to user
 * @return The integer entered by user
 * 
 * This function will keep asking until valid integer is entered
 */
int get_integer_input(const char *prompt);

/**
 * @brief Get string input from user with validation
 * @param prompt Message to display to user
 * @param buffer Buffer to store the input
 * @param max_len Maximum length of input (including null terminator)
 * 
 * This function automatically trims whitespace and validates length
 */
void get_string_input(const char *prompt, char *buffer, int max_len);

/* ========== STRING UTILITIES ========== */

/**
 * @brief Remove leading and trailing whitespace from string
 * @param str The string to trim (modified in-place)
 */
void trim_string(char *str);

/**
 * @brief Safely copy string with size limit
 * @param dest Destination buffer
 * @param src Source string
 * @param dest_size Size of destination buffer
 * 
 * Ensures null-termination and prevents buffer overflow
 */
void safe_string_copy(char *dest, const char *src, size_t dest_size);

/* ========== ERROR HANDLING ========== */

/**
 * @brief Get error message string from error code
 * @param error The error code
 * @return Error message string
 */
const char* get_error_message(ErrorCode error);

/**
 * @brief Print formatted error message
 * @param error The error code to print
 */
void print_error(ErrorCode error);

#endif /* UTILS_H */
