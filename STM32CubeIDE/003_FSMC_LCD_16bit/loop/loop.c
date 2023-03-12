#include "loop.h"

#define CMD 0x60000000
#define RAM 0x60020000 //LCD Register select = FSMC_A16
#define LCD_CMD (*((__IO uint16_t *) CMD)) // LCD_RS_DC = 0
#define LCD_RAM (*((__IO uint16_t *) RAM)) // LCD_RS_DC = 1

#define buffSize 32
uint16_t src[buffSize] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, //
		16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };

void setup() {
}

void loop() {
	TRIG_GPIO_Port->BSRR = TRIG_Pin << 16; //PC0 = 0

	for (int i = 0; i < buffSize; i++) {
		LCD_CMD = src[i]; // RS = 0
	}
	for (int i = 0; i < buffSize; i++) {
		LCD_RAM = src[i]; // RS = 1
	}

	TRIG_GPIO_Port->BSRR = TRIG_Pin; //PC0 = 1
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
}
