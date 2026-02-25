#include "logger.h"
#include <unistd.h>

int main(void) {
    printf("=== ITERATION 2 TEST ===\n");
    printf("Testing timestamp...\n\n");
    
    logger_log(LOG_INFO, "First message");
    sleep(1);  // Đợi 1 giây
    logger_log(LOG_INFO, "Second message (1 second later)");
    
    printf("\n✓ Check if timestamps are different\n");
    printf("✓ Format should be: [YYYY-MM-DD HH:MM:SS] [INFO] Message\n");
    return 0;
}