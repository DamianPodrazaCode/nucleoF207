#include "main.h"

#define ADDR_CMD (0x60000000) //LCD_RS=0
#define ADDR_RAM (0x60020000) //LCD_RS=1, LINIA A16 przy 16bit
#define LCD_CMD (*((__IO uint16_t*) ADDR_CMD))
#define LCD_RAM (*((__IO uint16_t*) ADDR_RAM))

#define buffSize 16
uint16_t src[buffSize] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

int main(void) {
    HAL_Init();
    SystemClock_Config();

    fsmcInit();


    while (1) {
        for (int i = 0; i < buffSize; i++) {
            LCD_CMD = src[i]; // DC = 0
        }
        __NOP();
        __NOP();
        __NOP();
        __NOP();

        for (int i = 0; i < buffSize; i++) {
            LCD_RAM = src[i]; // DC = 1
        }
        __NOP();
        __NOP();
        __NOP();
        __NOP();
    }

}
