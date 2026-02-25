#include "logger.h"

int main(void) {
    printf("=== ITERATION 1 TEST ===\n");
    printf("Testing basic logger...\n\n");
    
    logger_log(LOG_INFO, "Hello, Logger!");
    logger_log(LOG_INFO, "This is a test message");
    
    printf("\n✓ If you see 2 log lines above, test PASSED\n");
    return 0;
}