#include "logger.h"

int main(void) {
    printf("=== ITERATION 4 TEST ===\n");
    printf("Testing all levels and filtering...\n\n");
    
    // Test 1: All levels (min = DEBUG)
    printf("--- Test 1: All levels (min = DEBUG) ---\n");
    logger_init(LOG_DEBUG, NULL);
    logger_log(LOG_EMERGENCY, "EMERGENCY message");
    logger_log(LOG_ALERT, "ALERT message");
    logger_log(LOG_CRITICAL, "CRITICAL message");
    logger_log(LOG_ERROR, "ERROR message");
    logger_log(LOG_WARNING, "WARNING message");
    logger_log(LOG_NOTICE, "NOTICE message");
    logger_log(LOG_INFO, "INFO message");
    logger_log(LOG_DEBUG, "DEBUG message");

    printf("\n✓ Should see all 8 levels above\n");
    // Test 2: Filtering (min = WARNING)
    printf("\n--- Test 2: Filtering (min = WARNING) ---\n");
    logger_set_level(LOG_WARNING);
    printf("These should show:\n");
    logger_log(LOG_EMERGENCY, "Should show");
    logger_log(LOG_ALERT, "Should show");
    logger_log(LOG_CRITICAL, "Should show");
    logger_log(LOG_ERROR, "Should show");
    logger_log(LOG_WARNING, "Should show");
    
    printf("\nThese should NOT show:\n");
    logger_log(LOG_NOTICE, "Should NOT show");
    logger_log(LOG_INFO, "Should NOT show");
    logger_log(LOG_DEBUG, "Should NOT show");

    printf("(If you see log lines above, filtering is broken!)\n");
    
    logger_cleanup();
    
    printf("\n✓ Test completed\n");
    return 0;
}
