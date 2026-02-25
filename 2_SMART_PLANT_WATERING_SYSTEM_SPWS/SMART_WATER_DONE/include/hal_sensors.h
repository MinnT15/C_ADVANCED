/**
 * @file hal_sensors.h
 * @brief Hardware Abstraction Layer for sensors.
 */

#ifndef HAL_SENSORS_H
#define HAL_SENSORS_H

/**
 * @brief Read soil moisture percentage (0-100%).
 * @return float Moisture value.
 */
float HAL_ReadMoisture(void);

/**
 * @brief Read ambient temperature in Celsius.
 * @return float Temperature value.
 */
float HAL_ReadTemperature(void);

#endif // HAL_SENSORS_H
