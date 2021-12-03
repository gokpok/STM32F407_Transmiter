
#ifndef __ModbusSlave_H
#define __ModbusSlave_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"

	 
// Структура инициализации модуля
typedef struct
{
	uint8_t            *addr;     // Адрес slave-устройства
	uint16_t           *buf;      // Буфер обмена данными
	uint16_t            bufLen;   // Длинна буфера обмена данными
	UART_HandleTypeDef *uart;     // Приемопередатчик
	TIM_HandleTypeDef  *tim;      // Таймер завершения приема
	GPIO_TypeDef       *dirPort;  // Порт вывода управления RS485
	uint16_t            dirPin;   // Пин вывода управления RS485
	uint64_t           *gTick;    // Ссылка на счетчик глобальных тиков
	uint16_t           *timeout;  // Величина таймаута связи
} MBS_InitStruct;
	 
	 
// Инициализация slave-усройства
void MBS_Init(MBS_InitStruct *initStruct);
	 
// Обработчик slave-усройства
FuncRes MBS_Handler(void);
	 
// Обработчик прерывания по USATR (прием/передача)
void MBS_UART_Interrupt(void);
	 
// Обработчик прерывания по TIM (завершение приема)
void MBS_TIM_Interrupt(void);
	 

#ifdef __cplusplus
}
#endif
#endif
