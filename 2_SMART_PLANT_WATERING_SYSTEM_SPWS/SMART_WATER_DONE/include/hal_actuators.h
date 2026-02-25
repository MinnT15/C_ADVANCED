/**
 * @file hal_actuators.h
 * @brief Hardware Abstraction Layer for actuators (Pump, LED).
 */

#ifndef HAL_ACTUATORS_H
#define HAL_ACTUATORS_H

#include "config.h"

/**
 * @brief Control the water pump.
 * @param state PUMP_ON or PUMP_OFF.
 */
void HAL_SetPump(PumpState_t state);

/**
 * @brief Control the status LED.
 * @param state LED color/state.
 */
void HAL_SetLed(LedState_t state);

#endif // HAL_ACTUATORS_H
