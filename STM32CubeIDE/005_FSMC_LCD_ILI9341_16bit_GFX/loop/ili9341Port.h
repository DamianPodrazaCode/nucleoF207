#ifndef ILI9341PORT_H_
#define ILI9341PORT_H_

#include "main.h"
#include "fsmc.h"
#include "dma.h"

#include <stdbool.h>
#include <stdlib.h>

void initExtraHardware();
void writeCMD(uint16_t cmd);
void writeDATA(uint16_t data);
bool writeBUFFER(uint32_t buffer, uint32_t size);
void lcdBlOn();
void lcdBlOff();
void lcdRstHI();
void lcdRstLOW();
void lcdDelayMs(uint32_t ms);

#endif /* ILI9341PORT_H_ */
