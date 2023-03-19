#include "ili9341Port.h"

#define ADDR_CMD (0x60000000) //LCD_RS=0
#define ADDR_RAM (0x60020000) //LCD_RS=1, LINIA A16 przy 16bit

volatile bool transferCompleteDetected = true;
static void TransferComplete(DMA_HandleTypeDef *DmaHandle) {
	transferCompleteDetected = true;
}

void initExtraHardware() {
	HAL_DMA_RegisterCallback(&hdma_memtomem_dma2_stream0, HAL_DMA_XFER_CPLT_CB_ID, TransferComplete);
}

void writeCMD(uint16_t cmd) {
	*(__IO uint16_t*) (ADDR_CMD) = cmd;
}

void writeDATA(uint16_t data) {
	*(__IO uint16_t*) (ADDR_RAM) = data;
}

bool writeBUFFER(uint32_t buffer, uint32_t size) {
	if (transferCompleteDetected) {
		transferCompleteDetected = 0;
		HAL_DMA_Start_IT(&hdma_memtomem_dma2_stream0, buffer, ADDR_RAM, size);
		return true;
	};
	return false;
}

void lcdBlOn() {
	HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_SET);
}

void lcdBlOff() {
	HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_RESET);
}

void lcdRstHI() {
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
}

void lcdRstLOW() {
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
}

void lcdDelayMs(uint32_t ms) {
	HAL_Delay(ms);
}
