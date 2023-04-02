#include "loop.h"
#include "gfx.h"
#include <math.h>

Gfx scr;

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
uint32_t color;
int r;
float deg = 0;
const int iter = 3600;

void setup() {
	scr.init(scrOrientLandscape_90);

	time = HAL_GetTick();
	benchLine();
	benchTriangle();
	benchFillTriangle();
	benchRect();
	benchCircle();
	benchEllipse();
	benchRoundRect();
	time = HAL_GetTick() - time;

}

void loop() {
	benchLine();
	benchTriangle();
	benchFillTriangle();
	benchRect();
	benchCircle();
	benchEllipse();
	benchRoundRect();
}

void rotateStep(gfx2dPoint_t *pIn, gfx2dPoint_t *pOut, float deg) {
	pOut->x = ((pIn->x - 160) * cos(deg * PI / 180.0) - (pIn->y - 120) * sin(deg * PI / 180.0)) + 160;
	pOut->y = ((pIn->x - 160) * sin(deg * PI / 180.0) + (pIn->y - 120) * cos(deg * PI / 180.0)) + 120;
}

void benchLine() {
	srand(HAL_GetTick());
	for (int i = 0; i < iter; i++) {
		Ap.x = rand() % scr.scrWidth;
		Ap.y = rand() % scr.scrHeight;
		Bp.x = rand() % scr.scrWidth;
		Bp.y = rand() % scr.scrHeight;
		color = rand() % 0xffff;
		scr.line_2d(Ap, Bp, color);
	}
	deg = 0;
	scr.clr(COLOR_BLACK);
	for (int i = 0; i < iter >> 2; i++) {
		Ap.x = 160;
		Ap.y = 10;
		Bp.x = 160;
		Bp.y = 230;
		rotateStep(&A, &Ap, deg);
		rotateStep(&B, &Bp, deg);
		color = rand() % 0xffff;
		scr.line_2d(Ap, Bp, color);
		deg = deg + 1;
		HAL_Delay(4);
	}
}

void benchTriangle() {
	srand(HAL_GetTick());
	for (int i = 0; i < iter / 5; i++) {
		Ap.x = rand() % scr.scrWidth;
		Ap.y = rand() % scr.scrHeight;
		Bp.x = rand() % scr.scrWidth;
		Bp.y = rand() % scr.scrHeight;
		Cp.x = rand() % scr.scrWidth;
		Cp.y = rand() % scr.scrHeight;
		color = rand() % 0xffff;
		scr.triangle_2d(Ap, Bp, Cp, color);
	}
	scr.clr(COLOR_BLACK);
	for (int i = 0; i < iter / 5; i++) {
		color = rand() % 0xffff;
		rotateStep(&A, &Ap, deg);
		rotateStep(&B, &Bp, deg);
		rotateStep(&C, &Cp, deg);
		scr.triangle_2d(Ap, Bp, Cp, color);
		scr.triangle_2d(Ap, Bp, Cp, COLOR_BLACK);
		deg = deg + 1;
	}
	scr.clr(COLOR_BLACK);
}

void benchFillTriangle() {
	srand(HAL_GetTick());
	for (int i = 0; i < iter / 5; i++) {
		Ap.x = rand() % scr.scrWidth;
		Ap.y = rand() % scr.scrHeight;
		Bp.x = rand() % scr.scrWidth;
		Bp.y = rand() % scr.scrHeight;
		Cp.x = rand() % scr.scrWidth;
		Cp.y = rand() % scr.scrHeight;
		color = rand() % 0xffff;
		scr.fillTriangle_2d(Ap, Bp, Cp, color);
	}
	scr.clr(COLOR_BLACK);
	for (int i = 0; i < iter / 5; i++) {
		color = rand() % 0xffff;
		rotateStep(&A, &Ap, deg);
		rotateStep(&B, &Bp, deg);
		rotateStep(&C, &Cp, deg);
		scr.fillTriangle_2d(Ap, Bp, Cp, color);
		//HAL_Delay(2);
		scr.fillTriangle_2d(Ap, Bp, Cp, COLOR_BLACK);
		deg = deg + 1;
	}
	scr.clr(COLOR_BLACK);
}

