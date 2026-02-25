#define _DEFAULT_SOURCE
#include <stdio.h>
#include <unistd.h>
#include "spws_controller.h"

/* Mock helpers to simulate environment changes in main demo */
void HAL_Simulate_SetMoisture(float value);
void HAL_Simulate_PressButton1(void);
void HAL_Simulate_PressButton2(void);

int main() {
    printf("==================================================\n");
    printf("   SMART PLANT WATERING SYSTEM (SPWS) DEMO\n");
    printf("==================================================\n\n");

    /* 1. Initialization */
    SPWS_Init();
    printf("\n--- GIAI DOAN 1: CHE DO TU DONG (AUTO) ---\n");
    
    // Step A: Moisture normal
    printf("\n[Step 1] Dat dang du am (45%%)...\n");
    HAL_Simulate_SetMoisture(45.0f);
    for(int i=0; i<3; i++) {
        SPWS_Process();
        usleep(100000); // 100ms
    }

    // Step B: Moisture drops
    printf("\n[Step 2] Dat kho (25%%) -> He thong se tu bat bom...\n");
    HAL_Simulate_SetMoisture(25.0f);
    for(int i=0; i<5; i++) {
        SPWS_Process();
        usleep(100000);
    }

    // Step C: Moisture rises
    printf("\n[Step 3] Dang tuoi -> Do am tang len 75%% -> He thong tu tat bom...\n");
    HAL_Simulate_SetMoisture(75.0f);
    SPWS_Process();

    /* 2. Manual Mode */
    printf("\n--- GIAI DOAN 2: CHE DO THU CONG (MANUAL) ---\n");
    printf("\n[Step 4] Nhan nut 1 de chuyen sang MANUAL...\n");
    HAL_Simulate_PressButton1();
    SPWS_Process();

    printf("\n[Step 5] Nhan nut 2 de tuoi thu cong...\n");
    HAL_Simulate_PressButton2();
    SPWS_Process();
    
    printf("\n[Step 6] Dang tuoi thu cong thi nhan nut 1 chuyen ve AUTO...\n");
    printf("(Rule: Bom phai bi ngat ngay lap tuc)\n");
    HAL_Simulate_PressButton1();
    SPWS_Process();

    printf("\n==================================================\n");
    printf("             DEMO COMPLETED SUCCESSFULLY\n");
    printf("==================================================\n");

    return 0;
}
