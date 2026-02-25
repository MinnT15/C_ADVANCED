/**
 * @file hal_buttons.h
 * @brief Hardware Abstraction Layer for buttons.
 */

#ifndef HAL_BUTTONS_H
#define HAL_BUTTONS_H

#include <stdbool.h>

/**
 * @brief Check if Button 1 (Mode Toggle) is pressed.
 * @return true if pressed.
 */
bool HAL_CheckButton1(void);

/**
 * @brief Check if Button 2 (Manual Water) is pressed.
 * @return true if pressed.
 */
bool HAL_CheckButton2(void);

#endif // HAL_BUTTONS_H
