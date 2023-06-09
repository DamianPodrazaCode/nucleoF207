#include "loop.h"
#include <stdbool.h>

//jeszcze należy zmienić ustawienia w CubeMX,
// * Connectivity->FSMC->Data = 8 lub 16 bit
// * System Core->DMA->MEMTOMEM->Data width = Byte lub Half Word
//#define FSMC_LCD_8bit
#define FSMC_LCD_16bit

#ifdef FSMC_LCD_8bit

#define ADDR_CMD (0x60000000) //LCD_RS=0
#define ADDR_RAM (0x60010000) //LCD_RS=1, LINIA A16 przy 8bit
#define LCD_CMD (*((__IO uint8_t*) ADDR_CMD))
#define LCD_RAM (*((__IO uint8_t*) ADDR_RAM))

#define buffSize 16
uint8_t src[buffSize] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

#endif

#ifdef FSMC_LCD_16bit

#define ADDR_CMD (0x60000000) //LCD_RS=0
#define ADDR_RAM (0x60020000) //LCD_RS=1, LINIA A16 przy 16bit
#define LCD_CMD (*((__IO uint16_t*) ADDR_CMD))
#define LCD_RAM (*((__IO uint16_t*) ADDR_RAM))

#define buffSize 16
uint16_t src[buffSize] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

#endif

volatile int transferCompleteDetected = 1;
static void TransferComplete(DMA_HandleTypeDef *DmaHandle) {
	transferCompleteDetected = 1;
}

void setup() {
	HAL_DMA_RegisterCallback(&hdma_memtomem_dma2_stream0, HAL_DMA_XFER_CPLT_CB_ID, TransferComplete);
}

bool fAddr = true;
volatile uint32_t lcdAddr;

void loop() {
	if (transferCompleteDetected > 0) {
		transferCompleteDetected = 0;

		if (fAddr) {
			lcdAddr = ADDR_CMD;
			fAddr = false;
		} else {
			lcdAddr = ADDR_RAM;
			fAddr = true;
		}

		HAL_DMA_Start_IT(&hdma_memtomem_dma2_stream0, (uint32_t) src, lcdAddr, buffSize);

	}
}
