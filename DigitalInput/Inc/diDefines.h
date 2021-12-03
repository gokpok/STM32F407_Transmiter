
#ifndef __diDefines_H
#define __diDefines_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "DigitInput.h"
	 
	 
// Структура описания дискретного входа
typedef struct
{	
	GPIO_TypeDef *port;    // порт дискретного входа (GPIOx)
	uint16_t      pin;     // пин дискретного входа (GPIO_PIN_x)
} DI_DescriptStruct;
	 
	 
// Структура парметров обработки DI-модуля
typedef struct
{
	// Конфигурация порта	
	uint64_t           *time;        // Указатель на счетчик текущего времени
	uint8_t             diNum;       // Кол-во DI
	uint8_t             periodPoll;  // Периодичность опроса DI
	uint8_t             numPoll;     // Кол-во опроса DI
	
	// Оперативные параметры
	uint64_t   lastTime;  // Время последнего опроса
	uint8_t    stepPoll;  // Шаг (номер) текущего опроса
	uint8_t   *resArr;    // Указатель на массив результатов опроса
}DI_ParamStruct;
	 

extern DI_ParamStruct diParam;   // Параметры обработки DI


#ifdef __cplusplus
}
#endif
#endif
