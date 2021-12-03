
// ------------------------------------------------------------------------------------------------
// Модуль обмена данными по протоколу ModbusRTU в режиме master-устройства
// Разработчик ПО Сынышин Э. М. (edmahalich@yandex.ua)
// 
// Подмодуль инициализации модуля
// ------------------------------------------------------------------------------------------------

#include "mbmInit.h"
#include "mbmData.h"
#include "ModbusMaster.h"
#include "stdlib.h"



// Инициализация интерфейса modbus master ---------------------------------------------------------
void mbm_Init(uint8_t maxLen, uint16_t timeout, USART_TypeDef *uart, TIM_TypeDef *tim, 
							GPIO_TypeDef *dirPort, uint16_t dirPin, uint64_t *time)
{
	// Сохраняем переменные инициализации
	mbmMaxLen  = maxLen;
	mbmTimeout = timeout;
	mbmTime    = time;
	
	// Запоминаем перефирийные переменные
	mbmUart    = uart;
	mbmTim     = tim;
	mbmDirPort = dirPort;
	mbmDirPin  = dirPin;
	
	// Выделяем память под буферы модуля
	mbmRxBuf = (uint8_t*)  malloc(mbmMaxLen * sizeof(uint8_t) * 2 + 10);
	mbmTxBuf = (uint8_t*)  malloc(mbmMaxLen * sizeof(uint8_t) * 2 + 10);
} // mbm_Init()
