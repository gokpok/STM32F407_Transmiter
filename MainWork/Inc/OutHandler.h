
#ifndef __OutHandler_H
#define __OutHandler_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"
	 
// Структура дискретного выхода
typedef struct
{
	GPIO_TypeDef *port;         // порт дискретного выхода (GPIOx)
	uint16_t      pin;          // пин дискретного выхода (GPIO_PIN_x)
	uint64_t      changeTime;   // Время изменения состояния выхода
	uint16_t     *stateReg;     // Регистр управления состоянием
	uint16_t     *onCtrlReg;    // Регистр контроля включения
	uint16_t     *offCtrlReg;   // Регистр контроля отключения
	uint16_t     *toCtrlReg;    // Регистр контроля таймаута
	uint16_t     *onErrReg;     // Регистр ошибки включения
	uint16_t     *offErrReg;    // Регистр ошибки отключения
	uint8_t       bit;          // Номер бита DO в регистрах
} DO_StateStruct;
	 
	 
extern DO_StateStruct *DO_State;   // Указатель на массив состояний обрабатываемых DO
	 

// Инициализация модуля
void DO_Init(uint8_t num);
	 
// Добавление выхода в модуль
void DO_Add(uint8_t num, GPIO_TypeDef *port, uint16_t pin, uint16_t *stateReg, uint16_t *onCtrlReg,
						uint16_t *offCtrlReg, uint16_t *toCtrlReg, uint16_t *onErrReg, uint16_t *offErrReg, uint8_t bit);

// Обработчик состояний DO
void DO_Handler(void);

#ifdef __cplusplus
}
#endif
#endif
