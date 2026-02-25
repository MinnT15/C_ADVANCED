/**
 * @file config.h
 * @brief Configuration constants, enums and structs for SPWS.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stdbool.h>

/* System Constants */
#define DEFAULT_MIN_MOISTURE        30.0f
#define DEFAULT_MAX_MOISTURE        70.0f
#define MAX_WATERING_DURATION_S     10
#define SENSOR_READ_INTERVAL_S      2
#define MANUAL_WATERING_DURATION_S  5

/* Enums */
typedef enum {
    MODE_AUTO = 0,
    MODE_MANUAL
} SystemMode_t;

typedef enum {
    PUMP_OFF = 0,
    PUMP_ON
} PumpState_t;

typedef enum {
    LED_NORMAL = 0, // Green
    LED_WATERING,   // Yellow
    LED_ALARM       // Red
} LedState_t;

/* Structs */
typedef struct {
    float moisture;
    float temperature;
} SensorData_t;

typedef struct {
    float minMoistureThreshold;
    float maxMoistureThreshold;
    uint32_t maxWateringDuration_s;
    uint32_t sensorReadInterval_s;
    uint32_t manualWateringDuration_s;
} SystemSettings_t;

typedef struct {
    SystemMode_t mode;
    PumpState_t pumpState;
    LedState_t ledState;
    SensorData_t currentData;
    SystemSettings_t settings;
} SystemState_t;

#endif // CONFIG_H
