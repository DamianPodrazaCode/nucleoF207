#include "loop.h"
#include <stdbool.h>

#define CMD 0x60000000
#define RAM 0x60010000 //LCD Register select = FSMC_A16

#define buffSize 32
uint8_t src[buffSize] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, //
		16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };

volatile int transferCompleteDetected = 0;
static void TransferComplete(DMA_HandleTypeDef *DmaHandle) {
	transferCompleteDetected = 1;
}

void setup() {
	HAL_DMA_RegisterCallback(&hdma_memtomem_dma2_stream0, HAL_DMA_XFER_CPLT_CB_ID, TransferComplete);
	transferCompleteDetected = 1; //pierwsze wysłanie po dma
}

bool fAddr = true;
volatile uint32_t lcdAddr;

void loop() {
	if (transferCompleteDetected > 0) {
		transferCompleteDetected = 0;

		if (fAddr) {
			lcdAddr = CMD;
			fAddr = false;
		} else {
			lcdAddr = RAM;
			fAddr = true;
		}

		TRIG_GPIO_Port->BSRR = TRIG_Pin << 16; //PC0 = 0
		HAL_DMA_Start_IT(&hdma_memtomem_dma2_stream0, (uint32_t) src, lcdAddr, buffSize);
		TRIG_GPIO_Port->BSRR = TRIG_Pin; //PC0 = 1
	}
}

