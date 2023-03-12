#include "loop.h"
#include <stdbool.h>

//bo pod tym adresem zaczyna się BANK 1
#define CMD 0x60000000

// Dla 8-bit, przełączanie RS(DC) zależy od ustawienia odpowiedniej linii adresowej A0-A25 dla MPU 144 pin lub A16-A23 dla MPU 100 pin,
// trzeba sprawdzić linie Ax oscyloskopem, bo niektóre mają jakieś dziwne przerwy, ale tylo przy przesyłaniu recznym, przy DMA jest ok,
// wg lini ardesowej Ax trzeba ustawić w adresie odpowiedni bit, wtedy wpisując coś pod ten adres wysyłane są dane przez FSMC i zmienia się pin DC w stan wysoki
// np. dla A10 bit 10 czyli 0x60000400, dla A25 to 0x62000000, itp
// Dla 16-bit, przełączanie RS(DC) zależy od ustawienia odpowiedniej linii adresowej A0-A25 dla MPU 144 pin lub A16-A23 dla MPU 100 pin
// wg lini ardesowej Ax trzeba ustawić w adresie odpowiedni bit+0x1(dlatego że jest to adres 16bit), wtedy wpisując coś pod ten adres wysyłane są dane przez FSMC i zmienia się pin DC w stan wysoki
// np. dla A10 bit 10 czyli 0x60000400 + 0x00000100 czyli 0x60000500, dla A25 to 0x62000000 + 0x01000000 czyli 0x63000000, itp
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

