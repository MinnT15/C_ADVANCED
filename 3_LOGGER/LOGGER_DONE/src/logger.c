#include "logger.h"
#include <time.h>
#include <string.h>

// Logger state (typedef struct)
typedef struct {
    LogLevel min_level;
    FILE *log_file;
    bool initialized;
} Logger;

// Global static state
static Logger g_logger = { LOG_INFO, NULL, false };

// Helper: Get timestamp
static void get_timestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

// Helper: Convert level to string
static const char* get_level_string(LogLevel level) {
    static const char *level_strings[] = {
        "EMERGENCY", "ALERT", "CRITICAL", "ERROR",
        "WARNING", "NOTICE", "INFO", "DEBUG"
    };
    
    if (level >= 0 && level <= LOG_DEBUG) {
        return level_strings[level];
    }
    return "UNKNOWN";
}

// Helper: Check if should log
static bool should_log(LogLevel level) {
    return level <= g_logger.min_level;
}

// Helper: Get console stream (stderr for critical, stdout for others)
static FILE* get_console_stream(LogLevel level) {
    return (level <= LOG_CRITICAL) ? stderr : stdout;
}

// Initialize logger
int logger_init(LogLevel min_level, const char *log_filename) {
    // Cleanup if already initialized
    if (g_logger.initialized) {
        logger_cleanup();
    }
    
    g_logger.min_level = min_level;
    
    // Open log file if specified
    if (log_filename != NULL) {
        g_logger.log_file = fopen(log_filename, "a");
        if (g_logger.log_file == NULL) {
            fprintf(stderr, "Error: Cannot open log file: %s\n", log_filename);
            return -1;
        }
    }
    
    g_logger.initialized = true;
    return 0;
}

// Set minimum log level
void logger_set_level(LogLevel min_level) {
    g_logger.min_level = min_level;
}

// Cleanup logger
void logger_cleanup(void) {
    if (g_logger.log_file != NULL) {
        fclose(g_logger.log_file);
        g_logger.log_file = NULL;
    }
    g_logger.initialized = false;
}

// Main logging function (variadic)
void logger_log(LogLevel level, const char *file, int line,
                const char *format, ...) {
    // Filter by level
    if (!should_log(level)) {
        return;
    }
    
    // Get timestamp
    char timestamp[64];
    get_timestamp(timestamp, sizeof(timestamp));
    
    // Get level string
    const char *level_str = get_level_string(level);
    
    // Get basename of file
    const char *filename = strrchr(file, '/');
    filename = (filename != NULL) ? filename + 1 : file;
    
    // Format message using variadic arguments
    char message[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(message, sizeof(message), format, args);
    va_end(args);
    
    // Format final log line
    char log_line[2048];
    snprintf(log_line, sizeof(log_line),
             "[%s] [%s] [%s:%d] - %s",
             timestamp, level_str, filename, line, message);
    
    // Write to console (stderr for critical, stdout for others)
    FILE *console = get_console_stream(level);
    fprintf(console, "%s\n", log_line);
    fflush(console);
    
    // Write to file if configured
    if (g_logger.log_file != NULL) {
        fprintf(g_logger.log_file, "%s\n", log_line);
        fflush(g_logger.log_file);
    }
}
