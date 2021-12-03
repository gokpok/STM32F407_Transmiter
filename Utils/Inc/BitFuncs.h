
#ifndef __BitFuncs_H
#define __BitFuncs_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"
	 
// Получение значения бита
uint8_t GetBit(uint16_t *reg, uint8_t bit);
	 
// Задание значения бита
void SetBit(uint16_t *reg, uint8_t bit, uint8_t state);
	 
// Задание бита как "истина"
void SetBitTrue(uint16_t *reg, uint8_t bit);
	 
// Задание бита как "лож"
void SetBitFalse(uint16_t *reg, uint8_t bit);

#ifdef __cplusplus
}
#endif
#endif
