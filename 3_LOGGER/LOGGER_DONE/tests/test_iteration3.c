#include "logger.h"
#include <stdio.h>

int main(void) {
    printf("=== ITERATION 3 TEST ===\n");
    printf("Testing file output...\n\n");

    // Test 1: Console only
    printf("--- Test 1: Console only ---\n");
    logger_init(LOG_INFO, NULL);
    log_info("Console only message");
    logger_cleanup();

    // Test 2: Console + File
    printf("\n--- Test 2: Console + File ---\n");
    logger_init(LOG_INFO, "logs/test_iter3.log");
    log_info("This goes to console AND file");
    log_info("Second message to both");
    logger_cleanup();

    printf("\n✓ Check logs/test_iter3.log for file output\n");
    return 0;
}