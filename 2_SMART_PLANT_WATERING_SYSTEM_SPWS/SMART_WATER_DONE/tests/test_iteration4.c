#include <stdio.h>
#include "spws_controller.h"
#include "hal_sensors.h"
#include "hal_buttons.h"

#define check(name, condition) \
    do { \
        if (condition) { \
            printf("  [PASS] %s\n", name); \
        } else { \
            printf("  [FAIL] %s\n", name); \
            test_fail++; \
        } \
    } while(0)

/* External mock helpers */
void HAL_Simulate_PressButton1(void);
void HAL_Simulate_PressButton2(void);

int main() {
    int test_fail = 0;
    
    printf("--- ITERATION 4: MANUAL MODE & BUTTONS ---\n");
    
    SPWS_Init();
    const SystemState_t* state = SPWS_GetState();
    
    printf("Test 1: Toggle Mode via Button 1\n");
    HAL_Simulate_PressButton1();
    SPWS_Process();
    check("Mode is MANUAL", state->mode == MODE_MANUAL);

    printf("Test 2: Manual Water via Button 2 in MANUAL mode\n");
    HAL_Simulate_PressButton2();
    SPWS_Process();
    check("Pump is ON", state->pumpState == PUMP_ON);
    
    printf("Simulating %d cycles (manual duration)...\n", MANUAL_WATERING_DURATION_S);
    for(int i = 0; i < MANUAL_WATERING_DURATION_S; i++) {
        SPWS_Process();
    }
    check("Pump is OFF after duration", state->pumpState == PUMP_OFF);

    printf("Test 3: Button 2 in AUTO mode (Should be ignored)\n");
    HAL_Simulate_PressButton1(); // Toggle back to AUTO
    SPWS_Process();
    check("Mode is AUTO", state->mode == MODE_AUTO);
    
    HAL_Simulate_PressButton2();
    SPWS_Process();
    check("Pump is STILL OFF", state->pumpState == PUMP_OFF);

    if (test_fail == 0) {
        printf("\nRESULT: ALL TESTS PASSED ✅\n");
        return 0;
    } else {
        printf("\nRESULT: %d TESTS FAILED ❌\n", test_fail);
        return 1;
    }
}
