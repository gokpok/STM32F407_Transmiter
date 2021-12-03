
#ifndef __mbsHandler_H
#define __mbsHandler_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "ModbusSlave.h"

FuncRes mbs_Handler(void);    // Обработчик обмена данными

#ifdef __cplusplus
}
#endif
#endif
