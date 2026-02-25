/**
 * @file spws_controller.h
 * @brief Public API for the Smart Plant Watering System controller.
 */

#ifndef SPWS_CONTROLLER_H
#define SPWS_CONTROLLER_H

#include "config.h"

/**
 * @brief Initialize the system with default settings.
 */
void SPWS_Init(void);

/**
 * @brief Process system logic (main loop iteration).
 */
void SPWS_Process(void);

/**
 * @brief Toggle between AUTO and MANUAL modes.
 */
void SPWS_ToggleMode(void);

/**
 * @brief Get the current system state (for testing/monitoring).
 * @return const pointer to system state.
 */
const SystemState_t* SPWS_GetState(void);

#endif // SPWS_CONTROLLER_H
