/*
 * ili9341.h
 *
 *  Created on: Dec 31, 2022
 *      Author: ZoMbiE
 */

#ifndef ILI9341_H_
#define ILI9341_H_

#include "main.h"
#include "colors.h"

typedef enum {
	lcdOrientPortrait_0, lcdOrientLandscape_90, lcdOrientPortrait_180, lcdOrientLandscape_270
} lcdOrient;

typedef struct {
	uint16_t width;
	uint16_t height;
	lcdOrient orientation;
} lcdPropertiesTypeDef;

extern lcdPropertiesTypeDef lcdProp;

void ili9341Init(lcdOrient orientation);
void clearScr(unsigned short color);
void setPixel(int x, int y, unsigned short color);
void hLine(int x1, int x2, int y, unsigned short color);
void vLine(int x, int y1, int y2, unsigned short color);
void copyBuffer(unsigned short *buffer, int x, int y, int heigh, int width);

#endif /* ILI9341_H_ */
