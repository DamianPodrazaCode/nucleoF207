#include "loop.h"

void bench();
void bench2();
void bench3();

__IO uint32_t time = 0;

void setup() {
	drv_init(lcdOrientLandscape_90);
	clearScr(COLOR_BLACK);
	gfx_init(lcdProp.width, lcdProp.height);

//	gfx2d_line(0, 0, 100, 200, COLOR_WHITE);
//	gfx2d_triangle(100, 10, 200, 100, 10, 160, COLOR_LIGHTGREY);
//	gfx2d_fillTriangle(100, 10, 200, 100, 10, 160, COLOR_LIGHTGREY);

	time = HAL_GetTick();
//	bench();
	bench2();
//	bench3();

// 23
// clearScr(COLOR_BLACK);

// 267
//	for (int x = 0; x < 320; x++) {
//		for (int y = 0; y < 240; y++)
//			drawPixel(x, y, COLOR_BLUE);
//	}
	time = HAL_GetTick() - time;
}

void bench3() {
	gfx2d_fillTriangle(50, 80, 160, 20, 270, 200, COLOR_BLUE);
}

void bench2() {

//	gfx2d_line(2, 2, 217, 20, COLOR_CYAN);

//	for (int x = 0; x < lcdProp.width/2; x++)
//		gfx2d_line(x, 0, lcdProp.width / 2, lcdProp.height / 2, COLOR_CYAN);

	for (int x = 0; x < lcdProp.width; x++) {
		gfx2d_line(x, 0, lcdProp.width / 2, lcdProp.height / 2, COLOR_CYAN);
//		HAL_Delay(9);
	}
//	for (int y = 0; y < lcdProp.height; y++) {
//		gfx2d_line(lcdProp.width, y, lcdProp.width / 2, lcdProp.height / 2, COLOR_BLUE);
//		HAL_Delay(9);
//	}
//	for (int x = lcdProp.width; x >= 0; x--) {
//		gfx2d_line(x, lcdProp.height, lcdProp.width / 2, lcdProp.height / 2, COLOR_GREEN);
//		HAL_Delay(9);
//	}
//	for (int y = lcdProp.height; y >= 0; y--) {
//		gfx2d_line(0, y, lcdProp.width / 2, lcdProp.height / 2, COLOR_MAGENTA);
//		HAL_Delay(9);
//	}

}

void loop() {
//	clearScr(COLOR_BLUE);
//	time = HAL_GetTick();
//	bench();
//	time = HAL_GetTick() - time;
//	HAL_Delay(99);
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
		drawHLine(x1, x2, y1, color);
	}
	for (int i = 0; i < iter; i++) {
		x1 = rand() % lcdProp.width;
		y1 = rand() % lcdProp.height;
		y2 = rand() % lcdProp.height;
		color = rand() % 0xffff;
		drawVLine(x1, y1, y2, color);
	}
	for (int i = 0; i < iter; i++) {
		x1 = rand() % lcdProp.width;
		x2 = rand() % lcdProp.width;
		y1 = rand() % lcdProp.height;
		y2 = rand() % lcdProp.height;
		color = rand() % 0xffff;
		gfx2d_line(x1, y1, x2, y2, color);
	}
	for (int i = 0; i < iter * 100; i++) {
		x1 = rand() % lcdProp.width;
		y1 = rand() % lcdProp.height;
		color = rand() % 0xffff;
		drawPixel(x1, y1, color);
	}
	clearScr(COLOR_BLACK);
}
