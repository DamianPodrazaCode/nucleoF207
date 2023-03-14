#include "main.h"


void LED_Init();

int main(void) {
    HAL_Init();
    SystemClock_Config();

    LED_Init();

    while (1) {
        LED1_GPIO_PORT->BSRR = LED1_PIN;
        HAL_Delay(99);
        LED2_GPIO_PORT->BSRR = LED2_PIN;
        HAL_Delay(99);
        LED3_GPIO_PORT->BSRR = LED3_PIN;
        HAL_Delay(99);
        LED1_GPIO_PORT->BSRR = LED1_PIN << 16;
        HAL_Delay(99);
        LED2_GPIO_PORT->BSRR = LED2_PIN << 16;
        HAL_Delay(99);
        LED3_GPIO_PORT->BSRR = LED3_PIN << 16;
        HAL_Delay(99);
    }
    
}


