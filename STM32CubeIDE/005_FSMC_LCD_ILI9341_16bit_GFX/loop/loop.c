#include "loop.h"
#include <math.h>

void rotateStep(gfx2dPoint_t *pIn, gfx2dPoint_t *pOut, float deg);
void benchLine();
void benchTriangle();
void benchFillTriangle();
void benchRect();
void benchCircle();
void benchEllipse();
void benchRoundRect();

#define PI 3.14159265
__IO uint32_t time = 0;
gfx2dPoint_t A = { 160, 50 }, B = { 410, 190 }, C = { 110, 190 };
gfx2dPoint_t Ap, Bp, Cp;
gfx2dSize_t Sp;
gfx2dRadius_t Rp;
uint32_t color, r;
float deg = 0;
const uint32_t iter = 3600;

void setup() {
	drv_init(lcdOrientLandscape_90);
	clearScr(COLOR_BLACK);
	gfx_init(lcdProp.width, lcdProp.height);

	time = HAL_GetTick();
	benchLine();
	benchTriangle();
	benchFillTriangle();
	benchRect();
	benchCircle();
	benchEllipse();
	benchRoundRect();

//	Ap.x = 50;
//	Ap.y = 50;
//	Sp.w = 100;
//	Sp.h = 149;
//	gfx2d_fillRoundRect(Ap, Sp, 20, COLOR_BLUE);

//	Ap.x = 50;
//	Ap.y = 50;
//	Sp.w = 100;
//	Sp.h = 150;
//	gfx2d_roundRect(Ap, Sp, 20, COLOR_BLUE);

//	Ap.x = 10;
//	Ap.y = 10;
//	gfx2d_circle(Ap, 80, COLOR_BLUE);

//	Ap.x = -10;
//	Ap.y = 100;
//	Bp.x = 200;
//	Bp.y = -100;
//	gfx2d_line(Ap, Bp, COLOR_BLUE);
//
//	Ap.x = 200;
//	Ap.y = 300;
//	Bp.x = 400;
//	Bp.y = 100;
//	gfx2d_line(Ap, Bp, COLOR_RED);

	time = HAL_GetTick() - time;
}

void loop() {
}

void rotateStep(gfx2dPoint_t *pIn, gfx2dPoint_t *pOut, float deg) {
	pOut->x = ((pIn->x - 160) * cos(deg * PI / 180.0) - (pIn->y - 120) * sin(deg * PI / 180.0)) + 160;
	pOut->y = ((pIn->x - 160) * sin(deg * PI / 180.0) + (pIn->y - 120) * cos(deg * PI / 180.0)) + 120;
}

void benchLine() {
	srand(HAL_GetTick());
	for (int i = 0; i < iter; i++) {
		Ap.x = rand() % lcdProp.width;
		Bp.x = rand() % lcdProp.width;
		Ap.y = rand() % lcdProp.height;
		color = rand() % 0xffff;
		drawHLine(Ap.x, Bp.x, Ap.y, color);
	}
	for (int i = 0; i < iter; i++) {
		Ap.x = rand() % lcdProp.width;
		Ap.y = rand() % lcdProp.height;
		Bp.y = rand() % lcdProp.height;
		color = rand() % 0xffff;
		drawVLine(Ap.x, Ap.y, Bp.y, color);
	}
	for (int i = 0; i < iter; i++) {
		Ap.x = rand() % lcdProp.width;
		Ap.y = rand() % lcdProp.height;
		Bp.x = rand() % lcdProp.width;
		Bp.y = rand() % lcdProp.height;
		color = rand() % 0xffff;
		gfx2d_line(Ap, Bp, color);
	}
	for (int i = 0; i < iter * 100; i++) {
		Ap.x = rand() % lcdProp.width;
		Ap.y = rand() % lcdProp.height;
		color = rand() % 0xffff;
		drawPixel(Ap.x, Ap.y, color);
	}
	deg = 0;
	clearScr(COLOR_BLACK);
	for (int i = 0; i < iter >> 2; i++) {
		Ap.x = 160;
		Ap.y = 10;
		Bp.x = 160;
		Bp.y = 230;
		rotateStep(&A, &Ap, deg);
		rotateStep(&B, &Bp, deg);
		color = rand() % 0xffff;
		gfx2d_line(Ap, Bp, color);
		deg = deg + 1;
		HAL_Delay(4);
	}
}

void benchTriangle() {
	srand(HAL_GetTick());
	for (int i = 0; i < iter / 5; i++) {
		Ap.x = rand() % lcdProp.width;
		Ap.y = rand() % lcdProp.height;
		Bp.x = rand() % lcdProp.width;
		Bp.y = rand() % lcdProp.height;
		Cp.x = rand() % lcdProp.width;
		Cp.y = rand() % lcdProp.height;
		color = rand() % 0xffff;
		gfx2d_triangle(Ap, Bp, Cp, color);
	}
	clearScr(COLOR_BLACK);
	for (int i = 0; i < iter / 5; i++) {
		color = rand() % 0xffff;
		rotateStep(&A, &Ap, deg);
		rotateStep(&B, &Bp, deg);
		rotateStep(&C, &Cp, deg);
		gfx2d_triangle(Ap, Bp, Cp, color);
		//HAL_Delay(2);
		gfx2d_triangle(Ap, Bp, Cp, COLOR_BLACK);
		deg = deg + 1;
	}
	clearScr(COLOR_BLACK);
}