void benchRect() {
	srand(HAL_GetTick());
	for (int i = 0; i < iter; i++) {
		Ap.x = rand() % scr.scrWidth / 2;
		Ap.y = rand() % scr.scrHeight / 2;
		Sp.w = rand() % scr.scrWidth / 2;
		Sp.h = rand() % scr.scrHeight / 2;
		color = rand() % 0xffff;
		scr.rect_2d(Ap, Sp, color);
	}
	scr.clr(COLOR_BLACK);
	for (int i = 0; i < iter / 5; i++) {
		Ap.x = rand() % scr.scrWidth / 2;
		Ap.y = rand() % scr.scrHeight / 2;
		Sp.w = rand() % scr.scrWidth / 2;
		Sp.h = rand() % scr.scrHeight / 2;
		color = rand() % 0xffff;
		scr.fillRect_2d(Ap, Sp, color);
	}
	scr.clr(COLOR_BLACK);
}

void benchCircle() {
	srand(HAL_GetTick());
	for (int i = 0; i < iter; i++) {
		Ap.x = rand() % scr.scrWidth;
		Ap.y = rand() % scr.scrHeight;
		r = rand() % scr.scrHeight;
		color = rand() % 0xffff;
		scr.circle_2d(Ap, r, color);
	}
	scr.clr(COLOR_BLACK);
	for (int i = 0; i < iter / 5; i++) {
		Ap.x = rand() % scr.scrWidth;
		Ap.y = rand() % scr.scrHeight;
		r = rand() % scr.scrHeight / 2;
		color = rand() % 0xffff;
		scr.fillCircle_2d(Ap, r, color);
	}
	scr.clr(COLOR_BLACK);

}

void benchEllipse() {

	srand(HAL_GetTick());
	for (int i = 0; i < iter; i++) {
		Ap.x = rand() % scr.scrWidth;
		Ap.y = rand() % scr.scrHeight;
		Rp.rx = rand() % scr.scrWidth;
		Rp.ry = rand() % scr.scrHeight;
		color = rand() % 0xffff;
		//scr.clr(COLOR_BLACK);
		scr.ellipse_2d(Ap, Rp, color);
	}
	scr.clr(COLOR_BLACK);
	for (int i = 0; i < iter / 5; i++) {
		Ap.x = rand() % scr.scrWidth;
		Ap.y = rand() % scr.scrHeight;
		Rp.rx = rand() % scr.scrWidth;
		Rp.ry = rand() % scr.scrHeight;
		color = rand() % 0xffff;
		scr.fillEllipse_2d(Ap, Rp, color);
	}
	scr.clr(COLOR_BLACK);
}

void benchRoundRect() {
	srand(HAL_GetTick());
	for (int i = 0; i < iter; i++) {
		Ap.x = rand() % scr.scrWidth / 2;
		Ap.y = rand() % scr.scrHeight / 2;
		Sp.w = 2 + rand() % scr.scrWidth / 2;
		Sp.h = 2 + rand() % scr.scrHeight / 2;
		r = rand() % 10;
		if (r >= MIN(Sp.w, Sp.h) / 2)
			r = MIN(Sp.w, Sp.h) / 2;
		color = rand() % 0xffff;
		scr.roundRect_2d(Ap, Sp, 1 + r, color);
	}
	scr.clr(COLOR_BLACK);
	for (int i = 0; i < iter / 5; i++) {
		Ap.x = rand() % scr.scrWidth / 2;
		Ap.y = rand() % scr.scrHeight / 2;
		Sp.w = 2 + rand() % scr.scrWidth / 2;
		Sp.h = 2 + rand() % scr.scrHeight / 2;
		r = rand() % 10;
		if (r >= MIN(Sp.w, Sp.h) / 2)
			r = MIN(Sp.w, Sp.h) / 2;
		color = rand() % 0xffff;
		scr.fillRoundRect_2d(Ap, Sp, 1 + r, color);
	}
	scr.clr(COLOR_BLACK);
}
