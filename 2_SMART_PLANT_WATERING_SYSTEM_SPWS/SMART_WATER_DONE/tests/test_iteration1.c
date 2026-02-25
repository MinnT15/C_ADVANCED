#include <stdio.h>
#include "spws_controller.h"

#define check(name, condition) \
    do { \
        if (condition) { \
            printf("  [PASS] %s\n", name); \
        } else { \
            printf("  [FAIL] %s\n", name); \
            test_fail++; \
        } \
    } while(0)

int main() {
    int test_fail = 0;
    
    printf("--- ITERATION 1: SYSTEM INITIALIZATION ---\n");
    
    SPWS_Init();
    const SystemState_t* state = SPWS_GetState();
    
    printf("Testing initial conditions:\n");
    check("Mode is AUTO", state->mode == MODE_AUTO);
    check("Pump is OFF", state->pumpState == PUMP_OFF);
    check("LED is Normal", state->ledState == LED_NORMAL);
    check("Default Min Moisture is 30", state->settings.minMoistureThreshold == 30.0f);
    
    printf("Testing Mode Toggle:\n");
    SPWS_ToggleMode();
    check("Mode changed to MANUAL", state->mode == MODE_MANUAL);
    
    SPWS_ToggleMode();
    check("Mode changed back to AUTO", state->mode == MODE_AUTO);
    
    if (test_fail == 0) {
        printf("\nRESULT: ALL TESTS PASSED ✅\n");
        return 0;
    } else {
        printf("\nRESULT: %d TESTS FAILED ❌\n", test_fail);
        return 1;
    }
}
