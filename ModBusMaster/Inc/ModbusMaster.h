
#ifndef __ModbusMaster_H
#define __ModbusMaster_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
	 
	 
	 
// Перечисление обрабатываемых фукций обмена
typedef enum
{
	MBM_FUNC_GET_REGS = 0x03,   // Получение значений серии регистров
	MBM_FUNC_SET_REGS = 0x10,	  // Задание значений серии регистров
} MBM_FuncsEnum;


	 
// Перечисление ошибок модуля
typedef enum
{
	MBM_ERR_NONE      = 0,   // Отсутствие ошибки
	
	MBM_ERR_BADFUNC   = 1,   // Недопустимая функция запроса
	MBM_ERR_BADADDR   = 2,   // Адрес данных, указанный в запросе, недоступен
	
	MBM_ERR_TIMEOUT   = 100,   // Таймаут ожидания ответа
	MBM_ERR_MAX_LEN   = 101,   // Превышение допустимой длинны пакета
	MBM_ERR_ANSWER    = 102,   // Ошибочный ответ
} MBM_ErrEnum;


	 
extern uint8_t     mbmMaxLen;     // Максимальный размер обмена
extern uint16_t    mbmTimeout;    // Величина ожидания ответа slave-устройства
extern MBM_ErrEnum mbmErr;        // Ошибка транзакции
	 
	 
// Инициализация master-усройства
void MBM_Init(uint8_t maxLen, uint16_t timeout, USART_TypeDef *uart, TIM_TypeDef *tim, GPIO_TypeDef *dirPort, uint16_t dirPin, uint64_t *time);
	 
// Обработчик прерывания по USATR (прием/передача)
void MBM_UART_Interrupt(USART_TypeDef *uart);
	 
// Обработчик прерывания по TIM (завершение приема)
void MBM_TIM_Interrupt(TIM_TypeDef *tim);
	 
// Функция получения значений серии регистров от устройства
FuncRes MBM_GetRegs(uint8_t addr, uint16_t first, uint16_t quant, uint16_t *data);
	 
// Функция задания значений серии регистров от устройства
FuncRes MBM_SetRegs(uint8_t addr, uint16_t first, uint16_t quant, uint16_t *data);
	 

#ifdef __cplusplus
}
#endif
#endif
