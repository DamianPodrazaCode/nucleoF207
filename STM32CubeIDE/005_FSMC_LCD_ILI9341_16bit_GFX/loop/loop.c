#include "loop.h"

//void bench();

__IO uint32_t time = 0;

void setup() {
	ili9341_init(lcdOrientPortrait_0);
	ili9341_clearScr(COLOR_BLACK);


	time = HAL_GetTick();
//	bench();
	time = HAL_GetTick() - time;  //2486 ms
}

void loop() {
//	clearScr(COLOR_BLUE);
//	time = HAL_GetTick();
//	bench();
//	time = HAL_GetTick() - time;  //2486 ms
//	HAL_Delay(99);
}

//void bench() {
//	srand(HAL_GetTick());
//	uint32_t x1, x2, y1, y2, color;
//	const uint32_t iter = 2000;
//	for (int i = 0; i < iter; i++) {
//		x1 = rand() % lcdProp.width;
//		x2 = rand() % lcdProp.width;
//		y1 = rand() % lcdProp.height;
//		color = rand() % 0xffff;
//		hLine(x1, x2, y1, color);
//	}
//	for (int i = 0; i < iter; i++) {
//		x1 = rand() % lcdProp.width;
//		y1 = rand() % lcdProp.height;
//		y2 = rand() % lcdProp.height;
//		color = rand() % 0xffff;
//		vLine(x1, y1, y2, color);
//	}
//	for (int i = 0; i < iter; i++) {
//		x1 = rand() % lcdProp.width;
//		x2 = rand() % lcdProp.width;
//		y1 = rand() % lcdProp.height;
//		y2 = rand() % lcdProp.height;
//		color = rand() % 0xffff;
//		lcdLine(x1, y1, x2, y2, color);
//	}
//	for (int i = 0; i < iter * 100; i++) {
//		x1 = rand() % lcdProp.width;
//		y1 = rand() % lcdProp.height;
//		color = rand() % 0xffff;
//		setPixel(x1, y1, color);
//	}
//	clearScr(COLOR_BLACK);
//}
