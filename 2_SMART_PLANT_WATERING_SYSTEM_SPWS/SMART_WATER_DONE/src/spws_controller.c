/**
 * @file spws_controller.c
 * @brief Implementation of SPWS controller logic.
 */

#include "spws_controller.h"
#include <stdio.h>

#include "hal_sensors.h"
#include "hal_actuators.h"
#include "hal_buttons.h"

/* Private system state */
static SystemState_t g_system_state;
static uint32_t g_watering_time_counter = 0;

void SPWS_Init(void) {
    g_system_state.mode = MODE_AUTO;
    g_system_state.pumpState = PUMP_OFF;
    g_system_state.ledState = LED_NORMAL;
    
    g_system_state.currentData.moisture = 0.0f;
    g_system_state.currentData.temperature = 0.0f;
    
    /* Default settings */
    g_system_state.settings.minMoistureThreshold = DEFAULT_MIN_MOISTURE;
    g_system_state.settings.maxMoistureThreshold = DEFAULT_MAX_MOISTURE;
    g_system_state.settings.maxWateringDuration_s = MAX_WATERING_DURATION_S;
    g_system_state.settings.sensorReadInterval_s = SENSOR_READ_INTERVAL_S;
    g_system_state.settings.manualWateringDuration_s = MANUAL_WATERING_DURATION_S;
    
    HAL_SetPump(PUMP_OFF);
    HAL_SetLed(LED_NORMAL);
    
    printf("[SYSTEM] Initialized: Mode=AUTO, Pump=OFF, LED=Normal\n");
}

static void SPWS_UpdateLED(void) {
    if (g_system_state.pumpState == PUMP_ON) {
        g_system_state.ledState = LED_WATERING;
    } else {
        g_system_state.ledState = LED_NORMAL;
    }
    HAL_SetLed(g_system_state.ledState);
}

void SPWS_Process(void) {
    /* 1. Read Sensors */
    g_system_state.currentData.moisture = HAL_ReadMoisture();
    g_system_state.currentData.temperature = HAL_ReadTemperature();

    /* 2. Check Buttons */
    if (HAL_CheckButton1()) {
        SPWS_ToggleMode();
    }

    if (HAL_CheckButton2()) {
        if (g_system_state.mode == MODE_MANUAL) {
            if (g_system_state.pumpState == PUMP_OFF) {
                printf("[MANUAL] Button 2 pressed -> Starting manual watering\n");
                g_system_state.pumpState = PUMP_ON;
                HAL_SetPump(PUMP_ON);
                g_watering_time_counter = 0;
            }
        } else {
            printf("[SYSTEM] Button 2 ignored (only works in MANUAL mode)\n");
        }
    }

    /* 3. Mode-specific Logic */
    if (g_system_state.mode == MODE_AUTO) {
        if (g_system_state.pumpState == PUMP_OFF) {
            if (g_system_state.currentData.moisture < g_system_state.settings.minMoistureThreshold) {
                printf("[AUTO] Moisture low (%.1f%%) -> Starting Pump\n", g_system_state.currentData.moisture);
                g_system_state.pumpState = PUMP_ON;
                HAL_SetPump(PUMP_ON);
                g_watering_time_counter = 0;
            }
        } else {
            /* Pump is ON in AUTO mode */
            g_watering_time_counter++;
            
            bool stop_condition = false;
            if (g_system_state.currentData.moisture > g_system_state.settings.maxMoistureThreshold) {
                printf("[AUTO] Moisture sufficient (%.1f%%) -> Stopping Pump\n", g_system_state.currentData.moisture);
                stop_condition = true;
            } else if (g_watering_time_counter >= g_system_state.settings.maxWateringDuration_s) {
                printf("[AUTO] Timeout Protection (%ds) -> Stopping Pump\n", g_watering_time_counter);
                stop_condition = true;
            }
            
            if (stop_condition) {
                g_system_state.pumpState = PUMP_OFF;
                HAL_SetPump(PUMP_OFF);
                g_watering_time_counter = 0;
            }
        }
    } else {
        /* MANUAL MODE logic */
        if (g_system_state.pumpState == PUMP_ON) {
            g_watering_time_counter++;
            if (g_watering_time_counter >= g_system_state.settings.manualWateringDuration_s) {
                printf("[MANUAL] Manual watering completed (%ds)\n", g_watering_time_counter);
                g_system_state.pumpState = PUMP_OFF;
                HAL_SetPump(PUMP_OFF);
                g_watering_time_counter = 0;
            }
        }
    }
    
    /* 4. Update Status Display (LED) */
    SPWS_UpdateLED();
}

void SPWS_ToggleMode(void) {
    if (g_system_state.mode == MODE_AUTO) {
        g_system_state.mode = MODE_MANUAL;
        printf("[SYSTEM] Mode changed to MANUAL\n");
        /* Rule: Turn off pump immediately when switching to MANUAL */
        if (g_system_state.pumpState == PUMP_ON) {
            g_system_state.pumpState = PUMP_OFF;
            HAL_SetPump(PUMP_OFF);
            g_watering_time_counter = 0;
        }
    } else {
        g_system_state.mode = MODE_AUTO;
        printf("[SYSTEM] Mode changed to AUTO\n");
    }
    SPWS_UpdateLED();
}

const SystemState_t* SPWS_GetState(void) {
    return &g_system_state;
}
