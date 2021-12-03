
#ifndef __mbsData_H
#define __mbsData_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"


// Константы модуля
#define MBS_MAX_TRX_DATA 50
#define MBS_UART         USART3
#define MBS_TIM          TIM2

// Определение для пина управления RS485
#define MBS_DIR_ON     HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_SET)
#define MBS_DIR_OFF    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_RESET)
	 
	 
// Перечисление обрабатываемых фукций обмена
typedef enum
{
	MBS_FUNC_GET_REGS = 0x03,   // Получение значений серии регистров
	MBS_FUNC_SET_REGS = 0x10,	  // Задание значений серии регистров
} MBS_FuncsEnum;

// Структура ссылок перефирии модуля
typedef struct
{
	UART_HandleTypeDef *uart;     // Приемопередатчик
	TIM_HandleTypeDef  *tim;      // Таймер завершения приема
	GPIO_TypeDef       *dirPort;  // Порт вывода управления RS485
	uint16_t            dirPin;   // Пин вывода управления RS485
	uint64_t           *gTick;    // Счетчик глобальных тиков
} MBS_PeripheryStruct;

// Структура глобальных переменных модуля
typedef struct
{
	uint8_t  *addr;        // Адрес save-устройства
	uint16_t *timeout;     // Величина таймаута связи
	uint8_t   endReciev;   // Флаг завершения приема
	uint16_t  dataBegin;   // Начало запрашиваемых данных
	uint16_t  dataNum;     // Длинна запрашиваемых данных
	uint16_t  dataEnd;     // Конец запрашиваемых данных
	uint16_t  rxLen;       // Длинна полученного пакета
	uint16_t  txLen;       // Длинна передаваемого пакета
	uint16_t  crc;         // Контрольная сумма
	uint16_t  count1;      // 1й счетчик собственных нужд
	uint16_t  count2;      // 2й счетчик собственных нужд
} MBS_VariablesStruct;


// Глобальные данные модуля
extern volatile MBS_PeripheryStruct mbsPriph;                              // Перефирия
extern volatile MBS_VariablesStruct mbsVar;                                // Переменные
extern          uint8_t             mbsRxBuf[MBS_MAX_TRX_DATA * 2 + 10];   // Буфер приема
extern          uint8_t             mbsTxBuf[MBS_MAX_TRX_DATA * 2 + 10];   // Буфер передачи
extern          uint16_t           *mbsBuf;                                // Масив данных обмена
extern          uint16_t            mbsBufLen;                             // Размер масива данных обмена



#ifdef __cplusplus
}
#endif
#endif
