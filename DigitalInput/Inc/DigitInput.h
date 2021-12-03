
#ifndef __DigitInput_H
#define __DigitInput_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "main.h"
	 
extern uint8_t *DI_State;   // Указатель на массив состояний обрабатываемых DI
	 

// Инициализация DI модуля
void DI_Init(uint8_t diNum, uint8_t periodPoll, uint8_t numPoll, uint64_t *time);
	 
// Добавление входа в DI модуль
void DI_AddInput(uint8_t diNum, GPIO_TypeDef *port, uint16_t pin);

// Обработчик состояния DI
FuncRes DI_Handler(void);

#ifdef __cplusplus
}
#endif
#endif
