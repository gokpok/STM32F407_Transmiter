
#ifndef __mbmInit_H
#define __mbmInit_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"
	 
// Инициализация модуля
void mbm_Init(uint8_t maxLen, uint16_t timeout, USART_TypeDef *uart, TIM_TypeDef *tim, GPIO_TypeDef *dirPort, uint16_t dirPin, uint64_t *time);

#ifdef __cplusplus
}
#endif
#endif
