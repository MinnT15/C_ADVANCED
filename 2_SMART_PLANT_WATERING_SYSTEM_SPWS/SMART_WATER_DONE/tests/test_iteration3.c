#include <stdio.h>
#include "spws_controller.h"
#include "hal_sensors.h"

#define check(name, condition) \
    do { \
        if (condition) { \
            printf("  [PASS] %s\n", name); \
        } else { \
            printf("  [FAIL] %s\n", name); \
            test_fail++; \
        } \
    } while(0)

/* External mock helper */
void HAL_Simulate_SetMoisture(float value);

int main() {
    int test_fail = 0;
    
    printf("--- ITERATION 3: AUTO WATERING LOGIC ---\n");
    
    SPWS_Init();
    const SystemState_t* state = SPWS_GetState();
    
    printf("Test 1: Normal moisture (45%%) -> Pump should stay OFF\n");
    HAL_Simulate_SetMoisture(45.0f);
    SPWS_Process();
    check("Pump is OFF", state->pumpState == PUMP_OFF);
    check("LED is Normal", state->ledState == LED_NORMAL);

    printf("Test 2: Low moisture (20%%) -> Pump should turn ON\n");
    HAL_Simulate_SetMoisture(20.0f);
    SPWS_Process();
    check("Pump is ON", state->pumpState == PUMP_ON);
    check("LED is Watering (Yellow)", state->ledState == LED_WATERING);

    printf("Test 3: Moisture increases (80%%) -> Pump should turn OFF\n");
    HAL_Simulate_SetMoisture(80.0f);
    SPWS_Process();
    check("Pump is OFF", state->pumpState == PUMP_OFF);
    check("LED is Normal", state->ledState == LED_NORMAL);

    printf("Test 4: Low moisture again (20%%) -> Pump ON, then Timeout\n");
    HAL_Simulate_SetMoisture(20.0f);
    SPWS_Process();
    check("Pump is ON", state->pumpState == PUMP_ON);
    
    printf("Simulating %d cycles (timeout protection)...\n", MAX_WATERING_DURATION_S);
    for(int i = 0; i < MAX_WATERING_DURATION_S; i++) {
        SPWS_Process();
    }
    check("Pump is OFF due to timeout", state->pumpState == PUMP_OFF);

    if (test_fail == 0) {
        printf("\nRESULT: ALL TESTS PASSED ✅\n");
        return 0;
    } else {
        printf("\nRESULT: %d TESTS FAILED ❌\n", test_fail);
        return 1;
    }
}
