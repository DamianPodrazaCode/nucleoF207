#include "loop.h"
#include "drvILI9341.h"

DrvILI9341 lcd;

void setup() {
	lcd.drv_init(lcdOrientLandscape_90);
	lcd.clearScr(COLOR_BLUE);
}

void loop() {

}

