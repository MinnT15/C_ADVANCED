#include "hal_sensors.h"

/* Simulated sensor values */
static float g_fake_moisture = 45.0f;
static float g_fake_temperature = 28.5f;

float HAL_ReadMoisture(void) {
    return g_fake_moisture;
}

float HAL_ReadTemperature(void) {
    return g_fake_temperature;
}

/* Helper to simulate sensor changes in tests */
void HAL_Simulate_SetMoisture(float value) {
    g_fake_moisture = value;
}
