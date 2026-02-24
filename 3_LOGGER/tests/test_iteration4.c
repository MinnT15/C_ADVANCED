#include "logger.h"
#include <stdio.h>

int main(void) {
    printf("=== ITERATION 4 TEST ===\n");
    printf("Testing all levels and filtering...\n\n");

    // Test 1: All levels (min = DEBUG)
    printf("--- Test 1: All levels (min = DEBUG) ---\n");
    logger_init(LOG_DEBUG, NULL);
    log_emergency("EMERGENCY message");
    log_alert("ALERT message");
    log_critical("CRITICAL message");
    log_error("ERROR message");
    log_warning("WARNING message");
    log_notice("NOTICE message");
    log_info("INFO message");
    log_debug("DEBUG message");

    printf("\n✓ Should see all 8 levels above\n");

    // Test 2: Filtering (min = WARNING)
    printf("\n--- Test 2: Filtering (min = WARNING) ---\n");
    logger_set_level(LOG_WARNING);
    printf("These should show:\n");
    log_emergency("Should show");
    log_alert("Should show");
    log_critical("Should show");
    log_error("Should show");
    log_warning("Should show");

    printf("\nThese should NOT show:\n");
    log_notice("Should NOT show");
    log_info("Should NOT show");
    log_debug("Should NOT show");

    printf("(If you see log lines above, filtering is broken!)\n");

    logger_cleanup();

    printf("\n✓ Test completed\n");
    return 0;
}
