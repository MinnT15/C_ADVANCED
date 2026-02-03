#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

// Log levels (theo chuẩn syslog)
typedef enum {
    LOG_EMERGENCY = 0,  // System is unusable
    LOG_ALERT     = 1,  // Action must be taken immediately
    LOG_CRITICAL  = 2,  // Critical conditions
    LOG_ERROR     = 3,  // Error conditions
    LOG_WARNING   = 4,  // Warning conditions
    LOG_NOTICE    = 5,  // Normal but significant condition
    LOG_INFO      = 6,  // Informational messages
    LOG_DEBUG     = 7   // Debug-level messages
} LogLevel;

// Core functions
int logger_init(LogLevel min_level, const char *log_filename);
void logger_set_level(LogLevel min_level);
void logger_cleanup(void);
void logger_log(LogLevel level, const char *file, int line,
                const char *format, ...);

// Convenience macros
#define log_emergency(...) logger_log(LOG_EMERGENCY, __FILE__, __LINE__, __VA_ARGS__)
#define log_alert(...)     logger_log(LOG_ALERT,     __FILE__, __LINE__, __VA_ARGS__)
#define log_critical(...)  logger_log(LOG_CRITICAL,  __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...)     logger_log(LOG_ERROR,     __FILE__, __LINE__, __VA_ARGS__)
#define log_warning(...)   logger_log(LOG_WARNING,   __FILE__, __LINE__, __VA_ARGS__)
#define log_notice(...)    logger_log(LOG_NOTICE,    __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)      logger_log(LOG_INFO,      __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...)     logger_log(LOG_DEBUG,     __FILE__, __LINE__, __VA_ARGS__)

#endif // LOGGER_H
