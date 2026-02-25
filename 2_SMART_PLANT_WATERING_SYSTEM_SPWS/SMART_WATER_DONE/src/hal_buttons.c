#include "hal_buttons.h"

static bool g_btn1_state = false;
static bool g_btn2_state = false;

bool HAL_CheckButton1(void) {
    bool state = g_btn1_state;
    g_btn1_state = false; // Mocking a pulse/press
    return state;
}

bool HAL_CheckButton2(void) {
    bool state = g_btn2_state;
    g_btn2_state = false; // Mocking a pulse/press
    return state;
}

/* Helper for tests */
void HAL_Simulate_PressButton1(void) { g_btn1_state = true; }
void HAL_Simulate_PressButton2(void) { g_btn2_state = true; }
