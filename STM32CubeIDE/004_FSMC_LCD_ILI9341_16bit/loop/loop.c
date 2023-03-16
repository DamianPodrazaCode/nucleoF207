#include "loop.h"
#include <stdlib.h>

#include "../ili9341/ili9341.h"
#include "../ili9341/gfx.h"

void bench();

__IO uint32_t time = 0;

void setup() {
	lcdInit(lcdOrientPortrait_0);
	lcdClear(COLOR_BLUE);

	time = HAL_GetTick();
	bench();
	time = HAL_GetTick() - time;  //2486 ms
}

void loop() {
	//lcdInit(lcdOrientPortrait_0);
	lcdClear(COLOR_BLUE);
	time = HAL_GetTick();
	bench();
	time = HAL_GetTick() - time;  //2486 ms
	HAL_Delay(99);
}

void bench() {
	srand(HAL_GetTick());
	uint32_t x1, x2, y1, y2, color;
	const uint32_t iter = 2000;
	for (int i = 0; i < iter; i++) {
		x1 = rand() % lcdProp.width;
		x2 = rand() % lcdProp.width;
		y1 = rand() % lcdProp.height;
		color = rand() % 0xffff;
		lcdHLine(x1, x2, y1, color);
	}
	for (int i = 0; i < iter; i++) {
		x1 = rand() % lcdProp.width;
		y1 = rand() % lcdProp.height;
		y2 = rand() % lcdProp.height;
		color = rand() % 0xffff;
		lcdVLine(x1, y1, y2, color);
	}
	for (int i = 0; i < iter; i++) {
		x1 = rand() % lcdProp.width;
		x2 = rand() % lcdProp.width;
		y1 = rand() % lcdProp.height;
		y2 = rand() % lcdProp.height;
		color = rand() % 0xffff;
		lcdLine(x1, y1, x2, y2, color);
	}
	for (int i = 0; i < iter * 100; i++) {
		x1 = rand() % lcdProp.width;
		y1 = rand() % lcdProp.height;
		;
		color = rand() % 0xffff;
		lcdDrawPixel(x1, y1, color);
	}
	lcdClear(COLOR_BLACK);
}
