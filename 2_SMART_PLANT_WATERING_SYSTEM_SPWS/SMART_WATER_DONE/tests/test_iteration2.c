#include <stdio.h>
#include "hal_sensors.h"
#include "hal_actuators.h"
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

/* External mock functions declared in .c for testing */
void HAL_Simulate_SetMoisture(float value);
void HAL_Simulate_PressButton1(void);

int main() {
    int test_fail = 0;
    
    printf("--- ITERATION 2: HAL SIMULATION ---\n");
    
    printf("Testing Sensors:\n");
    HAL_Simulate_SetMoisture(25.5f);
    check("Moisture read correctly", HAL_ReadMoisture() == 25.5f);
    check("Temperature read correctly", HAL_ReadTemperature() > 0);

    printf("Testing Actuators (Visual check of logs):\n");
    HAL_SetPump(PUMP_ON);
    HAL_SetPump(PUMP_OFF);
    HAL_SetLed(LED_WATERING);

    printf("Testing Buttons:\n");
    HAL_Simulate_PressButton1();
    check("Button 1 press detected", HAL_CheckButton1() == true);
    check("Button 1 auto-reset", HAL_CheckButton1() == false);
    
    if (test_fail == 0) {
        printf("\nRESULT: ALL TESTS PASSED ✅\n");
        return 0;
    } else {
        printf("\nRESULT: %d TESTS FAILED ❌\n", test_fail);
        return 1;
    }
}
