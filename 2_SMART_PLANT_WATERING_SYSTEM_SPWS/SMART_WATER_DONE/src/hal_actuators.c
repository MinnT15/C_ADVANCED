#include "hal_actuators.h"
#include <stdio.h>

void HAL_SetPump(PumpState_t state) {
    if (state == PUMP_ON) {
        printf("[HAL] >>> BOM: BAT (ON) <<<\n");
    } else {
        printf("[HAL] >>> BOM: TAT (OFF) <<<\n");
    }
}

void HAL_SetLed(LedState_t state) {
    switch (state) {
        case LED_NORMAL:
            printf("[HAL] LED: XANH (Binh thuong)\n");
            break;
        case LED_WATERING:
            printf("[HAL] LED: VANG (Dang tuoi)\n");
            break;
        case LED_ALARM:
            printf("[HAL] LED: DO (Canh bao)\n");
            break;
    }
}
