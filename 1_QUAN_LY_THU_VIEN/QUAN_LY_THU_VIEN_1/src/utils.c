/**
 * @file utils.c
 * @brief Implementation of utility functions
 * @author Minh Tri
 * @date 2026-01-18
 */

 #include "utils.h"

/* ========== VALIDATION FUNCTIONS ========== */

/**
 * @brief Validate if ID is valid (must be > 0)
 */
bool validate_id(int id){
    return id > 0;
}
/**
 * @brief Validate if string is not empty and not NULL
 */
 bool validate_string(const char *str){
    if (str == NULL) {
        return false;
    }
    if (str[0] == '\0') {
        return false;
    }
    for (int i = 0; str[i] !='\0'; i++) {
        if(!isspace((unsigned char)str[i])){
            return true;
        }
    }
    return false;
}

/**
 * @brief Validate if string length is within limit
 */
bool validate_string_length(const char *str, int max_len) {
    if (str == NULL) {
        return false;
    }

    return strlen(str) <= (size_t)max_len;
}
/* ========== INPUT FUNCTIONS ========== */

/**
 * @brief Clear input buffer (delete /n and EOF in buffer) (stdin) 
 */
void clear_input_buffer(void) {
    int c;
    while (( c = getchar()) != '\n' && c != EOF);
}
/**
 * @brief Get integer input from user with validation
 */
int get_integer_input(const char *prompt) {
    int value;
    int result;

    while (1) {
        printf("%s", prompt);
        result = scanf("%d", &value);
        
        if (result == 1) {
            clear_input_buffer();
            return value;
        } else {
            printf("Invalid input. Please enter a valid integer.\n");
            clear_input_buffer();
        }
    }
}
/**
 * @brief Get string input from user with validation
 */
void get_string_input(const char *prompt, char *buffer, int max_len) {
    printf("%s", prompt);
    // Đọc chuỗi bằng fgets
    if (fgets(buffer, max_len, stdin) == NULL) {  
        return;
    }
    // Xóa '\n' ở cuối
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') { 
        buffer[len - 1] = '\0';
    }
    // Trim whitespace
    trim_string(buffer);
}
/* ========== STRING UTILITIES ========== */

/**
 * @brief Remove leading and trailing whitespace
 */
 void trim_string(char *str) {
    if (str == NULL) return;
    
    //  Bước 1: Xoá trailing whitespace
    int len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        len--;
    }
    str[len] = '\0';

    // Bước 2: Xoá leading whitespace
    int start = 0;
    while (str[start] != '\0' && isspace((unsigned char)str[start])) {
        start++;
    }

    // Bước 3: Dịch chuỗi về đầu
    if (start > 0) {
        int i = 0;
        while (str[start] != '\0') {
            str[i++] = str[start++];
        }
        str[i] = '\0';
    }
 }

/**
 * @brief Safely copy string with size limit (prevent buffer overflow and ensure null termination)
 */
void safe_string_copy(char *dest, const char *src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return;
    }

    // Copy tối đa dest_size - 1 ký tự để chừa chỗ cho '\0'
    strncpy(dest, src, dest_size - 1);
    // Đảm bảo chuỗi luôn kết thúc bằng '\0'
    dest[dest_size - 1] = '\0';
}

/* ========== ERROR HANDLING ========== */

/**
 * @brief Get error message from error code
 */
const char* get_error_message(ErrorCode error) {
    switch (error) {
        case SUCCESS: return "Success";
        case ERROR_INVALID_INPUT: return "Invalid input";
        case ERROR_NOT_FOUND: return "Not found";
        case ERROR_ALREADY_EXISTS: return "Already exists";
        case ERROR_FULL: return "Storage full";
        case ERROR_BOOK_BORROWED: return "Book is currently borrowed";
        case ERROR_BOOK_NOT_BORROWED: return "Book is not currently borrowed";
        case ERROR_MAX_BORROWED_REACHED: return "Maximum number of borrowed books reached";
        case ERROR_FILE_IO: return "File I/O error";
        case ERROR_NULL_POINTER: return "NULL pointer error";
        default: return "Unknown error";
    }
}

/**
 * @brief Print formatted error message
 */
void print_error(ErrorCode error) {
    if (error == SUCCESS) {
        printf("%s\n", get_error_message(error));
    } else {
        printf("Error: %s\n", get_error_message(error));
    }
}