
#ifndef __mbmData_H
#define __mbmData_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"


// Определение для пина управления RS485
#define MBM_DIR_ON     HAL_GPIO_WritePin(mbmDirPort, mbmDirPin, GPIO_PIN_SET)
#define MBM_DIR_OFF    HAL_GPIO_WritePin(mbmDirPort, mbmDirPin, GPIO_PIN_RESET)
	 

// Закрытые переменные модуля
extern uint8_t  *mbmRxBuf;      // Буфер приема
extern uint8_t  *mbmTxBuf;      // Буфер передачи
extern uint8_t   mbmAnsWait;    // Флаг ожидания ответа
extern uint8_t   mbmEndReciev;  // Флаг завершения приема
extern uint16_t  mbmDataBegin;  // Начало запрашиваемых данных
extern uint16_t  mbmDataNum;    // Длинна запрашиваемых данных
extern uint16_t  mbmDataEnd;    // Конец запрашиваемых данных
extern uint16_t  mbmRxLen;      // Длинна полученного пакета
extern uint16_t  mbmTxLen;      // Длинна передаваемого пакета
extern uint16_t  mbmCRC;        // Контрольная сумма
extern uint64_t *mbmTime;       // Счетчик глобальных тиков
extern uint64_t  mbmQueryTime;  // Время отправки запроса
extern uint16_t  mbmCount1;     // 1й счетчик собственных нужд
extern uint16_t  mbmCount2;     // 2й счетчик собственных нужд


// Переменные перефирии slave-устройства
extern USART_TypeDef *mbmUart;     // Приемопередатчик
extern TIM_TypeDef   *mbmTim;      // Таймер завершения приема
extern GPIO_TypeDef  *mbmDirPort;  // Порт вывода управления RS485
extern uint16_t       mbmDirPin;   // Пин вывода управления RS485

#ifdef __cplusplus
}
#endif
#endif
