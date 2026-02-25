#include "logger.h"
#include <stdio.h>

int main(void) {
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║     LOGGER SYSTEM - FINAL DEMO                 ║\n");
    printf("╚════════════════════════════════════════════════╝\n\n");
    
    // Initialize logger (DEBUG level, write to file)
    logger_init(LOG_DEBUG, "logs/app.log");
    
    // Demo 1: All log levels
    printf("=== Demo 1: All Log Levels ===\n");
    log_emergency("System is unusable!");
    log_alert("Action must be taken immediately!");
    log_critical("Critical condition occurred");
    log_error("Error: File not found");
    log_warning("Warning: Memory usage at 90%%");
    log_notice("User admin logged in");
    log_info("Application started successfully");
    log_debug("Debug: Variable x = %d", 42);
    
    // Demo 2: Format strings
    printf("\n=== Demo 2: Format Strings ===\n");
    log_info("User %s logged in from %s", "alice", "192.168.1.100");
    log_error("Connection timeout after %d seconds", 30);
    log_debug("Processing %d items, progress: %.2f%%", 100, 75.5);
    
    // Demo 3: Level filtering
    printf("\n=== Demo 3: Level Filtering ===\n");
    printf("Setting level to WARNING...\n");
    logger_set_level(LOG_WARNING);
    
    log_debug("This should NOT appear");
    log_info("This should NOT appear");
    log_warning("This SHOULD appear");
    log_error("This SHOULD appear");
    
    // Demo 4: File and line tracking
    printf("\n=== Demo 4: File and Line Tracking ===\n");
    log_info("Check the log - it shows file:line automatically!");
    log_error("Error on line %d", __LINE__);
    
    // Cleanup
    logger_cleanup();
    
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║     DEMO COMPLETED                             ║\n");
    printf("║     Check logs/app.log for file output         ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
    
    return 0;
}