void benchFillTriangle() {
	srand(HAL_GetTick());
	for (int i = 0; i < iter / 5; i++) {
		Ap.x = rand() % lcdProp.width;
		Ap.y = rand() % lcdProp.height;
		Bp.x = rand() % lcdProp.width;
		Bp.y = rand() % lcdProp.height;
		Cp.x = rand() % lcdProp.width;
		Cp.y = rand() % lcdProp.height;
		color = rand() % 0xffff;
		gfx2d_fillTriangle(Ap, Bp, Cp, color);
	}
	clearScr(COLOR_BLACK);
	for (int i = 0; i < iter / 5; i++) {
		color = rand() % 0xffff;
		rotateStep(&A, &Ap, deg);
		rotateStep(&B, &Bp, deg);
		rotateStep(&C, &Cp, deg);
		gfx2d_fillTriangle(Ap, Bp, Cp, color);
		//HAL_Delay(2);
		gfx2d_fillTriangle(Ap, Bp, Cp, COLOR_BLACK);
		deg = deg + 1;
	}
	clearScr(COLOR_BLACK);
}

void benchRect() {
	srand(HAL_GetTick());
	for (int i = 0; i < iter; i++) {
		Ap.x = rand() % lcdProp.width / 2;
		Ap.y = rand() % lcdProp.height / 2;
		Sp.w = rand() % lcdProp.width / 2;
		Sp.h = rand() % lcdProp.height / 2;
		color = rand() % 0xffff;
		gfx2d_rect(Ap, Sp, color);
	}
	clearScr(COLOR_BLACK);
	for (int i = 0; i < iter / 5; i++) {
		Ap.x = rand() % lcdProp.width / 2;
		Ap.y = rand() % lcdProp.height / 2;
		Sp.w = rand() % lcdProp.width / 2;
		Sp.h = rand() % lcdProp.height / 2;
		color = rand() % 0xffff;
		gfx2d_fillRect(Ap, Sp, color);
	}
	clearScr(COLOR_BLACK);
}

void benchCircle() {
	srand(HAL_GetTick());
	for (int i = 0; i < iter; i++) {
		Ap.x = rand() % lcdProp.width;
		Ap.y = rand() % lcdProp.height;
		r = rand() % lcdProp.height;
		color = rand() % 0xffff;
		gfx2d_circle(Ap, r, color);
	}
	clearScr(COLOR_BLACK);
	for (int i = 0; i < iter / 5; i++) {
		Ap.x = rand() % lcdProp.width;
		Ap.y = rand() % lcdProp.height;
		r = rand() % lcdProp.height / 2;
		color = rand() % 0xffff;
		gfx2d_fillCircle(Ap, r, color);
	}
	clearScr(COLOR_BLACK);

}

void benchEllipse() {
	srand(HAL_GetTick());
	for (int i = 0; i < iter; i++) {
		Ap.x = rand() % lcdProp.width;
		Ap.y = rand() % lcdProp.height;
		Rp.rx = rand() % lcdProp.width;
		Rp.ry = rand() % lcdProp.height;
		color = rand() % 0xffff;
		gfx2d_ellipse(Ap, Rp, color);
	}
	clearScr(COLOR_BLACK);
	for (int i = 0; i < iter / 5; i++) {
		Ap.x = rand() % lcdProp.width;
		Ap.y = rand() % lcdProp.height;
		Rp.rx = rand() % lcdProp.width;
		Rp.ry = rand() % lcdProp.height;
		color = rand() % 0xffff;
		gfx2d_fillEllipse(Ap, Rp, color);
	}
	clearScr(COLOR_BLACK);
}

void benchRoundRect() {
	srand(HAL_GetTick());
	for (int i = 0; i < iter; i++) {
		Ap.x = rand() % lcdProp.width / 2;
		Ap.y = rand() % lcdProp.height / 2;
		Sp.w = 2 + rand() % lcdProp.width / 2;
		Sp.h = 2 + rand() % lcdProp.height / 2;
		r = rand() % 10;
		if (r >= MIN(Sp.w, Sp.h) / 2)
			r = MIN(Sp.w, Sp.h) / 2;
		color = rand() % 0xffff;
		gfx2d_roundRect(Ap, Sp, 1 + r, color);
	}
	clearScr(COLOR_BLACK);
	for (int i = 0; i < iter / 5; i++) {
		Ap.x = rand() % lcdProp.width / 2;
		Ap.y = rand() % lcdProp.height / 2;
		Sp.w = 2 + rand() % lcdProp.width / 2;
		Sp.h = 2 + rand() % lcdProp.height / 2;
		r = rand() % 10;
		if (r >= MIN(Sp.w, Sp.h) / 2)
			r = MIN(Sp.w, Sp.h) / 2;
		color = rand() % 0xffff;
		gfx2d_fillRoundRect(Ap, Sp, 1 + r, color);
	}
	clearScr(COLOR_BLACK);
}
